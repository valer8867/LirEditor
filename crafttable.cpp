#include "crafttable.h"
#include "ui_crafttable.h"

craftTable::craftTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::craftTable)
{
    ui->setupUi(this);
}

craftTable::~craftTable()
{
    delete ui;
}
