#include "notesbrowser.h"
#include "ui_notesbrowser.h"

#include <QDir>
#include <QListWidgetItem>
#include <QMdiSubWindow>
#include <QTextBrowser>

#include <fstream>

NotesBrowser::NotesBrowser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotesBrowser)
{
    ui->setupUi(this);
    QDir directory("Data");
    QStringList shits = directory.entryList(QStringList() << "*.txt" << "*.TXT", QDir::Files);
    foreach(QString filename, shits) {

        std::ifstream fin(std::string("data/") + filename.toStdString());
        notes[filename.remove(".txt").toStdString()] = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
        ui->listWidget->addItem(filename);
    }
}

NotesBrowser::~NotesBrowser()
{
    delete ui;
}

void NotesBrowser::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QMdiSubWindow *mdisubwindow = new QMdiSubWindow();
    ui->mdiArea->addSubWindow(mdisubwindow);
    auto textBrowser = new QTextBrowser();
    textBrowser->setText(notes[item->text().toStdString()].c_str());
    mdisubwindow->setWidget(textBrowser);
    mdisubwindow->resize(200, 300);
    mdisubwindow->show();
}
