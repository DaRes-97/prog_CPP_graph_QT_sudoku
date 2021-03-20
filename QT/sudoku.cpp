#include "sudoku.h"
#include "ui_sudoku.h"
#include <QIntValidator>
#include <QObject>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);
    set_cells();
}

Sudoku::~Sudoku()
{
    delete ui;
}


void Sudoku::on_solveButton_clicked()
{

}

void Sudoku::on_resetButton_clicked()
{

}

void Sudoku::on_prevButton_clicked()
{

}

void Sudoku::on_nextButton_clicked()
{

}

void Sudoku::set_cells(){
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setValidator( new QIntValidator(0, 9, this) );
    }
}
