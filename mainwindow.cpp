#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QDir>
#include <QListWidgetItem>
#include <QTextEdit>
#include <QInputDialog>
#include <QShortcut>
#include <QTimer>
#include <QMessageBox>

#include <iostream>
#include <fstream>

#include "safetexteditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mousePressed(false)
{
    ui->setupUi(this);

    m_textEditor = new SafeTextEditor();
    m_textEditor->hide();
    ui->centralwidget->layout()->addWidget(m_textEditor);

    updateList();

    keyEsc = new QShortcut(this);
    keyEsc->setKey(Qt::Key_Escape);
    connect(keyEsc, &QShortcut::activated, this, &MainWindow::keyEsc_pressed);

    keyDel = new QShortcut(this);
    keyDel->setKey(Qt::Key_Delete);
    connect(keyDel, &QShortcut::activated, this, &MainWindow::keyDel_pressed);


    QTimer::singleShot(1000, this, &MainWindow::timer_shot);
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

void MainWindow::updateList()
{

    QDir directory("Data");
    QStringList shits = directory.entryList(QStringList() << "*.txt" << "*.TXT", QDir::Files);
    ui->listWidget->clear();
    foreach(QString filename, shits) {
        ui->listWidget->addItem(filename.remove(".txt"));
    }
    ui->listWidget->setFocus();
}

void MainWindow::loadTextEditor(std::string filename)
{
    ui->widget->hide();
    m_textEditor->openFile(filename + ".txt");
    m_textEditor->show();
    m_textEditor->setFocus();
}



void MainWindow::on_close_pushButton_clicked()
{
    m_textEditor->closeFile();
    this->close();
}

void MainWindow::on_tri_pushButton_clicked()
{
    setWindowState(Qt::WindowState::WindowMinimized);
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

        loadTextEditor(fileName.toStdString());
    }

}

void MainWindow::on_home_pushButton_clicked()
{
    if (m_textEditor->isVisible()) {
        m_textEditor->hide();
        m_textEditor->closeFile();
        ui->widget->show();
        updateList();
    }
}

void MainWindow::keyEsc_pressed()
{
    on_home_pushButton_clicked();
}

void MainWindow::keyDel_pressed()
{
    if (!ui->listWidget->selectedItems().empty()){
    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Submit", "Rly delete?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {


      } else {

      }
    }
}

void MainWindow::timer_shot()
{
    ui->listWidget->setFocus();
}

void MainWindow::on_rename_pushButton_clicked()
{
    if(!ui->listWidget->selectedItems().empty()) {
        bool ok;
        auto fileName = QInputDialog::getText(this, tr("Rename"), tr("Name:"), QLineEdit::Normal, nullptr, &ok);
        if (ok) {
            QFile file("data/" + ui->listWidget->selectedItems().front()->text() + ".txt");
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file.rename("data/" + fileName + ".txt");
            file.close();
            updateList();
            ui->listWidget->setCurrentItem(ui->listWidget->findItems(fileName, Qt::MatchExactly).front());
        }
    }
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    loadTextEditor(item->text().toStdString());
}
