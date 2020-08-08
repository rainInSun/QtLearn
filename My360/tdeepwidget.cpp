#include "tdeepwidget.h"
#include "tdeeplowwidget.h"
#include "tdeeptopwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

TDeepWidget::TDeepWidget(QWidget *parent)
    : QWidget(parent)
    , m_deepTopBox(nullptr)
    , m_deepLowBox(nullptr)
{
    setFixedSize(900, 600);

    m_deepTopBox = new TDeepTopWidget(this);
    m_deepLowBox = new TDeepLowWidget(this);

    QVBoxLayout *vLyt = new QVBoxLayout(this);
    vLyt->setMargin(0);
    vLyt->setSpacing(0);
    vLyt->addWidget(m_deepTopBox);
    vLyt->addWidget(m_deepLowBox);

    setLayout(vLyt);
}

TDeepWidget::~TDeepWidget()
{

}

TDeepTopWidget *TDeepWidget::getDeepTopWidget()
{
    return m_deepTopBox;
}

TDeepLowWidget *TDeepWidget::getDeepLowWidget()
{
    return m_deepLowBox;
}
