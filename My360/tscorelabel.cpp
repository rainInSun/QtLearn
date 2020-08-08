#include "tscorelabel.h"

#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

#define HUNDRED_INDEX 10
#define BKG_INDEX 11


TScoreLabel::TScoreLabel(QWidget *parent)
    : QLabel(parent)
    , m_fstIndex(5)
    , m_scdIndex(5)
{
    setFixedSize(200, 200);
    for (int i = 0; i < 10; i++)
    {
        QPixmap tmpPixmap(QString(":/images/resource/scores/%1.png").arg(i));
        m_pixmapList.push_back(tmpPixmap);
    }
    QPixmap hundredPixmap(":/images/resource/scores/hundred.png");
    m_pixmapList.push_back(hundredPixmap);

    QPixmap bkgPixmap(":/images/resource/scores/examine_score.png");
    m_pixmapList.push_back(bkgPixmap);
}


TScoreLabel::~TScoreLabel()
{

}

void TScoreLabel::setNum(int fstNum, int scdNum)
{
    if (fstNum < 0 || fstNum > 9 || scdNum < 0 || scdNum > 9)
    {
        return;
    }
    else
    {
        m_fstIndex = fstNum;
        m_scdIndex = scdNum;
    }
}

void TScoreLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);
    QRect bkgRect(0, 0, m_pixmapList[BKG_INDEX].width(), m_pixmapList[BKG_INDEX].height());
    paint.drawPixmap(bkgRect, m_pixmapList[BKG_INDEX]);

    int x = (200 - 2 * m_pixmapList[m_fstIndex].width()) / 2;
    int y = (200 - m_pixmapList[m_fstIndex].height()) / 2;
    QRect fstNumRect(x, y, m_pixmapList[m_fstIndex].width(), m_pixmapList[m_fstIndex].height());
    QRect scdNumRect(x + m_pixmapList[m_fstIndex].width(), y, m_pixmapList[m_scdIndex].width(), m_pixmapList[m_scdIndex].height());
    paint.drawPixmap(fstNumRect, m_pixmapList[m_fstIndex]);
    paint.drawPixmap(scdNumRect, m_pixmapList[m_scdIndex]);
}
