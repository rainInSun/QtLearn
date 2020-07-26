#include "widget.h"

#include <QPainter>
#include <QPen>
#include <QColor>
#include <QRect>
#include <QString>
#include <QFontMetrics>
#include <QTimer>

countDownWidget::countDownWidget(QWidget *parent)
    : QWidget(parent)
    ,m_countNum(3)
    ,m_countDownTimer(nullptr)
{
    setFixedSize(200, 200);
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_countDownTimer = new QTimer(this);
    connect(m_countDownTimer, &QTimer::timeout, this, &countDownWidget::onTimeout);
}

countDownWidget::~countDownWidget()
{
}

void countDownWidget::startCountDown()
{
    m_countDownTimer->start(1000);
}

void countDownWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QBrush brush(QColor(192, 192, 192));
    painter.setBrush(brush);

    QRect rect(0, 0, width(), height());
    painter.drawEllipse(rect);

    QFont font;
    font.setPixelSize(120);
    painter.setFont(font);

    QPen pen(Qt::white);
    painter.setPen(pen);

    QString strNum = QString::number(m_countNum);

    int numWidth = QFontMetrics(font).width(strNum);

    QRect rc((width() - numWidth) / 2, (height() - 140) / 2, 140, 140);
    painter.drawText(rc, strNum);
}

void countDownWidget::onTimeout()
{
    m_countNum--;
    if (m_countNum <= 0 && m_countDownTimer->isActive())
    {
        m_countDownTimer->stop();
        hide();
    }
    update();
}

