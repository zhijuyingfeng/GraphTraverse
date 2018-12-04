//
// Created by nigao on 12/1/18.
//

#include "graph.h"

Graph::~Graph()//析构函数
{
    //释放边集内存
    for (vector<EdgeNode*>::iterator it = Edges.begin(); it != Edges.end(); it++)
    {
        delete (*it);
    }
}

void Graph::addVertex(string name)
{
    Vertexes.push_back(VertexNode(Vertexes.size()+ 1, name, NULL));//将顶点加入到顶点集中
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

    //类似于在链表头部插入节点
    temp->path1 = Vertexes[v1].Edge;
    Vertexes[v1].Edge = temp;

    temp->path2 = Vertexes[v2].Edge;
    Vertexes[v2].Edge = temp;

    Edges.push_back(temp);//将该边加入到边集中
}


void Graph::BFS(const int &start)
{
    queue<int> Q;//遍历队列
    Q.push(start);//初始节点入队
    int temp=-1;//表示当前遍历的节点
    int size = Vertexes.size();//全部连通的节点数

    bool *visited = new bool[size];//标志节点是否被访问过
    bool *appeared=new bool[size];//标志节点是否进过队列
    memset(visited, 0, sizeof(bool)*size);
    memset(appeared, 0, sizeof(bool)*size);

    TreeNode* TreeNodes=new  TreeNode[size];//表示生成树
    int kid;//表示正在遍历的节点的孩子节点

    EdgeNode* edge;//依附于该节点的边
    while (!Q.empty())
    {
        temp = Q.front();
        Q.pop();
        if (visited[temp])//该节点已经被访问过时跳过后面步骤
        {
            continue;
        }

        visited[temp]=1;
        cout << Vertexes[temp].location << endl;//访问节点
        edge = Vertexes[temp].Edge;//edge指向依附该节点的第一条边
        while (edge)
        {
            kid=-1;

            //判断边的哪个端点是目前访问的节点
            if (edge->vertex1 == temp)//该边的vertex1是目前访问的端点
            {
                kid=edge->vertex2;
                Q.push(kid);
                edge = edge->path1;
            }
            else if (edge->vertex2 == temp)//该边的vertex2是目前访问的端点
            {
                kid=edge->vertex1;
                Q.push(kid);
                edge = edge->path2;
            }
            if(kid>=0&&!appeared[kid]&&!visited[kid])
            {
                //构建顶点之间的关系
                TreeNodes[kid].parent=temp;
                TreeNodes[temp].children.push_back(kid);
                appeared[kid]=1;
            }
        }
    }
    //利用TreeNodes构建可视化生成树
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
    stack<int> S;//访问栈
    S.push(start);//初始节点入栈

    int temp;//当前正在访问的节点序号
    int size=Vertexes.size();//全部连通的节点数
    bool *visited=new bool[size];//标志该节点是否被访问过
    TreeNode* TreeNodes=new TreeNode[size];//生成树
    memset(visited,0,sizeof(bool)*size);
    bool allVisited;//标志依附于该节点的边是否全部访问完毕
    EdgeNode* edge;//依附于该节点的边

    while(!S.empty())
    {
        temp=S.top();//当前访问节点出栈
        allVisited=1;//每次循环开始时设置其为1
        if(!visited[temp])//若没有访问过该节点，则访问
        {
            visited[temp]=1;
            cout<<Vertexes[temp].location<<endl;
        }
        edge=Vertexes[temp].Edge;//指向依附于该节点的第一条边
        while(edge)
        {
            //判断边的哪个端点是目前访问的节点
            if(edge->vertex1==temp)//该边的vertex1是目前访问的端点
            {
                //如果没有访问过，将其入栈
                if(!visited[edge->vertex2])
                {
                    TreeNodes[temp].children.push_back(edge->vertex2);
                    S.push(edge->vertex2);
                    allVisited=0;//因为存在没有访问过的节点，allVisited置0
                    break;
                }
                edge=edge->path1;
            }
            else if(edge->vertex2==temp)
            {
                if(!visited[edge->vertex1])//该边的vertex2是目前访问的端点
                {
                    S.push(edge->vertex1);
                    TreeNodes[temp].children.push_back(edge->vertex1);
                    allVisited=0;
                    break;
                }
                edge=edge->path2;
            }
        }
        if(allVisited)//如果依附于该节点的所有边全部已经访问过，将该节点出栈
        {
            S.pop();
        }
    }
    createGraph(TreeNodes);
    delete[]TreeNodes;
    delete[]visited;
}