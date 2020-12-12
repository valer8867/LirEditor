#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QListWidget>


class MyListWidget : public QListWidget
{
    Q_OBJECT

public:
    MyListWidget(QWidget* parent);

private:
    bool rmbPressed;


protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MYLISTWIDGET_H
