#ifndef SAFETEXTEDITOR_H
#define SAFETEXTEDITOR_H

#include <QTextEdit>

class QTimer;

class SafeTextEditor : public QTextEdit
{
    Q_OBJECT

public:
    SafeTextEditor(QWidget *parent = nullptr);

    void openFile(std::string filename);
    void closeFile();

private:
    std::string m_filename;

    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;

};

#endif // SAFETEXTEDITOR_H
