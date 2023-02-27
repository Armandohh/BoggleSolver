#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QValidator>
#include "Boggle.h"
#include <string>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void buildBoard(string board[BOARD_SIZE][BOARD_SIZE]);
public slots:
    void checkLineEdits();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
