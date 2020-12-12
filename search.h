#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>

#include <string>
#include <vector>

namespace Ui {
class Search;
}

class Search : public QWidget
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

    void m_setFocus();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Search *ui;
    std::vector<std::string> m_words;
};

#endif // SEARCH_H
