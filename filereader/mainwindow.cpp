#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList arr;

void MainWindow::on_browse_clicked()
{
    QString fileDialog = QFileDialog::getOpenFileName(this,tr("Seleccionar archivo de registro"),"",tr("TXT(*.txt)"));
    ui->exp->setEnabled(false);
    ui->textEdit->setText("");
    if (fileDialog.isEmpty())
    {
        ui->browse->setText("Import a new file");
        ui->content->setText("");
        ui->sort->setEnabled(false);
        arr.clear();
        return;
    }

    QFile file(fileDialog);
    QFileInfo fileInfo(fileDialog);
    ui->browse->setText(fileInfo.fileName() + " was imported");
    ui->content->setText("Unordered File Content");

    arr.clear();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            arr.push_back(str);
        }
    }
    for (int i = 0; i < arr.size(); i++) {
        ui->textEdit->setText(ui->textEdit->toPlainText()+arr.value(i));
    }
    file.close();
    ui->sort->setEnabled(true);
}

void MainWindow::on_sort_clicked()
{
    arr.sort(Qt::CaseInsensitive);
    ui->textEdit->setText("");
    for (int i = 0; i < arr.size(); i++) {
        ui->textEdit->setText(ui->textEdit->toPlainText()+arr.value(i));
    }
    ui->content->setText("Ordered File Content");
    ui->exp->setEnabled(true);
}

void MainWindow::on_exp_clicked()
{
    QString fileDialog = QFileDialog::getSaveFileName(this,tr("Guarda archivo de registro"),"",tr("TXT(*.txt)"));
    if (fileDialog.isEmpty()) return;
    QFile file(fileDialog);
    QFileInfo fileInfo(fileDialog);
    QTextStream qout(&file);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        for (int i = 0; i < arr.length(); i++) {
            qout << arr.value(i);
        }
    }
    ui->browse->setText(fileInfo.fileName() + " was exported");
}

