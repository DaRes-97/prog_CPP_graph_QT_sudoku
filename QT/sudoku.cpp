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
    //acquisisco i valori delle celle
    QVector<QVector<int>> matrix = get_content();
    prev.push(matrix);

    //risolvo il sudoku
    bool res = solve();

    //esito della risoluzione
    QString msg;
    msg = res ? "risolto" : "non risolvibile";
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle("Response");
    msgBox.exec();

    //setto lo stato delle componenti
    QVector<QVector<int>> final = prev.pop();
    prev.push(final);
    set_content(final);

    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setEnabled(false);
    }
    ui->solveButton->setEnabled(false);
    if(res){
        ui->nextButton->setEnabled(!next.isEmpty());
        ui->prevButton->setEnabled(!prev.isEmpty());
    }
}

//resetta lo stato iniziale del programma
void Sudoku::on_resetButton_clicked()
{
    prev.empty();
    next.empty();
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setText("");
        le->setEnabled(true);
    }
    ui->solveButton->setEnabled(true);
    ui->prevButton->setEnabled(false);
    ui->nextButton->setEnabled(false);
}

//torna indietro di un passo nella risoluzione
void Sudoku::on_prevButton_clicked()
{
    QVector<QVector<int>> matrix = prev.pop();
    next.push(matrix);

    set_content(matrix);

    ui->nextButton->setEnabled(!next.isEmpty());
    ui->prevButton->setEnabled(!prev.isEmpty());
}

//va avanti di un passo nella risoluzione
void Sudoku::on_nextButton_clicked()
{
    QVector<QVector<int>> matrix = next.pop();
    prev.push(matrix);

    set_content(matrix);

    ui->nextButton->setEnabled(!next.isEmpty());
    ui->prevButton->setEnabled(!prev.isEmpty());
}

//risolve il sudoku con la tecnica del backtracking
//salvando tutti gli stati intermedi
bool Sudoku::solve(){
    QVector<QVector<int>> matrix = prev.pop();

    if(!check_grid(matrix)){
        prev.push(matrix);
        return false;
    }

    if(is_full(matrix)){

        prev.push(matrix);
        return check_grid(matrix);

    } else {
        int col = 0;
        int row = 0;
        for(int c = 0; c < 9; c++){
            for(int d = 0; d < 9; d++){
                if(matrix[c][d] == 0){
                    row = c;
                    col = d;
                }
            }
        }
        for(int c = 1; c <= 9; c++){
            matrix[row][col] = c;
            if(check_grid(matrix)){
                prev.push(matrix);
                if(solve()){
                    return true;
                }
            }
        }

        prev.push(matrix);
        return false;
    }
}

//ritorna la colonna indicata
QVector<int> Sudoku::col(QVector<QVector<int>> matrix, int col)
{
    QVector<int> vect;
    QVectorIterator<QVector<int>> iter(matrix);
    while(iter.hasNext()){
        vect.append(iter.next()[col]);
    }

    return vect;
}

//ritorna la riga indicata
QVector<int> Sudoku::row(QVector<QVector<int>> matrix, int row)
{
    QVector<int> vect = matrix[row];
    return vect;
}

//ritorna il settore indicato
QVector<int> Sudoku::sect(QVector<QVector<int>> matrix, int sect)
{
    int row = ((sect-1)/3)*3;
    int col = ((sect-1)%3)*3;
    QVector<int> vect;

    //settore di controllo
    for(int c = row; c <= row+2; c++){
        for(int d = col; d <= col+2; d++){
            vect.append(matrix[c][d]);
        }
    }

    return vect;
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

//controlla se ci sono duplicati nell'array
bool Sudoku::check_array(QVector<int> vect)
{
    for(int c = 1; c <= 9; c++){
        if(vect.count(c) > 1)
            return false;
    }
    return true;
}

//controlla se ci sono duplicati nel campo gioco
bool Sudoku::check_grid(QVector<QVector<int>> matrix)
{
    for(int c = 0; c < 9; c++){
        QVector<int> c_row = row(matrix, c);
        QVector<int> c_col = col(matrix, c);
        QVector<int> c_sect = sect(matrix, c+1);

        if(!check_array(c_row) || !check_array(c_col) || !check_array(c_sect)){
            return false;
        }
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
