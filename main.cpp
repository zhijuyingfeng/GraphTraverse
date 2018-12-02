#include "mainwindow.h"
#include <QApplication>

const int cityNum = 25;
const int edgeNum=30;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Graph Traverse");
    const std::string cities[] =
            {
                    "哈尔滨","长春","沈阳","大连","天津","北京","呼和浩特","兰州","乌鲁木齐","西宁",
                    "西安","郑州","徐州","上海","武汉","成都","昆明","贵阳","株洲","南昌","福州","深圳",
                    "广州","柳州","南宁"
            };
    const int edges[][3] =
            {
                    {0,1,242},{1,2,305},{2,3,397},{2,4,704},{4,5,137},{5,6,668},
                    {6,7,1145},{7,8,1892},{4,12,674},{5,11,695},{11,12,349},{10,11,511},
                    {7,10,676},{7,9,216},{12,13,651},{11,14,534},{10,15,842},{15,16,1100},
                    {15,17,967},{14,18,409},{13,19,825},{19,20,622},{18,19,367},{17,18,902},
                    {16,17,639},{17,23,607},{18,23,672},{18,22,675},{21,22,140},{23,24,255}
            };

    for(int i=0;i<cityNum;i++)
    {
        w.addVertex(cities[i]);
    }
    for(int i=0;i<edgeNum;i++)
    {
        w.addEdge(edges[i][0], edges[i][1], edges[i][2]);
    }
    w.show();

    return a.exec();
}
