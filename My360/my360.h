#ifndef WIDGET_H
#define WIDGET_H
#include "buttons.h"
#include <QWidget>

class TLowerWidget;
class TTopWidget;
class TDeepWidget;

class Widget360 : public QWidget
{
    Q_OBJECT

public:
    Widget360(QWidget *parent = nullptr);
    ~Widget360();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onCheckBtnClicked();
    void onBackBtnClicked();
    void onCloseBtnClicked();

private:
    TLowerWidget *m_lowerBox;
    TTopWidget *m_topBox;
    TDeepWidget *m_deepBox;

    QPoint m_point;

};
#endif // WIDGET_H
