#ifndef WAREHOUSEWINDOW_H
#define WAREHOUSEWINDOW_H


#include <QWidget>
#include "CountableGoodsModel.h"


namespace Ui {
class WarehouseWindow;
}


class WarehouseWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WarehouseWindow(QWidget *parent = 0);
    ~WarehouseWindow();

private:
    Ui::WarehouseWindow *ui;
    CountableGoodsModel* fGoodsModel;

private slots:
    void goodsPriceChanged();

public slots:
    void refreshData();
};


#endif // WAREHOUSEWINDOW_H
