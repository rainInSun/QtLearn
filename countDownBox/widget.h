#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QTimer;

class countDownWidget : public QWidget
{
    Q_OBJECT

public:
    countDownWidget(QWidget *parent = nullptr);
    ~countDownWidget();
    void startCountDown();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void onTimeout();

private:

    int m_countNum;
    QTimer *m_countDownTimer;
};
#endif // WIDGET_H
