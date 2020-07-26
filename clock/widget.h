#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class clockWidget : public QWidget
{
    Q_OBJECT

public:
    clockWidget(QWidget *parent = nullptr);
    ~clockWidget();
    void startTimer();

protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private slots:
    void onTimer();

private:
    QTimer *m_timer;
    QPoint m_point;
};
#endif // WIDGET_H
