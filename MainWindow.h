#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "WarehouseWindow.h"
#include "DocsWindow.h"


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WarehouseWindow *fWndWarehouse = nullptr;
    DocsWindow *fWndIncomeDocs = nullptr;
    DocsWindow *fWndCashVouchers = nullptr;

public slots:
    void showIncomeDocs();
    void showWarehouse();
    void showCashVouchers();
    void showFinancialReport();
};


#endif // MAINWINDOW_H
