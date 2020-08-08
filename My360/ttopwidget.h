#ifndef TTOPWIDGET_H
#define TTOPWIDGET_H

#include <QWidget>

class QLabel;
class TFuncButton;
class QPropertyAnimation;
class QParallelAnimationGroup;
class TWidgetAnimation;
class TScoreLabel;

class TTopWidget : public QWidget
{
public:
    enum btnType
    {
        playVideo = 0,
        skin,
        menu,
        min,
        close,
        exam
    };
    Q_OBJECT
public:
    explicit TTopWidget(QWidget *parent = nullptr);
    ~TTopWidget();
    void startAnimation(bool isOut);
    TWidgetAnimation *getAnimation();
    TFuncButton *getBtn(btnType type);

private:
    QLabel *m_iconLabelTop;
    QLabel *m_textLabelTop;

    TFuncButton *m_playVideoBtn;
    TFuncButton *m_skinBtn;
    TFuncButton *m_menuBtn;
    TFuncButton *m_minBtn;
    TFuncButton *m_closeBtn;
    TFuncButton *m_examBtn;

    TWidgetAnimation *m_aniamtion;

    TScoreLabel *m_scoreLabel;
    QLabel *m_tipLabel;

signals:

};

#endif // TTOPWIDGET_H
