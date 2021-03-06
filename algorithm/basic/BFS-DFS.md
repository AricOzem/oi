# DFS和BFS

在对一件事毫无头绪时，我们可以用DFS\(深度优先搜索\)和BFS\(广度优先搜索\)来穷举所有情况

## 1 深度优先搜索

（英语：Depth-First-Search，简称DFS）是一种用于遍历或搜索树或图的算法。沿着树的深度遍历树的节点，尽可能深的搜索树的分支。当节点v的所在边都己被探寻过，搜索将回溯到发现节点v的那条边的起始节点。这一过程一直进行到已发现从源节点可达的所有节点为止。如果还存在未被发现的节点，则选择其中一个作为源节点并重复以上过程，整个进程反复进行直到所有节点都被访问为止。属于盲目搜索。

### 1.1算法步骤

深度优先遍历的方法是，从某元素出发：  
1. 访问元素v；  
2. 依次从v的未被访问的邻接点出发，对图进行深度优先遍历；直至图中和v有路径相通的顶点都被访问；  
3. 若此时图中尚有顶点未被访问，则从一个未被访问的顶点出发，重新进行深度优先遍历，直到图中所有顶点均被访问过为止

伪代码：

其中节点颜色的设置时为了方便设置点的状态也是为了方便理解

```cpp
DFS(G, s)
    for 在图G中的每一个节点u
        status[u] = WHITE
    // 进行其他初始化
    DFS-VISIT(s) 
DFS-VISIT(u)
    status[u] = GRAY
        for 每一个u的邻接节点v
            if (status[v] == WHITE)
                DFS-VISIT(v)
    status[u] = BLACK
```

### 1.2应用例题

[NOIP 2000 单词接龙](http://codevs.cn/problem/1018/) [题解](/CodeVS/p1018.md)

## 2 广度优先搜索

（英语：Breadth-First-Search，缩写为BFS），同样是一种图形搜索算法。简单的说，BFS是从根节点开始，沿着树的宽度遍历树的节点。如果所有节点均被访问，则算法中止。

### 2.1 算法步骤

广度优先算法的核心思想是：从初始节点开始，应用算符生成第一层节点，检查目标节点是否在这些后继节点中，若没有，再用产生式规则将所有第一层的节点逐一扩展，得到第二层节点，并逐一检查第二层节点中是否包含目标节点。若没有，再用算符逐一扩展第二层的所有节点……，如此依次扩展，检查下去，直到发现目标节点为止。即

1. 从图中的某一顶点V0开始，先访问V0；
2. 访问所有与V0相连的顶点V1，V2，......，Vt；
3. 依次访问与V1，V2，......，Vt相邻接的所有未曾访问过的顶点；
4. 循此以往，直至所有的顶点都被访问过为止。

这种搜索的次序体现沿层次向横向扩展的趋势，所以称之为广度优先搜索。  
伪代码

```cpp
bool BFS(Node& s, Node& t){
    queue<Node> Q;
    Node u,v;
    //初始状态将起点放进队列Q
    Q.push(s);
    while (!Q.empty()){//队列不为空，继续搜索！
        //取出队列的头Vn
        u = Q.front();
        //从队列中移除
        Q.pop();
        for 每一个与u邻接的v{
            if (v == t){
                //找到终点后具体操作
                return true;//返回
            }
            if (isValid(v) && !visit(v)){
                //v是一个合法的节点并且为白色节点
                Q.push(v);//加入队列Q
                hash(v) = true;//设置节点颜色
            }
        }
    }
    return false;//无解
}
```

其中节点颜色只是为了方便理解，并不一定要设置

### 2.2 应用例题

[Luogu 1443 马的遍历](https://www.luogu.org/problem/show?pid=1443) [题解](/Luogu/p1443.md)

