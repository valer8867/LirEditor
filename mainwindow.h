#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidgetItem;
class QTextEdit;

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
    QTextEdit *m_textEditor;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void loadTextEditor();
    void on_close_pushButton_clicked();
    void on_tri_pushButton_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_topHint_pushButton_clicked();
    void on_createNew_pushButton_clicked();


    void on_home_pushButton_clicked();
};
#endif // MAINWINDOW_H
