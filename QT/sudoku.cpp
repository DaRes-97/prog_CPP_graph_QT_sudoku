/*
    Resmini Daniele Andrea - MAT: 830446
    Progetto QT - SUDOKU
*/

#include "sudoku.h"
#include "ui_sudoku.h"
#include <QRegularExpressionValidator>
#include <QObject>
#include <QVector>
#include <QMessageBox>

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku)
{
    ui->setupUi(this);

    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        //inibisco input lettere e simboli ed escludo lo zero
        le->setValidator(new QRegularExpressionValidator(QRegularExpression("[1-9]"),this));
        le->setMaxLength(1);

        //disattivo tasto SOLVE con sudoku vuoto
        connect(le, SIGNAL(textChanged(const QString)), this, SLOT(on_text_changed()));
    }

    on_resetButton_clicked();
}

Sudoku::~Sudoku()
{
    prev_state.clear();
    next_state.clear();
    initial_state.clear();
    delete ui;
}

//disattiva tasto SOLVE con sudoku vuoto
void Sudoku::on_text_changed(){
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        if(!le->text().isEmpty()){
            ui->solveButton->setEnabled(true);
            return;
        }
    }

    ui->solveButton->setEnabled(false);
}

void Sudoku::on_solveButton_clicked()
{
    //acquisisco i valori delle celle
    QVector<QVector<int>> board = get_content();

    //setto lo stato iniziale
    for(int c = 0; c < 9; c++){
        QVector<bool> row;
        for(int d = 0; d < 9; d++){
            row.append(board[c][d] != 0);
        }
        initial_state.append(row);
    }

    //risolvo il sudoku
    bool res = solve(board);
    next_state.push(board);
    while(!next_state.isEmpty())
        prev_state.push(next_state.pop());

    //esito della risoluzione
    QString msg;
    msg = res ? "Sudoku risolto" : "Sudoku non risolvibile";
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.setWindowTitle("Response");
    msgBox.exec();

    //setto lo stato delle componenti
    QVector<QVector<int>> final = prev_state.pop();
    prev_state.push(final);
    set_content(final);

    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setReadOnly(true);
    }
    ui->solveButton->setEnabled(false);
    if(res){
        ui->nextButton->setEnabled(!next_state.isEmpty());
        ui->prevButton->setEnabled(!prev_state.isEmpty());
    }
}

//resetta lo stato iniziale del programma
void Sudoku::on_resetButton_clicked()
{
    //svuoto le stack
    prev_state.clear();
    next_state.clear();
    initial_state.clear();

    //riporto il widget allo stato iniziale
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->setText("");
        le->setReadOnly(false);
        le->setStyleSheet("QLineEdit { background: rgb(255, 255, 255);"
                        "color: black }");
    }
    ui->solveButton->setEnabled(true);
    ui->prevButton->setEnabled(false);
    ui->nextButton->setEnabled(false);
    ui->solveButton->setEnabled(false);
}

//torna indietro di un passo nella risoluzione
void Sudoku::on_prevButton_clicked()
{
    QVector<QVector<int>> board = prev_state.pop();
    next_state.push(board);

    set_content(board);

    ui->nextButton->setEnabled(!next_state.isEmpty());
    ui->prevButton->setEnabled(!prev_state.isEmpty());
}

//va avanti di un passo nella risoluzione
void Sudoku::on_nextButton_clicked()
{
    QVector<QVector<int>> board = next_state.pop();
    prev_state.push(board);

    set_content(board);

    ui->nextButton->setEnabled(!next_state.isEmpty());
    ui->prevButton->setEnabled(!prev_state.isEmpty());
}

//risolve il sudoku con la tecnica del backtracking
//salvando gli stati intermedi
bool Sudoku::solve(QVector<QVector<int>> board)
{
    //nessuna scelta possibile
    if(is_board_full(board)){
        return check_board(board);
    }

    QVector<QVector<int>> new_board = board;

    //trovo prossima cella libera
    int new_row = 0;
    int new_col = 0;
    bool found = false;
    for(int c = 0; c < 9 && !found; c++){
        for(int d = 0; d < 9 && !found; d++){
            if(new_board[c][d] == 0){
                new_row = c;
                new_col = d;
                found = true;
            }
        }
    }

    for(int c = 1; c <= 9; c++){

        //provo scelta c
        new_board[new_row][new_col] = c;

        //scelta c è safe
        if(check_board(new_board)){

            //la matrice è risolvibile con la scelta c
            if(solve(new_board)){
                next_state.push(new_board);
                return true;
            }
        }

        //la matrice non è risolvibile con la scelta c
        new_board[new_row][new_col] = 0;
    }

    //non ci sono soluzioni
    return false;
}

//colora la colonna selezionata di rosso
void Sudoku::set_red_background_col(int col)
{
    QString style;

    style = "QLineEdit { background: rgb(255, 150, 150) }";
    for(int d = 0; d < 9; d++){
        QLineEdit* le = get_box(d,col);
        le->setStyleSheet(style);
    }
}

