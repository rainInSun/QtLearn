#ifndef TLOWERWIDGET_H
#define TLOWERWIDGET_H

#include <QWidget>

class TFuncButton;
class TShortcutButton;
class TWidgetAnimation;

class TLowerWidget : public QWidget
{
public:
    enum BtnType
    {
        checkBtn = 0,
        cleanBtn,
        speedupBtn,
    };
    Q_OBJECT
public:
    explicit TLowerWidget(QWidget *parent = nullptr);
    ~TLowerWidget();
    TFuncButton* getBtn(BtnType btnType);

    void startAnimation(bool isOut);
    TWidgetAnimation *getAnimation();

private:
    TFuncButton *m_check;
    TFuncButton *m_clean;
    TFuncButton *m_speedup;

    TShortcutButton *m_softManager;
    TShortcutButton *m_humanSevice;
    TShortcutButton *m_phoneHelper;
    TShortcutButton *m_netSpeedTest;

    TWidgetAnimation *m_aniamtion;
};

#endif // TLOWERWIDGET_H
