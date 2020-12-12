#include "safetexteditor.h"

#include <fstream>

SafeTextEditor::SafeTextEditor(QWidget *parent)
    : QTextEdit(parent)
{

    setLineWrapMode(QTextEdit::LineWrapMode::NoWrap);
    setFrameShape(QTextEdit::NoFrame);
    setStyleSheet("background: rgb(234, 234, 234)");
    setFont (QFont ("Arial", 10));

    startTimer(60000);

}

void SafeTextEditor::openFile(std::string filename)
{
    m_filename = filename;
    std::ifstream fin(std::string("data/") + filename);
    auto content = std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());
    setText(content.c_str());
}

void SafeTextEditor::closeFile()
{
    if (!m_filename.empty()) {
        std::ofstream fout(std::string("data/") + m_filename);
        fout << this->toPlainText().toStdString();
        m_filename.clear();
    }
    clear();
}


void SafeTextEditor::timerEvent(QTimerEvent *event)
{
    if (!m_filename.empty()) {
        std::ofstream fout(std::string("data/") + m_filename);
        fout << this->toPlainText().toStdString();
    }
}
