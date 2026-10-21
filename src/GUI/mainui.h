#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MainUI;
}

class GLWidget;

class MainUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainUI(QWidget *parent = 0);
    ~MainUI();

private:
    Ui::MainUI *ui;

    GLWidget *m_glWidget;
    QPushButton *m_testBtn;
};

#endif // MAINUI_H
