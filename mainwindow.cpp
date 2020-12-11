#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QDir>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QInputDialog>

#include <iostream>
#include <fstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mousePressed(false)
{
    ui->setupUi(this);

    //assume the directory exists and contains some files and you want all jpg and JPG files
    QDir directory("Data");
    QStringList shits = directory.entryList(QStringList() << "*.txt" << "*.TXT", QDir::Files);
    foreach(QString filename, shits) {
        ui->listWidget->addItem(filename);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos  = event->pos();
        mousePressed = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        mousePressed = false;
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed) {
        QMouseEvent *moveMouseEvent = static_cast<QMouseEvent *>(event);
        move(pos() + moveMouseEvent->pos() - startPos);
    }
}

void MainWindow::loadTextEditor()
{
    ui->widget->hide();
    auto textEditor = new QTextEdit();
    textEditor->setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    textEditor->setFrameShape(QTextEdit::NoFrame);
    textEditor->setStyleSheet("background: rgb(234, 234, 234)");
    textEditor->setFont (QFont ("Arial", 10));
    ui->centralwidget->layout()->addWidget(textEditor);
    m_textEditor = textEditor;
}



void MainWindow::on_close_pushButton_clicked()
{
      this->close();
}

void MainWindow::on_tri_pushButton_clicked()
{
    setWindowState(Qt::WindowState::WindowMinimized);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    loadTextEditor();
    auto name = item->text();
    std::ifstream fin(std::string("data/") + name.toStdString());
    auto content = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    m_textEditor->setText(content.c_str());
}

void MainWindow::on_topHint_pushButton_clicked()
{

    if (windowFlags() & Qt::WindowStaysOnTopHint) {
        setWindowFlag(Qt::WindowStaysOnTopHint, false);
    }
    else {
        setWindowFlag(Qt::WindowStaysOnTopHint);
    }

    show();
}

void MainWindow::on_createNew_pushButton_clicked()
{
    bool ok;
    auto fileName = QInputDialog::getText(this, tr("New sheet"), tr("Name:"), QLineEdit::Normal, nullptr, &ok);
    if (ok && !fileName.isEmpty()){

        loadTextEditor();
    }

}

void MainWindow::on_home_pushButton_clicked()
{
    if (m_textEditor) {
        m_textEditor->hide();
        ui->widget->show();
    }
}
