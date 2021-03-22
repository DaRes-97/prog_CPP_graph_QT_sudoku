#include "sudoku.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/sudoku_icon.ico"));
    Sudoku w;
    w.show();
    return a.exec();
}
