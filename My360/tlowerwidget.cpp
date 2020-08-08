#include "tlowerwidget.h"
#include "buttons.h"
#include "twidgetanimation.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

TLowerWidget::TLowerWidget(QWidget *parent)
    : QWidget(parent)
    , m_check(nullptr)
    , m_clean(nullptr)
    , m_speedup(nullptr)
    , m_softManager(nullptr)
    , m_humanSevice(nullptr)
    , m_phoneHelper(nullptr)
    , m_netSpeedTest(nullptr)
    , m_aniamtion(nullptr)
{
    setFixedSize(900, 160);
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(QString("QWidget {background-color: #FFFFFF}"));
    m_check = new TFuncButton(this, QString(":/images/resource/icons/safe_check.png"));
    m_check->setFixedSize(95, 95);
    m_clean = new TFuncButton(this, QString(":/images/resource/icons/clean.png"));
    m_clean->setFixedSize(95, 95);
    m_speedup = new TFuncButton(this, QString(":/images/resource/icons/youhua.png"));
    m_speedup->setFixedSize(95, 95);

    QHBoxLayout *hFucBtnLayout = new QHBoxLayout;
    hFucBtnLayout->setMargin(0);
    hFucBtnLayout->setSpacing(0);
    hFucBtnLayout->addWidget(m_check, 0, Qt::AlignVCenter);
    hFucBtnLayout->addWidget(m_clean, 0, Qt::AlignVCenter);
    hFucBtnLayout->addWidget(m_speedup, 0, Qt::AlignVCenter);
    hFucBtnLayout->addStretch(10);

    m_softManager = new TShortcutButton(this, QString(":/images/resource/icons/shortcut04.png"),
                                     QString(":/images/resource/icons/shortcut_bkg.png"),
                                     QString(tr("软件管家")));
    m_humanSevice = new TShortcutButton(this, QString(":/images/resource/icons/shortcut01.png"),
                                     QString(":/images/resource/icons/shortcut_bkg.png"),
                                     QString(tr("人工服务")));
    m_phoneHelper = new TShortcutButton(this, QString(":/images/resource/icons/shortcut02.png"),
                                     QString(":/images/resource/icons/shortcut_bkg.png"),
                                     QString(tr("手机助手")));
    m_netSpeedTest = new TShortcutButton(this, QString(":/images/resource/icons/shortcut03.png"),
                                     QString(":/images/resource/icons/shortcut_bkg.png"),
                                     QString(tr("宽带测速")));
    QHBoxLayout *hShortcutBtnLayout = new QHBoxLayout;
    hShortcutBtnLayout->setMargin(10);
    hShortcutBtnLayout->setSpacing(10);
    hShortcutBtnLayout->addStretch(10);
    hShortcutBtnLayout->addWidget(m_softManager, 0, Qt::AlignBottom);
    hShortcutBtnLayout->addWidget(m_humanSevice, 0, Qt::AlignBottom);
    hShortcutBtnLayout->addWidget(m_phoneHelper, 0, Qt::AlignBottom);
    hShortcutBtnLayout->addWidget(m_netSpeedTest, 0, Qt::AlignBottom);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(hFucBtnLayout);
    mainLayout->addLayout(hShortcutBtnLayout);
    setLayout(mainLayout);

    m_aniamtion = new TWidgetAnimation(QRect(0, 440, 900, 160), QRect(0, 600, 900, 160), this);
}

TLowerWidget::~TLowerWidget()
{

}

TFuncButton* TLowerWidget::getBtn(TLowerWidget::BtnType btnType)
{
    switch (btnType)
    {
    case checkBtn:
        return m_check;
        break;
    case cleanBtn:
        return m_clean;
        break;
    case speedupBtn:
        return m_speedup;
        break;
    default:
        break;
    }
    return nullptr;
}

void TLowerWidget::startAnimation(bool isOut)
{
    m_aniamtion->startAnimation(isOut);
}

TWidgetAnimation *TLowerWidget::getAnimation()
{
    return m_aniamtion;
}
