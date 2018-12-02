//
// Created by nigao on 12/1/18.
//

#include "graph.h"

Graph::~Graph()
{
    for (vector<EdgeNode*>::iterator it = Edges.begin(); it != Edges.end(); it++)
    {
        delete (*it);
    }
}

void Graph::addVertex(string name)
{
    Vertexes.push_back(VertexNode(Vertexes.size()+ 1, name, NULL));
}

void Graph::addEdge(const int& v1, const int& v2, const int& dis)
{
    int size = Vertexes.size();
    if (size < v1 || size < v2)
    {
        cout << "No such vertex!" << endl;
        return;
    }
    EdgeNode* temp = new EdgeNode(0, dis, v1, v2, NULL, NULL);

    temp->path1 = Vertexes[v1].Edge;
    Vertexes[v1].Edge = temp;

    temp->path2 = Vertexes[v2].Edge;
    Vertexes[v2].Edge = temp;

    Edges.push_back(temp);
}


void Graph::BFS(const int &start)
{
    queue<int> Q;
    Q.push(start);
    int temp=-1;
    int size = Vertexes.size();

    bool *visited = new bool[size];
    bool *appeared=new bool[size];
    memset(visited, 0, sizeof(bool)*size);
    memset(appeared, 0, sizeof(bool)*size);

    TreeNode* TreeNodes=new  TreeNode[size];
    int kid;

    EdgeNode* edge;
    while (!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        if (visited[temp])
        {
            continue;
        }

        visited[temp]=1;
        cout << Vertexes[temp].location << endl;
        edge = Vertexes[temp].Edge;
        while (edge)
        {
            kid=-1;
            if (edge->vertex1 == temp)
            {
                kid=edge->vertex2;
                Q.push(kid);
                edge = edge->path1;
            }
            else if (edge->vertex2 == temp)
            {
                kid=edge->vertex1;
                Q.push(kid);
                edge = edge->path2;
            }
            if(kid>=0&&!appeared[kid]&&!visited[kid])
            {
                TreeNodes[kid].parent=temp;
                TreeNodes[temp].children.push_back(kid);
                appeared[kid]=1;
            }
        }
    }
    createGraph(TreeNodes);
    delete[]visited;
    delete[]TreeNodes;
    delete[]appeared;
}

void Graph::resetMark()
{
    int size = Edges.size();
    for (int i = 0; i < size; i++)
    {
        Edges[i]->mark = 0;
    }
}

void Graph::createGraph(const TreeNode *TreeNodes)
{
    int size=Vertexes.size();
    string filename="/home/nigao/Documents/Graph/SpanningTree.dot";
    fstream fs(filename,fstream::out);
    fs<<"digraph G {";
    fs<<"edge[color=blue];\n";
    for(int i=0;i<size;i++)
    {

        fs<<i<<" [label=\""<<Vertexes[i].location<<"\"];\n";
    }

    int KidsNum;
//    bool *appeared=new bool[size];
//    memset(appeared,0,sizeof(bool)*size);
    for(int i=0;i<size;i++)
    {
        KidsNum=TreeNodes[i].children.size();
        for(int j=0;j<KidsNum;j++)
        {
//            if(!appeared[TreeNodes[i].children[j]])
            {
                fs<<i<<" -> "<<TreeNodes[i].children[j]<<";\n";
//                appeared[TreeNodes[i].children[j]]=1;
            }
        }
    }
    fs<<"}\n";
    fs.close();
    system("dot -Tsvg /home/nigao/Documents/Graph/SpanningTree.dot\
           -o /home/nigao/Documents/Graph/SpanningTree.svg");
    system("eog /home/nigao/Documents/Graph/SpanningTree.svg");
//    delete []appeared;
}

void Graph::DFS(const int &start)
{
    stack<int> S;
    S.push(start);

    int temp;
    int size=Vertexes.size();
    bool *visited=new bool[size];
    TreeNode* TreeNodes=new TreeNode[size];
    memset(visited,0,sizeof(bool)*size);
    bool allVisited;
    EdgeNode* edge;

    while(!S.empty())
    {
        temp=S.top();
        allVisited=1;
        if(!visited[temp])
        {
            visited[temp]=1;
            cout<<Vertexes[temp].location<<endl;
        }
        edge=Vertexes[temp].Edge;
        while(edge)
        {
            if(edge->vertex1==temp)
            {
                if(!visited[edge->vertex2])
                {
                    TreeNodes[temp].children.push_back(edge->vertex2);
                    S.push(edge->vertex2);
                    allVisited=0;
                    break;
                }
                edge=edge->path1;
            }
            else if(edge->vertex2==temp)
            {
                if(!visited[edge->vertex1])
                {
                    S.push(edge->vertex1);
                    TreeNodes[temp].children.push_back(edge->vertex1);
                    allVisited=0;
                    break;
                }
                edge=edge->path2;
            }
        }
        if(allVisited)
        {
            S.pop();
        }
    }
    createGraph(TreeNodes);
    delete[]TreeNodes;
    delete[]visited;
}
