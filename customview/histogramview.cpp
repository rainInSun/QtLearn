#include "histogramview.h"

#include <QItemSelectionModel>
#include <QRegion>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QItemSelectionModel>
#include <QPainter>

HistogramView::HistogramView(QWidget *parent)
    : QAbstractItemView(parent)
    , m_selections(nullptr)
    , m_MRegionList(QList<QRegion>())
    , m_FRegionList(QList<QRegion>())
    , m_SRegionList(QList<QRegion>())
{

}

HistogramView::~HistogramView()
{

}

QRect HistogramView::visualRect(const QModelIndex &index) const
{

}

void HistogramView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{

}

QModelIndex HistogramView::indexAt(const QPoint &point) const
{
    QPoint newPoint(point.x(), point.y());
    QRegion region;
    QModelIndex index;
    QAbstractItemModel *presentModel = model();
    if (!presentModel)
        return index;
    //男列
    int cnt = 0;
    for (cnt = 0; cnt < m_MRegionList.size(); cnt++)
    {
        if (m_MRegionList.at(cnt).contains(newPoint))
        {
            //int row = m_MRegionList.indexOf(m_MRegionList.at(cnt));
            index = presentModel->index(cnt, 1, rootIndex());
            return index;
        }
    }
    //女列
    for (cnt = 0; cnt < m_FRegionList.size(); cnt++)
    {
        if (m_FRegionList.at(cnt).contains(newPoint))
        {
            //int row = m_FRegionList.indexOf(m_FRegionList.at(cnt));
            index = presentModel->index(cnt, 2, rootIndex());
            return index;
        }
    }
    //合计列
    for (cnt = 0; cnt < m_SRegionList.size(); cnt++)
    {
        if (m_SRegionList.at(cnt).contains(newPoint))
        {
            //int row = m_FRegionList.indexOf(m_FRegionList.at(cnt));
            index = presentModel->index(cnt, 3, rootIndex());
            return index;
        }
    }
    return QModelIndex();
}

void HistogramView::setSelectionModel(QItemSelectionModel *selectionModel)
{
    if (selectionModel)
        m_selections = selectionModel;
}

void HistogramView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(viewport());
    painter.setPen(Qt::black);
    //y坐标轴
    int x0 = 40;
    int y0 = 250;
    painter.drawLine(x0, y0, 40, 30);
    painter.drawLine(38, 32, 40, 30);
    painter.drawLine(40, 30, 42, 32);
    painter.drawText(20, 30, tr("人数"));
    for (int i = 1; i < 5; i++)
    {
        painter.drawLine(-1, -i * 50, 1, -i * 50);
        painter.drawText(-20, -i * 50, tr("%1").arg(i * 5));
    }
    //x坐标轴
    painter.drawLine(x0, y0, 540, 250);
    painter.drawLine(538, 248, 540, 250);
    painter.drawLine(540, 250, 538, 252);
    painter.drawText(545, 250, tr("部门"));
    int posD = x0 + 20;
    int row;
    QAbstractItemModel *presentModel = model();
    if (!presentModel)
        return;
    for (row = 0; row < presentModel->rowCount(rootIndex()); row++)
    {
        QModelIndex index = presentModel->index(row, 0, rootIndex());
        QString dep = presentModel->data(index).toString();
        painter.drawText(posD, y0 + 20, dep);
        posD += 50;
    }
    //完成表格第1列数据的柱状图绘制
    int posM = x0 + 20;
    m_MRegionList.clear();
    for (row = 0; row < presentModel->rowCount(rootIndex()); row++)
    {
        QModelIndex index = presentModel->index(row, 1, rootIndex());
        int male = presentModel->data(index).toDouble();
        int width = 10;
        if (m_selections->isSelected(index))
            painter.setBrush(QBrush(Qt::blue, Qt::Dense3Pattern));
        else
            painter.setBrush(QBrush(Qt::blue));
        painter.drawRect(QRect(posM, y0 - male * 10, width, male * 10));
        QRegion regionM(posM, y0 - male * 10, width, male * 10);
        m_MRegionList.insert(row, regionM);
        posM += 50;
    }
    //完成表格第二列数据的柱状图绘制
    int posF = x0 + 30;
    m_FRegionList.clear();
    for (row = 0; row < presentModel->rowCount(rootIndex()); row++)
    {
        QModelIndex index = presentModel->index(row, 2, rootIndex());
        int female = presentModel->data(index).toDouble();
        int width = 10;
        if (m_selections->isSelected(index))
            painter.setBrush(QBrush(Qt::red, Qt::Dense3Pattern));
        else
            painter.setBrush(QBrush(Qt::red));
        painter.drawRect(QRect(posF, y0 - female * 10, width, female * 10));
        QRegion regionF(posF, y0 - female * 10, width, female * 10);
        m_FRegionList.insert(row, regionF);
        posF += 50;
    }
    //完成表格第三列数据的柱状图绘制
    int posS = x0 + 40;
    m_SRegionList.clear();
    for (row = 0; row < presentModel->rowCount(rootIndex()); row++)
    {
        QModelIndex index = presentModel->index(row, 3, rootIndex());
        int retire = presentModel->data(index).toDouble();
        int width = 10;
        if (m_selections->isSelected(index))
            painter.setBrush(QBrush(Qt::green, Qt::Dense3Pattern));
        else
            painter.setBrush(QBrush(Qt::green));
        painter.drawRect(posS, y0 - retire * 10, width, retire * 10);
        QRegion regionS(posS, y0 - retire * 10, width, retire * 10);
        m_SRegionList.insert(row, regionS);
        posS += 50;
    }
}

void HistogramView::mousePressEvent(QMouseEvent *event)
{
    if (event)
    {
        QAbstractItemView::mousePressEvent(event);
        setSelection(QRect(event->pos().x(), event->pos().y(), 1, 1),
                     QItemSelectionModel::SelectCurrent);
    }
}

QRegion HistogramView::itemRegion(QModelIndex index)
{
    QRegion region;
    if (1 == index.column())
        region = m_MRegionList.at(index.row());
    if (2 == index.column())
        region = m_FRegionList.at(index.row());
    if (3 == index.column())
        region = m_SRegionList.at(index.row());
    return region;
}

QModelIndex HistogramView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                      Qt::KeyboardModifiers modifiers)
{

}

int HistogramView::horizontalOffset() const
{

}

int HistogramView::verticalOffset() const
{

}

bool HistogramView::isIndexHidden(const QModelIndex &index) const
{

}

void HistogramView::setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    QAbstractItemModel *presentModel = model();
    if (!presentModel)
        return;
    int rows = presentModel->rowCount(rootIndex());
    int columns = presentModel->columnCount(rootIndex());
    QModelIndex selectIndex;
    for (int row = 0; row < rows; row++)
    {
        for (int column = 1; column < columns; column++)
        {
            QModelIndex index = presentModel->index(row, column, rootIndex());
            QRegion region = itemRegion(index);
            if (!region.intersected(rect).isEmpty())
                selectIndex = index;
        }
    }
    if (selectIndex.isValid())
    {
        m_selections->select(selectIndex, command);
    }
    else
    {
        QModelIndex noIndex;
        m_selections->select(noIndex, command);
    }
}

QRegion HistogramView::visualRegionForSelection(const QItemSelection &selection) const
{

}

void HistogramView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QWidget *widget = viewport();
    if (widget)
        widget->update();
}

void HistogramView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                                const QVector<int> &roles)
{
    QAbstractItemView::dataChanged(topLeft, bottomRight);
    QWidget *widget = viewport();
    if (widget)
        widget->update();
}
