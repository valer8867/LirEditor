#include "search.h"
#include "ui_search.h"

#include <QFile>
#include <QSizePolicy>

#include <algorithm>

Search::Search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search)
{

    ui->setupUi(this);

    QFile file(":/dictionaries/dictv0.1");
    file.open(QFile::ReadOnly);
    std::string line;
    while (!file.atEnd())
       {
         line = file.readLine().toStdString();

         line.pop_back();
         line.pop_back();
          m_words.push_back(line);
       }
}

Search::~Search()
{
    delete ui;
}

void Search::m_setFocus()
{
    ui->lineEdit->setFocus();
}

void Search::on_pushButton_clicked()
{
    if(ui->lineEdit->text().isEmpty()) return;
    ui->textBrowser->clear();

    std::string tmp = ui->lineEdit->text().toStdString();
    std::string word;
    std::string pattern;
    char c;
    for (auto &item : m_words) {
        pattern = tmp;
        word = item;
        while(true) {
            if (pattern.empty())  {
                ui->textBrowser->append(item.c_str());
                break;
            }
            c = pattern.back();
            pattern.pop_back();
            auto it = std::find(word.begin(), word.end(), c);
            if (it != word.end()) {
                word.erase(it);
            }
            else break;

        }

    }
}
