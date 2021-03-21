#include "sudoku.h"
#include "ui_sudoku.h"
#include <QIntValidator>
#include <QObject>
#include <QMessageBox>

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

    on_resetButton_clicked();
}

Sudoku::~Sudoku()
{
    delete ui;
}


void Sudoku::on_solveButton_clicked()
{
    //DEBUG CHECKS
    bool r = check_row(correct_index(5));
    bool c = check_column(correct_index(5));
    bool s = check_sector(5);

    QString msg = "";
    if(r)
        msg.append("row correct/");
    if(c)
        msg.append("col correct/");
    if(s)
        msg.append("sect correct");
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle("Info Message");
    msgBox.exec();
}

void Sudoku::on_resetButton_clicked()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setText("");
    }
    ui->prevButton->setEnabled(false);
    ui->nextButton->setEnabled(false);
}

void Sudoku::on_prevButton_clicked()
{

}

void Sudoku::on_nextButton_clicked()
{

}

//dato l'indice in ingresso relativo
//alla casella ritorna l'indice corretto
//tenendo conto delle linee orizzontali e
//verticali che ho inserito nel layout,
//che occupano una posizione
int Sudoku::correct_index(int n)
{
    int idx = n-1;
    int res = 0;

    if(idx == 3){
        res = 4;
    } else if(idx > 3 && idx < 7){
        res = idx+1;
    } else if (idx == 7){
        res = 8;
    } else if(idx > 7){
        res = idx+2;
    }

    return res;
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

//controlla che tutte le caselle
//siano state riempite
bool Sudoku::is_full()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        QString str = le->text();
        if(str.isEmpty())
            return false;
    }

    return true;
}

//controllo che nella riga non ci siano
//elementi ripetuti tranne lo 0 (row da 1 a 9)
bool Sudoku::check_row(int row)
{
    int l[9];
    int idx = 0;

    for(int d = 0; d <= 10; d++){
        QLayoutItem* item = ui->cellsLayout->itemAtPosition(row,d);
        if(item){
            QWidget* widget = item->widget();
            QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
            if(le){
                QString val = le->text();
                l[idx] = (val.isEmpty()) ? 0 : val.toInt();
                idx++;
            }
        }
    }

    return has_duplicates(l);
}

//controllo che nella colonna non ci siano
//elementi ripetuti tranne lo 0 (col da 1 a 9)
bool Sudoku::check_column(int col)
{
    int l[9];
    int idx = 0;

    for(int d = 0; d <= 10; d++){
        QLayoutItem* item = ui->cellsLayout->itemAtPosition(d,col);
        if(item){
            QWidget* widget = item->widget();
            QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
            if(le){
                QString val = le->text();
                l[idx] = (val.isEmpty()) ? 0 : val.toInt();
                idx++;
            }
        }
    }

    return has_duplicates(l);
}

//controlla che non ci siano elementi
//ripetuti nel settore 3x3 definito tramite
//una variabile intera da 1 a 9
bool Sudoku::check_sector(int sect)
{
    int row = ((sect-1)/3)*4;
    int col = ((sect-1)%3)*4;
    row = correct_index(row);
    col = correct_index(col);
    int l[9];
    int idx = 0;

    for(int c = row; c <= row+2; c++){
        for(int d = col; d <= col+2; d++){
            QLayoutItem* item = ui->cellsLayout->itemAtPosition(c,d);
            if(item){
                QWidget* widget = item->widget();
                QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
                if(le){
                    QString val = le->text();
                    l[idx] = (val.isEmpty()) ? 0 : val.toInt();
                    idx++;
                }
            }
        }
    }

    return has_duplicates(l);
}
