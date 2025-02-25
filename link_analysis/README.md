# Link Analysis 

## Page Rank

Summarized the important bits of [this](http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf)

+ **PageRank** is a method for ranking a web page based on the graph of the web
+ Every link can be considered as a academic citation. That is, it is being referenced.
+ Nodes can be considered pages (web pages) and edges can be considered the "citations" or links.


## Formula

Let **u** be a web page (i.e. page of a website)

Let $F_{u}$ be the set (unique) of pages u points to. We can consider this to be the start node.

Let $B_{u}$ be the set (unique) of pages that point to u. We can consider this to be the end node.

Let $N_{u}$ = $|F_{u}|$ be the number of links from u. We can consider this the number of links/edges coming out from web page/node u. That is, $N_{u}$ is the number of forward links.

Let **c** be a factor used for normalization. 

Let **A** be square matrix with rows and columns corresponding to the web pages. $A_{u,v}$ = $\frac{1}{N_{u}}$ if there is a edge from **u** to **v**. Otherwise $A_{u,v}$ = 0.

If we treat **R** as a vector over web pages, then we have **R** = **cAR**.

### Simplified Formula: 

R(u) = c $\sum_{v \in B_{u} } \frac{R(v)}{N_{u}}$

### Formula That Solves Infinite Loop

**Problem**: There becomes an issue where there are two web pages that point to each other and no other web pages. That is, there are no edges other than to itself (undirected). This will create a infinite loop where the page will accumulate rank, but not set the rank.

Let **E(u)** be a vector over the web pages that corresponds to source of rank. We can consider this as a way to prevent circumstances where there are infinite loops.

R'(u) = c $\sum_{v \in B_{u} } \frac{R'(v)}{N_{u}}$ + cE(u)

### Finding PageRank Algorithm

$R_{0} \leftarrow S$

while $\delta > \epsilon$:

$R_{i+1} \leftarrow AR_{i}$

$d \leftarrow ||R_{i}||\_{1} - ||R_{i+1}||_{1}$

$R_{i+1} \leftarrow R_{i+1} + dE$

$\delta \leftarrow ||R_{i+1}$ - $R_{i}||_{1}$

end loop

There is still an issue with this approach with **dangling links**. **Dangling links** are links that point to any page with no outgoing links, that is, these links are the last link for the web page that it is point to. This is an issue because it is unknown where their weight (**PageRank**) should be distributed. 

One solution can be that the dangling node/link can be removed from the system and then added back at the end when all **PageRanks** have been calculated.
