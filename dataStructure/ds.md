## Kruskal Reconstruction Tree ##
find two nodes (u,v) which not connected with edge weight w
    - find root u (u') and v (v')
    - connect 2 root as child of new node x (assign weight w)
Tree property :
- binary tree
- max heap (root = last merge = largest weight)

## Catersian Tree ##
- value (k,w) (usually k is index, w is value)
- Binary Tree(k) + heap(w) 

## Treap ##
- I don't get actually :< 

## SweepLine Segment Tree ##
- discretization 
- do line by line, use seg tree for update

## Segment Tree with Graph ##
- Less edge for building the graph (O(N) -> O(lgN))

## Sqrt Decomposition ##
separating size O(N) structure to O(sqrt(n)) "blocks" , each with size O(sqrt(N))   

## Weighted DSU ## 
- store additional information on dsu 
- unite
- a->pa and b->pb 
- we want to unite ab
- val[pa] = val[b] - val[a] + s; 
a -> pa 
|     |
b -> pb