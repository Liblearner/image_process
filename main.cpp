#include "mainwindow.h"		// 生成的窗口类头文件，创建项目时候的根据 class name 生成的
#include <QApplication>		// 应用程序类头文件

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    return a.exec();
}
