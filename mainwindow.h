#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListWidgetItem;
class SafeTextEditor;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QShotcut;

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
    SafeTextEditor *m_textEditor;
    QShortcut *keyEsc;
    QShortcut *keyDel;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void updateList();
    void loadTextEditor(std::string);
    void on_close_pushButton_clicked();
    void on_tri_pushButton_clicked();
    void on_topHint_pushButton_clicked();
    void on_createNew_pushButton_clicked();


    void on_home_pushButton_clicked();
    void keyEsc_pressed();
    void keyDel_pressed();
    void timer_shot();
    void on_rename_pushButton_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
