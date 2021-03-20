#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>

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

    bool has_duplicates(int* arr);
    bool check_row(int row);
    bool check_column(int column);
};
#endif // SUDOKU_H
