#include "signin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Signin w;
    w.show();
    return a.exec();
}
