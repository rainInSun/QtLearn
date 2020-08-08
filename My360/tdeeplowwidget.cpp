#include "tdeeplowwidget.h"
#include "buttons.h"

#include <QHBoxLayout>

TDeepLowWidget::TDeepLowWidget(QWidget *parent)
    : QWidget(parent)
    , m_btnQuickScan(nullptr)
    , m_btnFullScan(nullptr)
    , m_btnCustomScan(nullptr)
{
    setFixedSize(900, 450);
    m_btnQuickScan = new TFuncButtonWithAnimation(this, QString(":/images/resource/icons/scan_button_quick.png"),
                                                  QString(":/images/resource/icons/scan_button_quick_hover.png"),
                                                  140, 140);
    m_btnFullScan = new TFuncButtonWithAnimation(this, QString(":/images/resource/icons/scan_button_full.png"),
                                                 QString(":/images/resource/icons/scan_button_full_hover.png"),
                                                 140, 140);
    m_btnCustomScan = new TFuncButtonWithAnimation(this, QString(":/images/resource/icons/scan_button_custom.png"),
                                                   QString(":/images/resource/icons/scan_button_custom_hover.png"),
                                                   140, 140);
    QHBoxLayout *hLyt = new QHBoxLayout;
    hLyt->setMargin(100);
    hLyt->addWidget(m_btnQuickScan);
    hLyt->addStretch(1);
    hLyt->addWidget(m_btnFullScan);
    hLyt->addStretch(1);
    hLyt->addWidget(m_btnCustomScan);
    setLayout(hLyt);
}

TDeepLowWidget::~TDeepLowWidget()
{

}

void TDeepLowWidget::view()
{
    setVisible(true);
}
