#include "mainwindow.h"
#include "histogramview.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_fileMenu(nullptr)
    , m_openAct(nullptr)
    , m_model(nullptr)
    , m_table(nullptr)
    , m_histogram(nullptr)
    , m_splitter(nullptr)
{
    createAction();
    createMenu();
    setupModel();
    setupView();
    setWindowTitle(tr("View Example"));
    resize(600, 600);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createAction()
{
    m_openAct = new QAction(tr("打开"), this);
    connect(m_openAct, SIGNAL(triggered()),
            this, SLOT(slotOpen()));
}

void MainWindow::createMenu()
{
    m_fileMenu = new QMenu(tr("文件"), this);
    if (m_openAct && m_fileMenu)
        m_fileMenu->addAction(m_openAct);
    QMenuBar *menuBar = QMainWindow::menuBar();
    if (menuBar)
        menuBar->addMenu(m_fileMenu);
}

void MainWindow::setupModel()
{
    m_model = new QStandardItemModel(4, 4, this);
    m_model->setHeaderData(0, Qt::Horizontal, tr("部门"));
    m_model->setHeaderData(1, Qt::Horizontal, tr("男"));
    m_model->setHeaderData(2, Qt::Horizontal, tr("女"));
    m_model->setHeaderData(3, Qt::Horizontal, tr("退休"));
}

void MainWindow::setupView()
{
    m_table = new QTableView(this);
    m_table->setModel(m_model);
    m_histogram = new HistogramView(this);
    m_histogram->setModel(m_model);
    QItemSelectionModel *selectionModel = new QItemSelectionModel(m_model, this);
    m_table->setSelectionModel(selectionModel);
    m_histogram->setSelectionModel(selectionModel);
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            m_table, SLOT(selectionChanged(QItemSelection, QItemSelection)));
    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            m_histogram, SLOT(selectionChanged(QItemSelection, QItemSelection)));

    m_splitter = new QSplitter(this);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_table);
    m_splitter->addWidget(m_histogram);
    //m_splitter->setFixedSize(600, 600);
    QWidget *widget = new QWidget(this);
    setCentralWidget(widget);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_splitter);
    widget->setLayout(mainLayout);
}

void MainWindow::openFile(QString path)
{
    if (!path.isEmpty())
    {
        QFile file(path);
        if (file.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream stream(&file);
            QString line;
            m_model->removeRows(0, m_model->rowCount(QModelIndex()),QModelIndex());
            int row = 0;
            do
            {
                line = stream.readLine();
                if (!line.isEmpty())
                {
                    m_model->insertRows(row, 1, QModelIndex());
                    QStringList pieces = line.split("，", QString::SkipEmptyParts);
                    m_model->setData(m_model->index(row, 0, QModelIndex()), pieces.value(0));
                    m_model->setData(m_model->index(row, 1, QModelIndex()), pieces.value(1));
                    m_model->setData(m_model->index(row, 2, QModelIndex()), pieces.value(2));
                    m_model->setData(m_model->index(row, 3, QModelIndex()), pieces.value(3));
                    row++;
                }
            } while (!line.isEmpty());
        }
        file.close();
    }
}

void MainWindow::slotOpen()
{
    QString filePath;
    filePath = QFileDialog::getOpenFileName(this, "打开", ".", "histogram files(*.txt)");
    if (!filePath.isEmpty())
        openFile(filePath);
}