//ritorna la colonna indicata dalla matrice
QVector<int> Sudoku::get_col(QVector<QVector<int>> board, int col)
{
    QVector<int> vect;
    QVectorIterator<QVector<int>> iter(board);
    while(iter.hasNext()){
        vect.append(iter.next()[col]);
    }

    return vect;
}

//colora la riga selezionata di rosso
void Sudoku::set_red_background_row(int row)
{
    QString style;

    style = "QLineEdit { background: rgb(255, 150, 150) }";
    for(int d = 0; d < 9; d++){
        QLineEdit* le = get_box(row,d);
        le->setStyleSheet(style);
    }
}

//ritorna la riga indicata dalla matrice
QVector<int> Sudoku::get_row(QVector<QVector<int>> board, int row)
{
    QVector<int> vect = board[row];
    return vect;
}

//colora il settore 3x3 selezionato di rosso
void Sudoku::set_red_background_sect(int sect)
{
    int row = ((sect-1)/3)*3;
    int col = ((sect-1)%3)*3;
    QString style;

    style = "QLineEdit { background: rgb(255, 150, 150) }";
    for(int c = row; c <= row+2; c++){
        for(int d = col; d <= col+2; d++){
            QLineEdit* le = get_box(c,d);
            le->setStyleSheet(style);
        }
    }
}

//ritorna il settore 3x3 indicato dalla matrice
QVector<int> Sudoku::get_sect(QVector<QVector<int>> board, int sect)
{
    int row = ((sect-1)/3)*3;
    int col = ((sect-1)%3)*3;
    QVector<int> vect;

    //settore di controllo
    for(int c = row; c <= row+2; c++){
        for(int d = col; d <= col+2; d++){
            vect.append(board[c][d]);
        }
    }

    return vect;
}

//ritorna il puntatore alla QLineEdit nella
//posizione specificata
QLineEdit* Sudoku::get_box(int row, int col)
{
    int correct_row = correct_box_index(row);
    int correct_col = correct_box_index(col);

    QLayoutItem* item = ui->cellsLayout->itemAtPosition(correct_row,correct_col);
    QWidget* widget = item->widget();
    QLineEdit* le = dynamic_cast<QLineEdit*>(widget);

    return le;
}

//dato l'indice in ingresso relativo
//alla casella della matrice ritorna
//l'indice corretto all'interno del grid layout
//tenendo conto delle linee orizzontali e
//verticali che ho inserito nel layout,
//che occupano una posizione
int Sudoku::correct_box_index(int n)
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
bool Sudoku::is_board_full(QVector<QVector<int>> board)
{
    QVectorIterator<QVector<int>> iter(board);
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
bool Sudoku::check_board(QVector<QVector<int>> board)
{
    for(int c = 0; c < 9; c++){
        QVector<int> c_row = get_row(board, c);
        QVector<int> c_col = get_col(board, c);
        QVector<int> c_sect = get_sect(board, c+1);

        if(!check_array(c_row) || !check_array(c_col) || !check_array(c_sect)){
            return false;
        }
    }

    return true;
}

//il metodo acquisisce il contenuto
//delle celle del sudoku in una matrice
//9x9
QVector<QVector<int>> Sudoku::get_content()
{
    QVector<QVector<int>> content;

    for(int c = 0; c < 9; c++){
        QVector<int> row;

        for(int d = 0; d <9; d++){
            QLineEdit* le = get_box(c,d);
            QString val = le->text();
            int n = (val.isEmpty()) ? 0 : val.toInt();
            row.append(n);
        }

        content.append(row);
    }

    return content;
}

//il metodo setta il contenuto di una matrice 9x9
//all'interno dello spazio di gioco, setta sfondo rosso
//sui settori errati e colora di blu i numeri inseriti
//prima di cliccare il tasto SOLVE
void Sudoku::set_content(QVector<QVector<int>> board)
{

    for(int c = 0; c < 9; c++){
        for(int d = 0; d < 9; d++){
                QLineEdit* le = get_box(c,d);

                int val = board[c][d];
                QString str = (val == 0) ? "" : QString::number(val);

                QString style;
                //setto colore del numero
                if(initial_state[c][d]){
                    style = "QLineEdit { color: blue }";
                } else {
                    style = "QLineEdit { color: black }";
                }

                le->setStyleSheet(style);
                //setto il numero
                le->setText(str);
        }
    }

    //sfondo rosso per settori con duplicati
    for(int c = 0; c < 9; c++){
        if(!check_array(get_row(board,c)))
            set_red_background_row(c);
        if(!check_array(get_col(board,c)))
            set_red_background_col(c);
        if(!check_array(get_sect(board,c+1)))
            set_red_background_sect(c+1);
    }
}
