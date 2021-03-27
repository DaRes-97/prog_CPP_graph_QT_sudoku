/*
    Resmini Daniele Andrea - MAT: 830446
    Progetto QT - SUDOKU
*/

#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QStack>
#include "ui_sudoku.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Sudoku; }
QT_END_NAMESPACE

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = nullptr);
    ~Sudoku();

private slots:
    void on_solveButton_clicked();

    void on_resetButton_clicked();

    void on_prevButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::Sudoku *ui;

    //salvataggio stadi di risoluzione
    QStack<QVector<QVector<int>>> prev_state;
    QStack<QVector<QVector<int>>> next_state;

    bool solve(QVector<QVector<int>> board);

    //BOX = casella
    //COL = colonna
    //ROW = riga
    //SECT = settore 3x3

    QLineEdit* get_box(int row, int col);
    int correct_box_index(int idx);

    QVector<int> get_col(QVector<QVector<int>> board, int col);
    void set_background_col(int col, bool isred);

    QVector<int> get_row(QVector<QVector<int>> board, int row);
    void set_background_row(int row, bool isred);

    QVector<int> get_sect(QVector<QVector<int>> board, int sect);
    void set_background_sect(int sect, bool isred);

    bool is_board_full(QVector<QVector<int>> board);
    bool check_array(QVector<int> arr);
    bool check_board(QVector<QVector<int>> board);

    QVector<QVector<int>> get_content();
    void set_content(QVector<QVector<int>> board);
};
#endif // SUDOKU_H
