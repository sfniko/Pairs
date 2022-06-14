#include "mainwindow.hh"
#include <QApplication>



#include <player.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
