#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Boggle.cpp"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //limit line edits to only alphabet characters
    QRegularExpression rx ("[a-z]+");
    QValidator *validator = new QRegularExpressionValidator (rx, this);

    ui->lineEdit->setValidator(validator);
    ui->lineEdit_2->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);
    ui->lineEdit_4->setValidator(validator);
    ui->lineEdit_5->setValidator(validator);
    ui->lineEdit_6->setValidator(validator);
    ui->lineEdit_7->setValidator(validator);
    ui->lineEdit_8->setValidator(validator);
    ui->lineEdit_9->setValidator(validator);
    ui->lineEdit_10->setValidator(validator);
    ui->lineEdit_11->setValidator(validator);
    ui->lineEdit_12->setValidator(validator);
    ui->lineEdit_13->setValidator(validator);
    ui->lineEdit_14->setValidator(validator);
    ui->lineEdit_15->setValidator(validator);
    ui->lineEdit_16->setValidator(validator);

    //connect the line edits to the checkLineEdits slot
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_2, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_3, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_4, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_5, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_6, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_7, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_8, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_9, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_10, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_11, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_12, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_13, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_14, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_15, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
    connect(ui->lineEdit_16, SIGNAL(textEdited(QString)), this, SLOT(checkLineEdits()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Boggle boggle;
    string board[BOARD_SIZE][BOARD_SIZE];
    buildBoard(board);
    boggle.SetBoard(board);

    // Output to a file.  Notice we pass in a file.
    ofstream solveOutput;
    solveOutput.open("solvedBoard.txt");
    boggle.SolveBoard(true, solveOutput);
    solveOutput.close();

    //Open as a QFile to output to UI Text Browser
    ui->stackedWidget->setCurrentIndex(1);
    QFile file ("solvedBoard.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());

    solveOutput.close();

}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::checkLineEdits() {
    bool on = !ui->lineEdit->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_3->text().isEmpty() && !ui->lineEdit_4->text().isEmpty() &&
            !ui->lineEdit_5->text().isEmpty() && !ui->lineEdit_6->text().isEmpty() && !ui->lineEdit_7->text().isEmpty() && !ui->lineEdit_8->text().isEmpty() &&
            !ui->lineEdit_9->text().isEmpty() && !ui->lineEdit_10->text().isEmpty() && !ui->lineEdit_11->text().isEmpty() && !ui->lineEdit_12->text().isEmpty() &&
            !ui->lineEdit_13->text().isEmpty() && !ui->lineEdit_14->text().isEmpty() && !ui->lineEdit_15->text().isEmpty() && !ui->lineEdit_16->text().isEmpty();

    ui->pushButton->setEnabled(on);
}

void MainWindow::buildBoard(string board[BOARD_SIZE][BOARD_SIZE]) {

    board[0][0] = ui->lineEdit->text().toStdString();
    board[0][1] = ui->lineEdit_2->text().toStdString();
    board[0][2] = ui->lineEdit_3->text().toStdString();
    board[0][3] = ui->lineEdit_4->text().toStdString();

    board[1][0] = ui->lineEdit_5->text().toStdString();
    board[1][1] = ui->lineEdit_6->text().toStdString();
    board[1][2] = ui->lineEdit_7->text().toStdString();
    board[1][3] = ui->lineEdit_8->text().toStdString();

    board[2][0] = ui->lineEdit_9->text().toStdString();
    board[2][1] = ui->lineEdit_10->text().toStdString();
    board[2][2] = ui->lineEdit_11->text().toStdString();
    board[2][3] = ui->lineEdit_12->text().toStdString();

    board[3][0] = ui->lineEdit_13->text().toStdString();
    board[3][1] = ui->lineEdit_14->text().toStdString();
    board[3][2] = ui->lineEdit_15->text().toStdString();
    board[3][3] = ui->lineEdit_16->text().toStdString();
}
