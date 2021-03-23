#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QStack>

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
    QStack<QVector<QVector<int>>> prev;
    QStack<QVector<QVector<int>>> next;

    bool solve(QVector<QVector<int>> matrix, int row, int col);

    int correct_index(int idx);

    QVector<int> get_col(QVector<QVector<int>> matrix, int col);
    void back_col(int col, bool isred);
    QVector<int> get_row(QVector<QVector<int>> matrix, int row);
    void back_row(int row, bool isred);
    QVector<int> get_sect(QVector<QVector<int>> matrix, int sect);
    void back_sect(int sect, bool isred);

    bool is_full(QVector<QVector<int>> matrix);
    bool check_array(QVector<int> arr);
    bool check_grid(QVector<QVector<int>> matrix);
    QVector<QVector<int>> get_content();
    QVector<QVector<int>> init_content(int n);
    void set_content(QVector<QVector<int>> matrix);
};
#endif // SUDOKU_H
