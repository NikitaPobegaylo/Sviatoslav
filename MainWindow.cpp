#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DocsWindow.h"
#include <QVBoxLayout>
#include "WarehouseWindow.h"
#include "FinancialReportDialog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);

    connect(ui->actIncomeDocs, SIGNAL(triggered()), SLOT(showIncomeDocs()));
    connect(ui->actCashVouchers, SIGNAL(triggered()), SLOT(showCashVouchers()));
    connect(ui->actWarehouse, SIGNAL(triggered()), SLOT(showWarehouse()));
    connect(ui->actShowFinancialReport, SIGNAL(triggered()), SLOT(showFinancialReport()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showIncomeDocs()
{
    if (fWndIncomeDocs == nullptr) {
        fWndIncomeDocs = new DocsWindow(ui->layoutStack);
        fWndIncomeDocs->setDocumentType(Income);
    }
    ui->layoutStack->addWidget(fWndIncomeDocs);
    ui->layoutStack->setCurrentWidget(fWndIncomeDocs);
    fWndIncomeDocs->refreshDocuments();
}


void MainWindow::showWarehouse()
{
    if (fWndWarehouse == nullptr)
        fWndWarehouse = new WarehouseWindow(ui->layoutStack);
    ui->layoutStack->addWidget(fWndWarehouse);
    ui->layoutStack->setCurrentWidget(fWndWarehouse);
    fWndWarehouse->refreshData();
}


void MainWindow::showCashVouchers()
{
    if (fWndCashVouchers == nullptr) {
        fWndCashVouchers = new DocsWindow(ui->layoutStack);
        fWndCashVouchers->setDocumentType(CashVoucher);
    }
    ui->layoutStack->addWidget(fWndCashVouchers);
    ui->layoutStack->setCurrentWidget(fWndCashVouchers);
    fWndCashVouchers->refreshDocuments();
}


void MainWindow::showFinancialReport()
{
    FinancialReportDialog *dlg = new FinancialReportDialog(this);
    dlg->exec();
    delete dlg;
}
