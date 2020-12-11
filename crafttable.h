#ifndef CRAFTTABLE_H
#define CRAFTTABLE_H

#include <QWidget>

namespace Ui {
class craftTable;
}

class craftTable : public QWidget
{
    Q_OBJECT

public:
    explicit craftTable(QWidget *parent = nullptr);
    ~craftTable();

private:
    Ui::craftTable *ui;
};

#endif // CRAFTTABLE_H
