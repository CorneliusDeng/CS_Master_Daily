# Introduction to Big Data Mining

- Big data is a buzzword, or catch-phrase, used to describe a massive volume of both structured and unstructured data that is so large that it's difficult to process using traditional database and software techniques. 

- The four V's of big data

  - Volume: scale of data
  - Variety: different forms of data
  - Velocity: analysis of streaming data
  - Veracity: uncertainty of data

- Data mining consists of applying data analysis and discovery algorithms that, under acceptable computational efficiency limitations, produce a particular  enumeration of patterns over the data

- Main Data Mining Tasks

  - Association Rule Mining
  - Cluster Analysis
  - Classification/Prediction
  - Outlier Detection

- Main Directions of Big Data Mining

  - Scalable Data Mining Algorithms 

    Basic idea: propose new data mining algorithms to handle big data using differernt strategies, mainly focus on: 

    - Novel scalable algorithms (Sampling, Hashing, Divide-and-Conquer, etc.)
    - Map-reduce oriented Parallell platforms (Hadoop, Spark, GraphLab)
    - Speed-up Hardwares (GPUs/Clouds/Clusters)

  - Data Stream Mining

    Basic idea: propose new data mining algorithms to handle evloving data streams using differernt strategies, mainly focus on:

    - Handle Evolving Data Streams 
    - Clustering on Massive Data Streams
    - Classification/Prediction
    - Semi-supervised Learning
    - Irregular nodes/patterns mining on data streams

  - Multi-source or multi-type data mining

    Basic idea: propose new algorithms for structure or unstructure data, or different types of data, different sources, etc,  mainly focus on:

    - Different types of data (E.g. categorical data, nominal data, mixed- type data mining )
    - Different forms of data (vector data, graph data, image/text data, hetergeneous data) 
    - Learning on different sources of data (Multi-view learning, Transfer learning, Multi-task learning, etc)
    - Data fusion or data integration (Multiple-kernel learning）

  - Uncertainty Analysis, Link/Missing value prediction

    - Link Prediction (Clustering-based, Structure-based, Multi-view based)

    - Uncertain data Clustering (Probability-function based)

    - Recommender System (Missing items prediction,...)

    - Robust Machine learning (Adversarial examples)

      

# Foundation of Data Mining

## Main tasks in machine learning

- Supervised learning: targets to learn the mapping function or relationship between the features and the labels based on the labeled data.
- Unsupervised learning: aims at learning the intrinsic structure from unlabeled data.
- Semi-supervised learning: can be regarded as the unsupervised learning with some constraints on labels, or the supervised learning with additional information on the distribution of data. 

Supervised Learning
- Given training data $X=\{(x_1,y_1),(x_2,y_2),\cdots,(x_N,y_N)\}$ where $y_i$ is the corresponding label of data $x_i$, supervised learning learns the mapping function $Y=F(X|\theta)$, or the posterior distribution $P(Y|X)$
- Supervised problems: Classification、Regression、 Learn to Rank、Tagging

## Loss Function

To measure the predicted results, we introduce the loss function $L(Y,F(X|θ))$, which a non-negative function

- 0-1 loss 
  $$
  L(y,F(x))= 
  \begin{cases}
  0, &  y = F(x|\theta) \\
  1, &  y ≠ F(x|\theta)
  \end{cases}
  $$

- Squared loss: $L(y,F(x|\theta))=(y-F(x|\theta))^2$

- Absolute loss: $L(y,F(x|\theta))=|y-F(x|\theta)|$

- Log loss (Cross Entropy): $L(y,P(y|x,\theta))=-logP(y|x,\theta)=-\displaystyle\sum_{j=1}^Cy_jlogp_j=-[y_jlogp_j+(1-y_j)log(1-p_j)]$

Training loss: loss on training data   

Test loss: loss on test data

Generalization 

- Empirical  risk: $R(F)=\frac{1}{N}\displaystyle\sum_{i=1}^NL(y_i,F(x_i))$
- Note: A good model cannot only take training loss into account and minimize the empirical risk. Instead, improve the model generalization.

Model Selection: To avoid Underfitting and Overfitting 

Strategy of avoiding overfit

- Increase Sample
- Remove Outliers
- Decrease model complexity
- Train-Validation-Test
- Regularization 

Model Selection and Regularization

- Structural risk: Empirical risk + regularization 

  $\frac{1}{N}\displaystyle\sum_{i=1}^NL(y_i,F(x_i))+\lambda\phi(F)$

  $\phi(F)$ measures model complexity, aiming at selecting a model that can fit the current data as simple as possible

  $\lambda$ is the trade-off between model fitness and model complexity

- Choice of $\phi(F)$

  - $l_2$ norm: $L(\beta)=\frac{1}{N}\displaystyle\sum_{i=1}^NL(Y_i,F(X_i|\beta))+\frac{\lambda}{2}||\beta||_2$
  - $l_1$ norm: $L(\beta)=\frac{1}{N}\displaystyle\sum_{i=1}^NL(Y_i,F(X_i|\beta))+\frac{\lambda}{2}||\beta||_1$

## Classification

### Nearest Neighbor Classifiers

Basic idea: If it walks like a duck, quacks like a duck, then it’s probably a duck

K-nearest neighbors of a record x are data points that have the k smallest distance to x

Predict class label of test instance with major vote strategy

Remarks:

✅ Highly effective method for noisy training data

✅ Target function for a whole space may be described as a combination of less complex local approximations

✅ Learning is very simple (lazy learning)

❎ Classification is time consuming

❎ Difficult to determine the optimal k

❎ Curse of Dimensionality

### Naïve Bayes

Given training data  $X$, posteriori probability of a hypothesis $H$, $P(H|X)$ follows the Bayes theorem $P(H|X)=\frac{P(X|H)P(H)}{P(X)}$

Predicts $X$ belongs to $C_2$ iff the probability $P(C_2|X)$ is the highest among all the $P(C_k|X)$ for all the $k$ classes

Practical difficulty: require initial knowledge of many probabilities, significant computational cost

Class Conditional independent :
$$
\begin{align}
& P(X|C_i)=\displaystyle\prod_{k=1}^nP(x_k|C_i) \\
& P(C_i|X)=\frac{P(X|C_i)P(C_i)}{P(X)}=\frac{P(C_i) \displaystyle \prod_{k=1}^n P(x_k|C_i) }{P(X)} \\
& \underset{i}{arg\; max}\,P(C_i|X)=P(C_i)\displaystyle\prod_{k=1}^nP(X_i|C_i)
\end{align}
$$

### Decision Tree

$Information\;Gain(A) =Entropy(S)-\displaystyle\sum_{v\in Values(A)}\frac{|S_v|}{|S|}·Entropy(S_v) $

$Entropy=-\displaystyle\sum_{d\in Decisions}p(d)log((p(d)))$

### Support Vector Machine

There are infinite lines (hyperplanes) separating the two classes but we want to find the best one (the one that minimizes classification error on unseen data)

SVM searches for the hyperplane with the largest margin, i.e., maximum marginal hyperplane (MMH)

- SVM—Linearly Separable


A separating hyperplane can be written as: $W\cdot X+b=0$, The hyperplane defining the sides of the margin: $H_1:w_0+w_1x_1+w_1x_1\geq1,for \; y_i=+1$, H_2:w_0+w_1x_1+w_1x_1\leq-1,for \; y_i=-1$

Any training tuples that fall on hyperplanes $H_1$ or $H_2$ (i.e., the sides defining the margin) are support vectors.

This becomes a constrained (convex) quadratic optimization problem: 
$$
margin=\underset{w,b}{max}\frac{2}{||w||}\Longleftrightarrow\underset{w,b}{min}\frac{1}{2}||w||^2 \\
s.t. \; y_i(w\cdot x_i+b)\geq1,\; i=1,2,\cdots,N \\
\\
\text{1、Constrained optimization problem to non-constrained problem with augmented Lagrangian multipliers
} \\
L(w,b,\alpha)=\frac{1}{2}||w||^2-\displaystyle\sum_{i=1}^N\alpha_i(y_i(w\cdot x_i+b)-1) \\
2、Let \; \theta(w)=\underset{\alpha_i\geq0}{max}L(w,b,\alpha)  \\
\theta(w)=
\begin{cases}
\frac{1}{2}||w||^2, & y_i(w\cdot x_i+b)\geq1 \\
+\infty, & y_i(w\cdot x_i+b)\leq1
\end{cases}
\Longrightarrow
\underset{w,b}{min}\;\theta(w)=\underset{w,b}{min}\;\underset{\alpha_i\geq0}{max}L(w,b,\alpha) =p^*\\ \\
\text{Because Lagrange duality},\quad \underset{w,b}{min}\;\theta(w)=\underset{w,b}{min}\;\underset{\alpha_i\geq0}{max}L(w,b,\alpha) =p^* \rightarrow \underset{\alpha_i\geq0}{max}\; \underset{w,b}{min}L(w,b,\alpha) =d^* \\

\text{KTT Conditions}
\begin{cases}
\alpha_i \geq 0 \\
y_i(w_i\cdot x_i+b) - 1 \geq 0 \\
\alpha_i(y_i(w_i\cdot x_i+b) - 1) = 0, \quad \text{$\alpha_i$ is support vector }
\end{cases} \\
\begin{align}
L(w,b,\alpha)
& =\frac{1}{2}\displaystyle\sum_{i=1}^N\sum_{j=1}^N \alpha_i\alpha_jy_iy_j(x_i\cdot x_j)-\sum_{i=1}^N\alpha_iy_i((\sum_{j=1}^N\alpha_jy_jx_j)\cdot x_i+b)+\sum_{i=1}^N\alpha_i  \\
& = -\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N \alpha_i\alpha_jy_iy_j(x_i\cdot x_j)+\sum_{i=1}^N\alpha_i \\
\end{align}
$$

- SVM—Linearly Inseparable


Transform the original input data into a higher dimensional space

Search for a linear separating hyperplane in the new space

Kernel Trick: Instead of computing the dot product on the transformed data tuples, it is mathematically equivalent to instead applying a kernel function $K(X_i,X_j)$ to the original data, i.e., $K(x,z)=\phi(x)\phi(z)$
$$
SVM+Kernel \quad 
\frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N \alpha_i\alpha_jy_iy_j(\phi(x_i)\cdot \phi(x_j))-\sum_{i=1}^N\alpha_i \\
s.t. \; \sum_{i=1}^N\alpha_iy_i=0;\quad 0\leq\alpha_i\leq C \\
\text{Objective function}\quad \frac{1}{2}\sum_{i=1}^N\sum_{j=1}^N \alpha_i\alpha_jy_iy_j\cdot k(x,z)-\sum_{i=1}^N\alpha_i \\
Classifier \quad sign(\sum_{i=1}^N\alpha_iy_i(x_i\cdot x+1)^p+b) \\
Kmeans+Kernel \quad \underset{H^TH=1,H\geq0}{max}Tr(H^TX^TXH) \\
PCA+Kernel \quad C_F=\frac{1}{N}\phi(X)[\phi(X)]^T=\frac{1}{N}\sum_{i=1}^N\phi(x_i)\phi(x_i)^T
$$

## Ensemble Learning

- Strategies: Bagging、Boosting、Stacking

- Rationale for Ensemble Learning
  - No Free Lunch thm: There is no algorithm that is always the most accurate
  - Generate a group of base-learners which when combined have higher accuracy
  - Different learners use different：Algorithms、Parameters、Representations (Modalities)、Training sets、Subproblems

### Bagging - Aggregate Bootstrapping

Given a standard training set $D$ of size $n$
For i = 1 ... M
	Draw  a sample of size $n*<n$ from $D$ uniformly and with replacement
	Learn classifier $C_i$
Final classifier is a vote of $C_1\cdots C_M$ 
Increases classifier stability/reduces variance

- Random Forest
  - Ensemble consisting of a bagging of un-pruned decision tree learners with a randomized selection of features at each split.
  - Grow many trees on datasets sampled from the original dataset with replacement (a bootstrap sample). 
    - Draw K bootstrap samples of a fixed size
    - Grow a DT, randomly sampling a few attributes/dimensions to split on at each internal node
  - Average the predictions of the trees for a new query (or take majority vote)

### Boosting

Train classifiers (e.g. decision trees) in a sequence

A new classifier should focus on those cases which were incorrectly classified in the last round.

Combine the classifiers by letting them vote on the final prediction (like bagging).

Each classifier is “weak” but the ensemble is “strong.”

AdaBoost is a specific boosting method.

![](https://raw.githubusercontent.com/CorneliusDeng/Markdown-Photos/main/Machine%20Learning/Adaboost.png)

### Stacking

## Clustering





# Hashing 





# Sampling





# Data Stream Mining





# Graph Mining





# Hadoop-Spark





# Review

- What is big data?

- The 4V features in big data.

- What is  data mining?

- The main tasks of data mining?

- Main tasks in machine learning

- Loss function 

- Generalization: $L(M)=\sum_{i=1}^n(Y_i-Y_i^*)^2+\lambda \Phi(M)$

- How to avoid overfitting?

  - Increasing samples
  - Remove outlines
  - Train-Validation-Test
  - Decreasing the model complexity 
  - Regulization ($l_1$ norm, $l_2$ norm)

- Classical Algorithm (KNN、Naive Bases)

- Decision Tree

  - How to find the best split?

    Information Gain: $IG(x) = H(Y) -H(Y|X)$

  - Advantages 

- Support Vector Machine

  - Basic idea: class margin maximum 

  - Define **any** three parallel hyperplane   
    $$
    \begin{cases}
    wx+b=1 \\
    wx+b=0 \\
    wx+b=-1
    \end{cases}
    \Longrightarrow
    \begin{cases}
    y_i(wx_i+b) \geq 1, & \text {empirical risk} \\
    max\frac{1}{||w||}, & \text {margin maximum} \\
    min\frac{1}{2}||w||^2
    \end{cases}
    $$

- next time

  