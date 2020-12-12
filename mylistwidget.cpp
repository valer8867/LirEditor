#include "mylistwidget.h"

#include <QMouseEvent>

MyListWidget::MyListWidget(QWidget *parent)
    : QListWidget(parent)
    , rmbPressed(false)
{

}


void MyListWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
       // emit rightClick(&event->pos());
    }
    QListWidget::mousePressEvent(event);
}
