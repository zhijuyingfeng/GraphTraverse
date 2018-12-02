#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <fstream>
#include <QMessageBox>
#include <QString>

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
    std::string location;//
    EdgeNode *Edge;//
    VertexNode():Num(-1),location(NULL),Edge(NULL){}
    VertexNode(const int &N,const std::string&l,EdgeNode* E):Num(N),location(l),Edge(E){}
};

struct TreeNode
{
    int parent;
    std::vector<int> children;
    TreeNode():parent(-1){}
    TreeNode(const int &p):parent(p){}
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::string str;

private:
    std::vector<VertexNode> Vertexes;
    std::vector<EdgeNode*>Edges;
    void createGraph(const TreeNode* TreeNodes);

public:
//    ~Graph();
    void addVertex( std::string name);
    void addEdge(const int& v1, const int& v2, const int& dis);
    void BFS(const int& start);
    void DFS(const int& start);
    void resetMark();
private slots:
    void on_BFS_clicked();
    void on_DFS_clicked();
};

#endif // MAINWINDOW_H
