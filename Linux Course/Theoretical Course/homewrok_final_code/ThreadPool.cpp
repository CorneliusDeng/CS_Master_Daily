#include "header.h"

template <typename T>
SafeQueue<T>::SafeQueue() {}

template <typename T>
SafeQueue<T>::SafeQueue(SafeQueue &&other) {}

template <typename T>
SafeQueue<T>::~SafeQueue() {}

template <typename T>
bool SafeQueue<T>::empty(){
    std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变

    return m_queue.empty();
}

template <typename T>
int SafeQueue<T>::size(){
    std::unique_lock<std::mutex> lock(m_mutex); // 互斥信号变量加锁，防止m_queue被改变

    return m_queue.size();
}


class ThreadPool::ThreadWorker
{
private:
    int m_id; // 工作id
    ThreadPool *m_pool; // 所属线程池

public:
    ThreadWorker(ThreadPool *pool, const int id);
    void operator()();
};

ThreadPool::ThreadWorker::ThreadWorker(ThreadPool *pool, const int id) : m_pool(pool), m_id(id) {}

void ThreadPool::ThreadWorker::operator()()
{
    std::function<void()> func; // 定义基础函数类func
    bool dequeued; // 是否正在取出队列中元素

    while (!m_pool->m_shutdown)
    {
        {
            std::unique_lock<std::mutex> lock(m_pool->m_conditional_mutex); // 为线程环境加锁，互访问工作线程的休眠和唤醒

            if (m_pool->m_queue.empty()) // 如果任务队列为空，阻塞当前线程
            {
                m_pool->m_conditional_lock.wait(lock); // 等待条件变量通知，开启线程
            }

            dequeued = m_pool->m_queue.dequeue(func); // 取出任务队列中的元素
        }

        // 如果成功取出，执行工作函数
        if (dequeued)
            func();
    }
}

ThreadPool::ThreadPool(const int n_threads)
    : m_threads(std::vector<std::thread>(n_threads)), m_shutdown(false) {} // 线程池构造函数

void ThreadPool::init()
{
    for (int i = 0; i < m_threads.size(); ++i)
    {
        m_threads.at(i) = std::thread(ThreadWorker(this, i)); // 分配工作线程
    }
}

// Waits until threads finish their current task and shutdowns the pool
void ThreadPool::shutdown()
{
    m_shutdown = true;
    m_conditional_lock.notify_all(); // 通知，唤醒所有工作线程

    for (int i = 0; i < m_threads.size(); ++i)
    {
        if (m_threads.at(i).joinable()) // 判断线程是否在等待
        {
            m_threads.at(i).join(); // 将线程加入到等待队列
        }
    }
}