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
    bool mark;//
    int distance;//
    int vertex1, vertex2;//
    EdgeNode* path1 ;//
    EdgeNode *path2;//
    EdgeNode():mark(0),distance(-1),vertex1(-1),vertex2(-1),path1(NULL),path2(NULL){}
    EdgeNode(const int &m,const int& dis,const int &v1,const int &v2,EdgeNode* p1,EdgeNode* p2):\
							mark(m),distance(dis),vertex1(v1),vertex2(v2),path1(p1),path2(p2){}
};

struct VertexNode
{
    int Num;//
    string location;//
    EdgeNode *Edge;//
    VertexNode():Num(-1),location(NULL),Edge(NULL){}
    VertexNode(const int &N,const string&l,EdgeNode* E):Num(N),location(l),Edge(E){}
};

struct TreeNode
{
    int parent;
    vector<int> children;
    TreeNode():parent(-1){}
    TreeNode(const int &p):parent(p){}
};

class Graph
{
private:
    vector<VertexNode> Vertexes;
    vector<EdgeNode*>Edges;
    void createGraph(const TreeNode* TreeNodes);

public:
    ~Graph();
    void addVertex( string name);
    void addEdge(const int& v1, const int& v2, const int& dis);
    void BFS(const int& start);
    void DFS(const int& start);
    void resetMark();
};

#endif //CLIONAPPLICATION3_GRAPH_H
