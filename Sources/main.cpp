#include "AnnoTool.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon"));
    AnnoTool w;
    w.show();
    return a.exec();
}
