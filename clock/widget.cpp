#include "widget.h"

#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QTime>
#include <QTimer>
#include <QMouseEvent>

clockWidget::clockWidget(QWidget *parent)
    : QWidget(parent)
    , m_timer(nullptr)
    , m_point(QPoint(0, 0))
{
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setFixedSize(300, 300);

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &clockWidget::onTimer);
}

clockWidget::~clockWidget()
{
    if (m_timer != nullptr)
    {
        delete m_timer;
        m_timer = nullptr;
    }
}

void clockWidget::startTimer()
{
    m_timer->start(1000);
}

void clockWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen(Qt::black);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.translate(width() / 2, height() / 2);

    painter.save();
    for (int i = 0; i < 12; i++)
    {
        painter.drawLine(0, -150, 0, -130);
        painter.rotate(30);
    }
    painter.restore();

    static const QPoint minuteHand[3] =
    {
        QPoint(-10, 0),
        QPoint(10, 0),
        QPoint(0,-100)
    };

    painter.setPen(Qt::NoPen);

    QBrush brush(Qt::black);
    painter.setBrush(brush);

    QTime timeNow = QTime::currentTime();
    painter.save();
    painter.rotate(6 * (timeNow.minute() + timeNow.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();

    static const QPoint hourHand[3] =
    {
        QPoint(-10, 0),
        QPoint(10, 0),
        QPoint(0,-80)
    };
    //painter.rotate(30);
    painter.save();
    painter.rotate(30 * (timeNow.hour() + timeNow.minute() / 60.0 + timeNow.second() / 3600.0));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();
}

void clockWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
    }
}

void clockWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_point = event->globalPos() - this->frameGeometry().topLeft();
    }
    else
    {
        close();
    }
}

void clockWidget::onTimer()
{
    update();
}

