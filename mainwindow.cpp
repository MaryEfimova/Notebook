#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Задаём тригер на создание нового файла

void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

//Задаём тригер на открытие файла

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can not open file : " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

//Задаем тригер на сохранение файла

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Can not save file : " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

//Задаём тригер на печать файла

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected){
        QMessageBox::warning(this, "Warning", "Can not Access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

//Задаём тригер на выход из приложения

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

//Задаём тригер на копирование текста

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//Задаём тригер на вставку текста

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//Задаём тригер на вырезание текста

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//Задаём тригер на отмену последнего действия

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//Задаём тригер на восстановление последнего действия

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

