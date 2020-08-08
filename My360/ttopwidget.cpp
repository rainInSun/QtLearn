#include "ttopwidget.h"
#include "buttons.h"
#include "twidgetanimation.h"
#include "tscorelabel.h"

#include <QLabel>
#include <QIcon>
#include <QHBoxLayout>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLabel>

TTopWidget::TTopWidget(QWidget *parent)
    : QWidget(parent)
    , m_iconLabelTop(nullptr)
    , m_textLabelTop(nullptr)
    , m_playVideoBtn(nullptr)
    , m_skinBtn(nullptr)
    , m_menuBtn(nullptr)
    , m_minBtn(nullptr)
    , m_closeBtn(nullptr)
    , m_examBtn(nullptr)
    , m_aniamtion(nullptr)
    , m_scoreLabel(nullptr)
    , m_tipLabel(nullptr)
{
    setFixedSize(900, 440);
    setAttribute(Qt::WA_StyledBackground,true);
    setStyleSheet(QString("QWidget {background-color: %1}").arg(QColor(42, 191, 29).name(QColor::HexArgb)));

    m_iconLabelTop = new QLabel(this);
    m_iconLabelTop->setFixedSize(16, 16);
    QIcon icon(QString(":/images/resource/icons/360logo.png"));
    m_iconLabelTop->setPixmap(icon.pixmap(16, 16));

    m_textLabelTop = new QLabel(this);
    m_textLabelTop->setFixedSize(180, 16);
    m_textLabelTop->setText(tr("360安全管家 1.0 beta"));

    m_playVideoBtn = new TFuncButton(this, QString(":/images/resource/icons/playvideo.png"), 24, 24);
    m_skinBtn = new TFuncButton(this, QString(":/images/resource/icons/Skin.png"), 24, 24);
    m_menuBtn = new TFuncButton(this, QString(":/images/resource/icons/Menu.png"), 24, 24);
    m_minBtn = new TFuncButton(this, QString(":/images/resource/icons/min.png"), 24, 24);
    m_closeBtn = new TFuncButton(this, QString(":/images/resource/icons/close.png"), 24, 24);

    QHBoxLayout *hLyt = new QHBoxLayout;
    hLyt->setMargin(0);
    hLyt->setSpacing(5);
    hLyt->addWidget(m_iconLabelTop, 0, Qt::AlignTop);
    hLyt->addWidget(m_textLabelTop, 0, Qt::AlignTop);
    hLyt->addStretch(10);
    hLyt->addWidget(m_playVideoBtn, 0, Qt::AlignRight | Qt::AlignTop);
    hLyt->addWidget(m_skinBtn, 0, Qt::AlignRight | Qt::AlignTop);
    hLyt->addWidget(m_menuBtn, 0, Qt::AlignRight | Qt::AlignTop);
    hLyt->addWidget(m_minBtn, 0, Qt::AlignRight | Qt::AlignTop);
    hLyt->addWidget(m_closeBtn, 0, Qt::AlignRight | Qt::AlignTop);

    m_scoreLabel = new TScoreLabel(this);
    m_scoreLabel->setNum(8, 6);
    m_tipLabel = new QLabel(this);
    m_tipLabel->setStyleSheet(QString("QLabel {font: 40px; color: #FFFFFFFF}"));
    m_tipLabel->setText(tr("建议每天体检"));
    QHBoxLayout *mLyt = new QHBoxLayout;
    mLyt->setMargin(20);
    mLyt->setSpacing(20);
    mLyt->addWidget(m_scoreLabel, 0, Qt::AlignVCenter | Qt::AlignLeft);
    mLyt->addWidget(m_tipLabel, 0, Qt::AlignVCenter);
    mLyt->addStretch(10);

    m_examBtn = new TFuncButton(this, QString(":/images/resource/icons/exam.png"), 212, 74);
    QHBoxLayout *bLyt = new QHBoxLayout;
    bLyt->setMargin(50);
    bLyt->addWidget(m_examBtn, 0, Qt::AlignHCenter | Qt::AlignBottom);
    QHBoxLayout *dLyt = new QHBoxLayout;
    dLyt->setMargin(10);


    QVBoxLayout *mainLyt = new QVBoxLayout;
    mainLyt->addLayout(hLyt);
    mainLyt->addLayout(mLyt);
    mainLyt->addLayout(bLyt);
    mainLyt->addLayout(dLyt);
    setLayout(mainLyt);

    m_aniamtion = new TWidgetAnimation(QRect(0, 0, 900, 440), QRect(0, -440, 900, 440), this);
}

TTopWidget::~TTopWidget()
{

}

void TTopWidget::startAnimation(bool isOut)
{
    m_aniamtion->startAnimation(isOut);
}

TWidgetAnimation *TTopWidget::getAnimation()
{
    return m_aniamtion;
}

TFuncButton *TTopWidget::getBtn(TTopWidget::btnType type)
{
    switch (type)
    {
    case playVideo:
        return m_playVideoBtn;
        break;
    case skin:
        return m_skinBtn;
        break;
    case menu:
        return m_menuBtn;
        break;
    case min:
        return m_minBtn;
        break;
    case close:
        return m_closeBtn;
        break;
    case exam:
        return m_examBtn;
        break;
    default:
        break;
    }
    return nullptr;
}

