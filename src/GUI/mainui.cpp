#include "mainui.h"
#include "ui_mainui.h"

#include "glwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

MainUI::MainUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainUI)
{
    ui->setupUi(this);

    m_glWidget = new GLWidget(this);
    m_testBtn = new QPushButton("test", this);

    QHBoxLayout* h_layout = new QHBoxLayout(this);
    setLayout(h_layout);

    QVBoxLayout* v_layout_11 = new QVBoxLayout(this);
    v_layout_11->addWidget(m_glWidget);

    QVBoxLayout* v_layout_12 = new QVBoxLayout(this);
    v_layout_12->addWidget(m_testBtn);

    h_layout->addLayout(v_layout_11);
    h_layout->addLayout(v_layout_12);

    h_layout->setStretch(0,5);
    h_layout->setStretch(1,1);

    connect(m_testBtn, SIGNAL(clicked()), m_glWidget, SLOT(onBtnClicked()));
}

MainUI::~MainUI()
{
    delete ui;
}
