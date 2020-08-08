#ifndef TSCORELABEL_H
#define TSCORELABEL_H

#include <QLabel>

class QPixmap;

class TScoreLabel : public QLabel
{
public:
    explicit TScoreLabel(QWidget *parent = nullptr);
    ~TScoreLabel();
    void setNum(int fstNum, int scdNum);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPixmap> m_pixmapList;
    int m_fstIndex;
    int m_scdIndex;
};

#endif // TSCORELABEL_H
