#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>


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



void MainWindow::on_close_pushButton_clicked()
{
      this->close();
}

void MainWindow::on_tri_pushButton_clicked()
{
    setWindowState(Qt::WindowState::WindowMinimized);
}
