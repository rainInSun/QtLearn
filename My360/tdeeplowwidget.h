#ifndef TDEEPLOWWIDGET_H
#define TDEEPLOWWIDGET_H

#include <QWidget>

class TFuncButtonWithAnimation;

class TDeepLowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TDeepLowWidget(QWidget *parent = nullptr);
    ~TDeepLowWidget();
public slots:
    void view();
protected:

private:
    TFuncButtonWithAnimation *m_btnQuickScan;
    TFuncButtonWithAnimation *m_btnFullScan;
    TFuncButtonWithAnimation *m_btnCustomScan;

signals:

};

#endif // TDEEPLOWWIDGET_H
