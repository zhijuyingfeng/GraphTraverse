//
// Created by nigao on 12/1/18.
//

#ifndef CLIONAPPLICATION3_GRAPH_H
#define CLIONAPPLICATION3_GRAPH_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <fstream>
using namespace std;

struct EdgeNode
{
    bool mark;//标记该边是否被访问过
    int distance;//该边权值
    int vertex1, vertex2;//该边的两个顶点
    EdgeNode* path1 ;//依附顶点vertex1的下一条边
    EdgeNode *path2;//依附顶点vertex2的下一条边
    EdgeNode():mark(0),distance(-1),vertex1(-1),vertex2(-1),path1(NULL),path2(NULL){}
    EdgeNode(const int &m,const int& dis,const int &v1,const int &v2,EdgeNode* p1,EdgeNode* p2):\
                            mark(m),distance(dis),vertex1(v1),vertex2(v2),path1(p1),path2(p2){}
};

struct VertexNode
{
    int Num;//顶点序号
    string location;//城市名称
    EdgeNode *Edge;//依附该顶点的第一条边
    VertexNode():Num(-1),location(NULL),Edge(NULL){}
    VertexNode(const int &N,const string&l,EdgeNode* E):Num(N),location(l),Edge(E){}
};

struct TreeNode//可视化生成树时使用，为生成树的顶点
{
    int parent;//父节点序号
    vector<int> children;//孩子节点序号
    TreeNode():parent(-1){}
    TreeNode(const int &p):parent(p){}
};

class Graph
{
private:
    vector<VertexNode> Vertexes;//图的顶点集合
    vector<EdgeNode*>Edges;//图的边集
    void createGraph(const TreeNode* TreeNodes);//创建可视化的生成树

public:
    ~Graph();
    void addVertex( string name);//向图中添加节点
    void addEdge(const int& v1, const int& v2, const int& dis);//向图中添加边
    void BFS(const int& start);//广度优先搜索
    void DFS(const int& start);//深度优先搜索
    void resetMark();//将边的mark位为重置为0
};

#endif //CLIONAPPLICATION3_GRAPH_H