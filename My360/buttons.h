#ifndef BUTTONS_H
#define BUTTONS_H

#include <QPushButton>

class QPixmap;
class QString;
class QPropertyAnimation;

class TFuncButton : public QPushButton
{
    Q_OBJECT;
    Q_PROPERTY(int m_curPixmapIndex READ curIndex WRITE setCurIndex)
public:
    TFuncButton(QWidget *parent = nullptr, QString iconPath = "", int btnWidth = 100, int btnHeight = 100);
    ~TFuncButton();

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    int curIndex();
    void setCurIndex(int curInex);

protected:
    QVector<QPixmap> m_pixmapList;
    int m_curPixmapIndex;
    QString m_iconPath;
};

class TShortcutButton : public QPushButton
{
    Q_OBJECT;

public:
    TShortcutButton(QWidget *parent = nullptr, QString iconPath = "", QString bgkPath = "", QString text = "");
    ~TShortcutButton();

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int m_curIconIndex;
    int m_curBkgIndex;
    QPixmap *m_iconPixmap;
    QVector<QPixmap> m_bkgList;
    QString m_showText;
};

class TFuncButtonWithAnimation : public TFuncButton
{
    Q_OBJECT;

public:
    TFuncButtonWithAnimation(QWidget *parent = nullptr, QString iconPath = "",QString animationImgPath = "",
                             int btnWidth = 100, int btnHeight = 100);
    ~TFuncButtonWithAnimation();

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
private:
    QVector<QPixmap> m_curPixmapVec;
    QVector<QPixmap> m_btnAnimationPixmapVec;
    QPropertyAnimation *m_btnAnimation;

    void initBtnAnimation();
    void setCurPixmapVec(QVector<QPixmap> &pixmapVec);

private slots:
    void onBtnAnimationFinish();

};
#endif // BUTTONS_H
