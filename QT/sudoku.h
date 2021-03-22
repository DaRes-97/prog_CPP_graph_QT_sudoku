#ifndef SUDOKU_H
#define SUDOKU_H

#include <QMainWindow>
#include <QList>

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
    QList<int**> states; //stadi di risoluzione

    int correct_index(int idx);
    bool is_full(QVector<QVector<int>> matrix);
    bool check_row(QVector<QVector<int>> matrix, int row);
    bool check_column(QVector<QVector<int>> matrix, int column);
    bool check_sector(QVector<QVector<int>> matrix, int sector);
    QVector<QVector<int>> get_content();
    void set_content(QVector<QVector<int>> matrix);
};
#endif // SUDOKU_H
