#ifndef TDEEPTOPWIDGET_H
#define TDEEPTOPWIDGET_H

#include <QWidget>

class TFuncButton;

class TDeepTopWidget : public QWidget
{
public:
    enum BtnTye
    {
        backBtn = 0
    };
    Q_OBJECT
public:
    explicit TDeepTopWidget(QWidget *parent = nullptr);
    ~TDeepTopWidget();

    TFuncButton *getBtn(BtnTye type);

public slots:
    void view();

private:
    TFuncButton *m_backBtn;
signals:

};

#endif // TDEEPTOPWIDGET_H
