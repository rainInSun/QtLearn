#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStandardItemModel;
class QTableView;
class QMenuBar;
class QMenu;
class QAction;
class QSplitter;
class HistogramView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createAction();
    void createMenu();
    void setupModel();
    void setupView();
    void openFile(QString path);

private slots:
    void slotOpen();

private:
    QMenu *m_fileMenu;
    QAction *m_openAct;
    QStandardItemModel *m_model;
    QTableView *m_table;
    HistogramView *m_histogram;
    QSplitter *m_splitter;
};
#endif // MAINWINDOW_H
