
## 

## 207. 课程表
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

 

示例 1：
```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
```
示例 2：
```
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
```
***
#### 思路：
经典图问题，要建立入度表和邻接表。

```
class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        m = len(prerequisites)
        if m ==0:
            return True
        in_degree = [0] * numCourses
        adj = [set() for _ in range(numCourses)]
        #要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
        for second, first in prerequisites:
            in_degree[second] += 1
            adj[first].add(second)
        #上面实现的是入度表和临接表

        #先遍历一遍，把所有入度为0的节点加入队列
        queue = deque()
        for i in range(numCourses):
            if in_degree[i] == 0:
                queue.append(i)
        
        counter =0
        while queue:
            top=queue.popleft()
            counter +=1
            for successor in adj[top]:
                in_degree[successor] -= 1
                if in_degree[successor] == 0:
                    queue.append(successor)
        return counter == numCourses
```

## 210. 课程表 II
现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程 ai 前 必须 先选修 bi 。

例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。

 

示例 1：
```
输入：numCourses = 2, prerequisites = [[1,0]]
输出：[0,1]
解释：总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
```
示例 2：
```
输入：numCourses = 4, prerequisites = [[1,0],[2,0],[3,1],[3,2]]
输出：[0,2,1,3]
解释：总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
```
示例 3：
```
输入：numCourses = 1, prerequisites = []
输出：[0]
```

***
#### 思路：
和[课程表](https://leetcode.cn/problems/course-schedule/)思路一致，依旧是BFS即可。

```
class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        # 你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
        # 表示为 0 <- 1

        in_degree = [0] * numCourses
        adj  = [set() for _ in range(numCourses)]

        for second, first in prerequisites:
            in_degree[second] += 1
            adj[first].add(second)
        
        allowCourse = collections.deque()
        for i in range(numCourses):
            if in_degree[i] == 0:
                allowCourse.append(i)
        
        res = []
        while allowCourse:
            top = allowCourse.popleft()
            res.append(top)
            for item in adj[top]:
                in_degree[item] -= 1
                if in_degree[item] == 0:
                    allowCourse.append(item)

        if len(res) != numCourses:
            return []
        return res
```
## 684. 冗余连接
树可以看成是一个连通且 无环 的 无向 图。

给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。

请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。如果有多个答案，则返回数组 edges 中最后出现的边。

 

示例 1：
```
输入: edges = [[1,2], [1,3], [2,3]]
输出: [2,3]
```
示例 2：


```
输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
输出: [1,4]
```
***
#### 思路：

***并查集***
并查集分为查找和合并两个功能：
* 查找：查找当前节点的代表节点
* 合并：合并两个节点所在的集合

```
class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        parent = list(range(n + 1))

        def find(index: int) -> int:
            if parent[index] != index:
                parent[index] = find(parent[index])
            return parent[index]
        
        def union(index1: int, index2: int):
            parent[find(index1)] = find(index2)

        for node1, node2 in edges:
            if find(node1) != find(node2):
                union(node1, node2)
            else:
                return [node1, node2]   
                    
        return []
```
