#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MazeWidget mazeWidget;
    mazeWidget.show();

    return a.exec();
}
