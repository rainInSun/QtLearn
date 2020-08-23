#ifndef HISTOGRAMVIEW_H
#define HISTOGRAMVIEW_H

#include <QAbstractItemView>

class QItemSelectionModel;
class QRegion;
class QMouseEvent;
class QPaintEvent;
class QItemSelectionModel;

class HistogramView : public QAbstractItemView
{
    Q_OBJECT
public:
    HistogramView(QWidget *parent = nullptr);
    virtual ~HistogramView();

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &point) const override;
    void setSelectionModel(QItemSelectionModel *selectionModel) override;
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    QRegion itemRegion(QModelIndex index);

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;
    bool isIndexHidden(const QModelIndex &index) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;

protected slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles = QVector<int>()) override;

private:
    QItemSelectionModel *m_selections;
    QList<QRegion> m_MRegionList;
    QList<QRegion> m_FRegionList;
    QList<QRegion> m_SRegionList;
};

#endif // HISTOGRAMVIEW_H
