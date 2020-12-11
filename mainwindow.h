#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidgetItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

    QPoint startPos;
    bool mousePressed;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void on_close_pushButton_clicked();
    void on_tri_pushButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_topHint_pushButton_clicked();
};
#endif // MAINWINDOW_H
