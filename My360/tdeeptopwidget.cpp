#include "tdeeptopwidget.h"
#include "buttons.h"

TDeepTopWidget::TDeepTopWidget(QWidget *parent)
    : QWidget(parent)
    , m_backBtn(nullptr)
{
    setFixedSize(900, 150);
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(QString("QWidget {background-color: %1}").arg(QColor(42, 191, 29).name(QColor::HexArgb)));

    m_backBtn = new TFuncButton(this, QString(":/images/resource/icons/return.png"), 115, 38);
    m_backBtn->move(0, 0);
}

TDeepTopWidget::~TDeepTopWidget()
{

}

TFuncButton *TDeepTopWidget::getBtn(TDeepTopWidget::BtnTye type)
{
    switch (type)
    {
    case backBtn:
        return m_backBtn;
        break;
    default:
        break;
    }
    return nullptr;
}

void TDeepTopWidget::view()
{
    setVisible(true);
}
