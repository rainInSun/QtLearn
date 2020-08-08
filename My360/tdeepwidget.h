#ifndef TDEEPWIDGET_H
#define TDEEPWIDGET_H

#include <QWidget>

class TDeepTopWidget;
class TDeepLowWidget;

class TDeepWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TDeepWidget(QWidget *parent = nullptr);
    ~TDeepWidget();

    TDeepTopWidget *getDeepTopWidget();
    TDeepLowWidget *getDeepLowWidget();

private:
    TDeepTopWidget *m_deepTopBox;
    TDeepLowWidget *m_deepLowBox;
signals:

};

#endif // TDEEPWIDGET_H
