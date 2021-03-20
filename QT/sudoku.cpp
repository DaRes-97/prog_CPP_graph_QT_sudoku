#include "sudoku.h"
#include "ui_sudoku.h"
#include <QIntValidator>
#include <QObject>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);

    //inibisco input lettere e simboli
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setValidator( new QIntValidator(1, 9, this) );
        le->setMaxLength(1);
    }
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
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setText("");
    }
}

void Sudoku::on_prevButton_clicked()
{

}

void Sudoku::on_nextButton_clicked()
{

}

//la funzione determina se sono presenti
//duplicati nell'array in ingresso, tranne
//lo zero
bool Sudoku::has_duplicates(int* arr)
{
    int count;
    for(int c = 1; c <= 9; c++){
        count = 0;
        for(int d = 0; d < 10; d++){
            if(arr[d] == c)
                count++;
        }
        if(count > 1)
            return false;
    }

    return true;
}

//controllo che nella riga non ci siano
//elementi ripetuti tranne lo 0
bool Sudoku::check_row(int row)
{
    int l[9];

    for(int d = 0; d <= 10; d++){
        QLayoutItem* item = ui->cellsLayout->itemAtPosition(d,row);
        QWidget* widget = item->widget();
        QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
        if(le){
            QString val = le->text();
            l[d] = (val.isEmpty()) ? 0 : val.toInt();
        }
    }

    return has_duplicates(l);
}

//controllo che nella colonna non ci siano
//elementi ripetuti tranne lo 0
bool Sudoku::check_column(int row)
{
    int l[9];

    for(int d = 0; d <= 10; d++){
        QLayoutItem* item = ui->cellsLayout->itemAtPosition(row,d);
        QWidget* widget = item->widget();
        QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
        if(le){
            QString val = le->text();
            l[d] = (val.isEmpty()) ? 0 : val.toInt();
        }
    }

    return has_duplicates(l);
}
