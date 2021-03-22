#include "sudoku.h"
#include "ui_sudoku.h"
#include <QIntValidator>
#include <QObject>
#include <QVector>
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
    QVector<QVector<int>> matrix = get_content();
    //DEBUG CHECKS
        bool r = check_row(matrix,5);
        bool c = check_column(matrix,5);
        bool s = check_sector(matrix,5);

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

        QVector<QVector<int>> test;
        for(int c = 0; c < 9; c++){
            QVector<int> row;
            for(int d = 0; d < 9; d++)
                row.append(4);
            test.append(row);
        }

        set_content(test);
    //FINE DEBUG////////
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
    int idx = n;
    int res = 0;

    if(idx < 3){
        res = idx;
    } else if(idx >= 3 && idx < 6){
        res = idx+1;
    } else if(idx >= 6){
        res = idx+2;
    }

    return res;
}

//controlla che tutte le caselle
//siano state riempite
bool Sudoku::is_full(QVector<QVector<int>> matrix)
{
    QVectorIterator<QVector<int>> iter(matrix);
    while(iter.hasNext()){
        if(iter.next().contains(0))
            return false;
    }
    return true;
}

//controllo che nella riga non ci siano
//elementi ripetuti tranne lo 0 (row da 1 a 9)
bool Sudoku::check_row(QVector<QVector<int>> matrix, int row)
{
    QVector<int> vect = matrix[row];
    for(int c = 1; c <= 9; c++){
        if(vect.count(c) > 1)
            return false;
    }
    return true;
}

//controllo che nella colonna non ci siano
//elementi ripetuti tranne lo 0 (col da 1 a 9)
bool Sudoku::check_column(QVector<QVector<int>> matrix, int col)
{
    QVector<int> vect;
    QVectorIterator<QVector<int>> iter(matrix);
    while(iter.hasNext()){
        vect.append(iter.next()[col]);
    }

    for(int c = 1; c <= 9; c++){
        if(vect.count(c) > 1)
            return false;
    }
    return true;
}

//controlla che non ci siano elementi
//ripetuti nel settore 3x3 definito tramite
//una variabile intera da 1 a 9
bool Sudoku::check_sector(QVector<QVector<int>> matrix, int sect)
{
    int row = ((sect-1)/3)*3;
    int col = ((sect-1)%3)*3;
    int count = 0;
    QVector<QVector<int>> submatrix;

    //settore di controllo
    for(int c = row; c <= row+2; c++){
        QVector<int> row;
        for(int d = col; d <= col+2; d++){
            row.append(matrix[c][d]);
        }
        submatrix.append(row);
    }

    //intercetto duplicati
    for(int b = 1; b <= 9; b++){
        count = 0;
        for(int c = 0; c < 3; c++){
            for(int d = 0; d < 3; d++){
                if(submatrix[c][d] == b)
                    count++;
            }
        }
        if(count > 1)
            return false;
    }
    return true;
}

//il metodo acquisisce il contenuto
//delle celle del sudoku in una matrice
//9x9
QVector<QVector<int>> Sudoku::get_content(){
    QVector<QVector<int>> content;

    for(int c = 0; c <= 10; c++){
        if(c != 3 && c != 7){
            QVector<int> row;
            for(int d = 0; d <= 10; d++){
                QLayoutItem* item = ui->cellsLayout->itemAtPosition(c,d);
                if(item){
                    QWidget* widget = item->widget();
                    QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
                    if(le){
                        QString val = le->text();
                        int n = (val.isEmpty()) ? 0 : val.toInt();
                        row.append(n);
                    }
                }
            }
            content.append(row);
        }
    }

    return content;
}

//il metodo setta il contenuto di una matrice 9x9
//all'interno dello spazio di gioco
void Sudoku::set_content(QVector<QVector<int>> matrix)
{
    for(int c = 0; c < 9; c++){
        for(int d = 0; d < 9; d++){
            int correct_row = correct_index(c);
            int correct_col = correct_index(d);
            QLayoutItem* item = ui->cellsLayout->itemAtPosition(correct_row,correct_col);
            if(item){
                QWidget* widget = item->widget();
                QLineEdit* le = dynamic_cast<QLineEdit*>(widget);
                if(le){
                    int val = matrix[c][d];
                    QString str = (val == 0) ? "" : QString::number(val);
                    le->setText(str);
                }
            }
        }
    }
}
