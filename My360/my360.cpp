#include "my360.h"
#include "tlowerwidget.h"
#include "ttopwidget.h"
#include "tdeepwidget.h"
#include "twidgetanimation.h"
#include "tdeeplowwidget.h"
#include "tdeeptopwidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QPoint>
#include <QMouseEvent>

Widget360::Widget360(QWidget *parent)
    : QWidget(parent)
    , m_lowerBox(nullptr)
    , m_topBox(nullptr)
    , m_deepBox(nullptr)
{
    setFixedSize(900, 600);
    setWindowFlag(Qt::FramelessWindowHint);
    m_lowerBox = new TLowerWidget(this);
    setWindowIcon(QIcon(":/images/resource/icons/360logo.png"));
    //m_lowerBox->move(0, 440);

    m_topBox = new TTopWidget(this);
    m_deepBox = new TDeepWidget(this);
    m_deepBox->lower();
    m_deepBox->hide();

    QVBoxLayout *hLyt = new QVBoxLayout(this);
    hLyt->setMargin(0);
    hLyt->setSpacing(0);
    hLyt->addWidget(m_topBox);
    hLyt->addWidget(m_lowerBox);

    setLayout(hLyt);

    connect(m_lowerBox->getBtn(TLowerWidget::checkBtn), SIGNAL(clicked()),
            this, SLOT(onCheckBtnClicked()));

    connect(m_lowerBox->getBtn(TLowerWidget::checkBtn), SIGNAL(clicked()),
            m_deepBox, SLOT(show()));

    connect(m_deepBox->getDeepTopWidget()->getBtn(TDeepTopWidget::backBtn), SIGNAL(clicked()),
            this, SLOT(onBackBtnClicked()));

//    connect(m_lowerBox->getAnimation()->getOutAnimation(), SIGNAL(valueChanged(QVariant)),
//            m_deepBox->getDeepTopWidget(), SLOT(update()));

//    connect(m_lowerBox->getAnimation()->getOutAnimation(), SIGNAL(valueChanged(QVariant)),
//            m_deepBox->getDeepLowWidget(), SLOT(update()));
    connect(m_lowerBox->getAnimation()->getInAnimation(), SIGNAL(finished()),
            m_deepBox, SLOT(hide()));

    connect(m_topBox->getBtn(TTopWidget::close), SIGNAL(clicked()),
            this, SLOT(onCloseBtnClicked()));
}

Widget360::~Widget360()
{
}

void Widget360::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
    }
}

void Widget360::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        m_point = event->globalPos() - this->frameGeometry().topLeft();
    }
}

void Widget360::onCheckBtnClicked()
{
    m_topBox->startAnimation(true);
    m_lowerBox->startAnimation(true);
}

void Widget360::onBackBtnClicked()
{
    m_topBox->startAnimation(false);
    m_lowerBox->startAnimation(false);
}

void Widget360::onCloseBtnClicked()
{
    close();
}

