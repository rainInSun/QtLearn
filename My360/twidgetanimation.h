#ifndef TWIDGETANIMATION_H
#define TWIDGETANIMATION_H

#include <QObject>

class QPropertyAnimation;
class QParallelAnimationGroup;

class TWidgetAnimation : public QObject
{
    Q_OBJECT
public:
    explicit TWidgetAnimation(QRect startRec, QRect endRec, QObject *parent = nullptr);
    ~TWidgetAnimation();

    void startAnimation(bool isOut);
    QPropertyAnimation *getOutAnimation();
    QPropertyAnimation *getInAnimation();

private:
    void initAnimation(QObject *parent, QRect startRec, QRect endRec);

    QPropertyAnimation *m_outGeometryAnimation;
    QPropertyAnimation *m_inGeometryAnimation;
    QPropertyAnimation *m_outWinOpacityAnimation;
    QPropertyAnimation *m_inWinOpacityAnimation;

    QParallelAnimationGroup *m_inGrp;
    QParallelAnimationGroup *m_outGrp;


signals:

};

#endif // TWIDGETANIMATION_H
