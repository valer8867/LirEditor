#ifndef NOTESBROWSER_H
#define NOTESBROWSER_H

#include <QMainWindow>

#include <map>
#include <string>

class QListWidgetItem;

namespace Ui {
class NotesBrowser;
}

class NotesBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit NotesBrowser(QWidget *parent = nullptr);
    ~NotesBrowser();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::NotesBrowser *ui;
    std::map<std::string, std::string> notes;
};

#endif // NOTESBROWSER_H
