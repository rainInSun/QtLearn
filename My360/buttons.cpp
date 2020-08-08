#include "buttons.h"

#include <QVector>
#include <QPixmap>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QFont>
#include <QPropertyAnimation>
#include <QPaintEvent>

TFuncButton::TFuncButton(QWidget *parent, QString iconPath, int btnWidth, int btnHeight)
    : QPushButton(parent)
    , m_curPixmapIndex(0)
    , m_iconPath(iconPath)
{
    setFixedSize(btnWidth,btnHeight);
    QPixmap icon(m_iconPath);
    if (!icon.isNull())
    {
        for (int cnt = 0; cnt < 4; ++cnt)
            {
                m_pixmapList.push_back(icon.copy(cnt * (icon.width() / 4),
                                                        0,
                                                        icon.width() / 4,
                                                        icon.height()));
            }
    }
}

TFuncButton::~TFuncButton()
{

}

void TFuncButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRect rc(0, 0, m_pixmapList[m_curPixmapIndex].width(), m_pixmapList[m_curPixmapIndex].height());
    if (!m_pixmapList.isEmpty())
        painter.drawPixmap(rc, m_pixmapList[m_curPixmapIndex]);

}

void TFuncButton::enterEvent(QEvent *event)
{
    m_curPixmapIndex = 1;
    update();

    return QPushButton::enterEvent(event);
}

void TFuncButton::leaveEvent(QEvent *event)
{
    m_curPixmapIndex = 0;
    update();

    return QPushButton::leaveEvent(event);
}

void TFuncButton::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        m_curPixmapIndex = 2;
        update();
    }
    return QPushButton::mousePressEvent(event);
}

void TFuncButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button())
    {
        m_curPixmapIndex = 0;
        update();
    }
    return QPushButton::mouseReleaseEvent(event);
}

int TFuncButton::curIndex()
{
    return m_curPixmapIndex;
}

void TFuncButton::setCurIndex(int curInex)
{
    m_curPixmapIndex = curInex;
    update();
}


TShortcutButton::TShortcutButton(QWidget *parent, QString iconPath, QString bgkPath, QString text)
    : QPushButton(parent)
    , m_curIconIndex(0)
    , m_curBkgIndex(0)
    , m_iconPixmap(nullptr)
    , m_showText(text)
{
    setFixedSize(70, 70);

    m_iconPixmap = new QPixmap(iconPath);
    QPixmap bkgPixmap(bgkPath);

    if (!bkgPixmap.isNull())
    {
        for (int i = 0; i < 2; i++)
        {
            m_bkgList.push_back(bkgPixmap.copy(i * (bkgPixmap.width() / 3),
                                               0,
                                               bkgPixmap.width() / 3,
                                               bkgPixmap.height()));
        }
    }

}

TShortcutButton::~TShortcutButton()
{

}

void TShortcutButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect bkgRec(0, 0, width(), height());
    if (!m_bkgList.isEmpty())
        painter.drawPixmap(bkgRec, m_bkgList[m_curBkgIndex]);

    QRect iconRec(15, 10, 40, 40);
    if (!m_iconPixmap->isNull())
        painter.drawPixmap(iconRec, *m_iconPixmap);

    QRect textRec(10, 55, 50, 20);
    QFont font;
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(textRec, m_showText);

}

void TShortcutButton::enterEvent(QEvent *event)
{
    m_curBkgIndex = 1;
    update();

    return QPushButton::enterEvent(event);
}

void TShortcutButton::leaveEvent(QEvent *event)
{
    m_curBkgIndex = 0;
    update();

    return QPushButton::leaveEvent(event);
}

TFuncButtonWithAnimation::TFuncButtonWithAnimation(QWidget *parent, QString iconPath, QString animationImgPath, int btnWidth, int btnHeight)
    : TFuncButton(parent, iconPath, btnWidth, btnHeight)
    , m_btnAnimation(nullptr)
{
    QPixmap btnAnimationPixmap(animationImgPath);
    if (!btnAnimationPixmap.isNull())
    {
        for (int cnt = 0; cnt < 8; cnt++)
        {
            m_btnAnimationPixmapVec.push_back(btnAnimationPixmap.copy(cnt * btnAnimationPixmap.width() / 8,
                                                                      0,
                                                                      btnAnimationPixmap.width() / 8,
                                                                      btnAnimationPixmap.height()));
        }
    }
    setCurPixmapVec(m_pixmapList);
    initBtnAnimation();
    connect(m_btnAnimation, SIGNAL(finished()), this, SLOT(onBtnAnimationFinish()));
}

TFuncButtonWithAnimation::~TFuncButtonWithAnimation()
{

}

void TFuncButtonWithAnimation::enterEvent(QEvent *event)
{
    Q_UNUSED(event);

    setCurPixmapVec(m_btnAnimationPixmapVec);
    m_btnAnimation->start();
}

void TFuncButtonWithAnimation::leaveEvent(QEvent *event)
{
    m_btnAnimation->stop();
    setCurPixmapVec(m_pixmapList);
    TFuncButton::leaveEvent(event);
}

void TFuncButtonWithAnimation::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rc(event->rect().x(),event->rect().y(), m_curPixmapVec[m_curPixmapIndex].width(), m_curPixmapVec[m_curPixmapIndex].height());
    painter.drawPixmap(rc, m_curPixmapVec[m_curPixmapIndex]);
}

void TFuncButtonWithAnimation::mousePressEvent(QMouseEvent *event)
{
    m_btnAnimation->stop();
    setCurPixmapVec(m_pixmapList);
    TFuncButton::mousePressEvent(event);
}

void TFuncButtonWithAnimation::mouseReleaseEvent(QMouseEvent *event)
{
    TFuncButton::mouseReleaseEvent(event);
}

void TFuncButtonWithAnimation::initBtnAnimation()
{
    m_btnAnimation = new QPropertyAnimation(this, "m_curPixmapIndex");
    m_btnAnimation->setStartValue(0);
    m_btnAnimation->setEndValue(7);
    m_btnAnimation->setDuration(600);
}

void TFuncButtonWithAnimation::setCurPixmapVec(QVector<QPixmap> &pixmapVec)
{
    m_curPixmapVec = pixmapVec;
}

void TFuncButtonWithAnimation::onBtnAnimationFinish()
{
    setCurPixmapVec(m_pixmapList);
    m_curPixmapIndex = 0;
    update();
}
