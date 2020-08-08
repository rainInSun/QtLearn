#include "twidgetanimation.h"

#include <QRect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

TWidgetAnimation::TWidgetAnimation(QRect startRec, QRect endRec, QObject *parent)
    : QObject(parent)
    , m_outGeometryAnimation(nullptr)
    , m_inGeometryAnimation(nullptr)
    , m_outWinOpacityAnimation(nullptr)
    , m_inWinOpacityAnimation(nullptr)
    , m_inGrp(nullptr)
    , m_outGrp(nullptr)
{
    initAnimation(parent, startRec, endRec);
}

TWidgetAnimation::~TWidgetAnimation()
{

}

void TWidgetAnimation::startAnimation(bool isOut)
{
    if (isOut && m_outGrp)
    {
        m_outGrp->start();
    }
    else if (!isOut && m_inGrp)
    {
        m_inGrp->start();
    }
}

QPropertyAnimation *TWidgetAnimation::getOutAnimation()
{
    return m_outGeometryAnimation;
}

QPropertyAnimation *TWidgetAnimation::getInAnimation()
{
    return m_inGeometryAnimation;
}

void TWidgetAnimation::initAnimation(QObject *parent, QRect startRec, QRect endRec)
{
    m_outGeometryAnimation = new QPropertyAnimation(parent, "geometry");
    m_outGeometryAnimation->setDuration(400);
//    m_outGeometryAnimation->setStartValue(QRect(0, 0, 900, 440));
//    m_outGeometryAnimation->setEndValue(QRect(0, -440, 900, 440));
    m_outGeometryAnimation->setStartValue(startRec);
    m_outGeometryAnimation->setEndValue(endRec);

    m_inGeometryAnimation = new QPropertyAnimation(parent, "geometry");
    m_inGeometryAnimation->setDuration(400);
    m_inGeometryAnimation->setStartValue(endRec);
    m_inGeometryAnimation->setEndValue(startRec);

    m_outWinOpacityAnimation = new QPropertyAnimation(parent, "windowOpacity");
    m_outWinOpacityAnimation->setDuration(400);
    m_outWinOpacityAnimation->setStartValue(1);
    m_outWinOpacityAnimation->setEndValue(0);

    m_inWinOpacityAnimation = new QPropertyAnimation(parent, "windowOpacity");
    m_inWinOpacityAnimation->setDuration(400);
    m_inWinOpacityAnimation->setStartValue(0);
    m_inWinOpacityAnimation->setEndValue(1);

    m_outGrp = new QParallelAnimationGroup;
    m_outGrp->addAnimation(m_outGeometryAnimation);
    m_outGrp->addAnimation(m_outWinOpacityAnimation);

    m_inGrp = new QParallelAnimationGroup;
    m_inGrp->addAnimation(m_inGeometryAnimation);
    m_inGrp->addAnimation(m_inWinOpacityAnimation);
}
