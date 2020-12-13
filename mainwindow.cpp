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
#include <QSizePolicy>

#include <iostream>
#include <fstream>

#include "safetexteditor.h"
#include "search.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mousePressed(false)
{
    ui->setupUi(this);

    m_textEditor = new SafeTextEditor();
    m_textEditor->hide();
    ui->centralwidget->layout()->addWidget(m_textEditor);
    m_search = new Search();
    m_search->hide();
    ui->centralwidget->layout()->addWidget(m_search);
    updateList();

    keyEsc = new QShortcut(this);
    keyEsc->setKey(Qt::Key_Escape);
    connect(keyEsc, &QShortcut::activated, this, &MainWindow::keyEsc_pressed);

    keyDel = new QShortcut(this);
    keyDel->setKey(Qt::Key_Delete);
    connect(keyDel, &QShortcut::activated, this, &MainWindow::keyDel_pressed);

    keyEnter = new QShortcut(this);
    keyEnter->setKey(Qt::Key_Return);
    connect(keyEnter, &QShortcut::activated, this, &MainWindow::keyEnter_pressed);


    keyCtrlN = new QShortcut(this);
    keyCtrlN->setKey(Qt::CTRL + Qt::Key_N);
    connect(keyCtrlN, &QShortcut::activated, this, &MainWindow::on_createNew_pushButton_clicked);

    keyCtrlF = new QShortcut(this);
    keyCtrlF->setKey(Qt::CTRL + Qt::Key_F);
    connect(keyCtrlF, &QShortcut::activated, this, &MainWindow::on_search_pushButton_clicked);


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
    keyEnter->setEnabled(false);
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
        m_search->hide();
        updateList();
        keyEnter->setEnabled(true);
    }
}

void MainWindow::keyEsc_pressed()
{
    on_home_pushButton_clicked();
}

void MainWindow::keyDel_pressed()
{
    on_delete_pushButton_clicked();
}

void MainWindow::keyEnter_pressed()
{
    if(!ui->listWidget->selectedItems().empty()) {
        on_listWidget_itemDoubleClicked(ui->listWidget->selectedItems().front());
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

void MainWindow::on_delete_pushButton_clicked()
{

    if(!ui->listWidget->selectedItems().empty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Remove", "Are you sure?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            QFile file("data/" + ui->listWidget->selectedItems().front()->text() + ".txt");
            file.remove();
            updateList();
        }

    }
}

void MainWindow::on_search_pushButton_clicked()
{
    if (m_textEditor->isHidden()) return;
    if (m_search->isHidden()) {
        m_search->show();
        m_search->m_setFocus();
    }
    else {
        m_search->hide();
    }
}

void MainWindow::on_listWidget_itemEntered(QListWidgetItem *item)
{

}
