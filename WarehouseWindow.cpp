#include "WarehouseWindow.h"
#include "ui_WarehouseWindow.h"
#include "CountableGoods.h"
#include "ShopInfoStorage/ShopInfoStorage.h"
#include <QMessageBox>


WarehouseWindow::WarehouseWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarehouseWindow)
{
    ui->setupUi(this);

    fGoodsModel = new CountableGoodsModel(ui->tvWarehouse);
    fGoodsModel->setNameReadOnly(true);
    fGoodsModel->setBarcodesReadOnly(true);
    fGoodsModel->setGoodsCountReadOnly(true);
    ui->tvWarehouse->setModel(fGoodsModel);

    connect(ui->tbRefresh, SIGNAL(pressed()), SLOT(refreshData()));

    refreshData();
}


WarehouseWindow::~WarehouseWindow()
{
    delete ui;
}


void WarehouseWindow::goodsPriceChanged()
{
    CountableGoods *g = qobject_cast<CountableGoods *>(sender());
    if (g != nullptr) {
        ShopInfoStorage *storage = ShopInfoStorage::currentStorage;
        storage->setGoodsPrice(g->id(), g->price());
        if (!storage->lastError().isNull())
            QMessageBox::critical(this, tr("Ошибка изменения цены товара"), storage->lastError());
    }
}


void WarehouseWindow::refreshData()
{
    // Удаляем старые объекты товаров
    QList<Goods *> oldGoods = fGoodsModel->goods();
    foreach(Goods* g, oldGoods) {
        if (g != nullptr)
            delete g;
    }

    // Загружаем актуальную информацию о состоянии склада
    ShopInfoStorage *storage = ShopInfoStorage::currentStorage;
    fGoodsModel->setGoods(storage->getWarehouse(fGoodsModel));
    if (!storage->lastError().isNull())
        QMessageBox::critical(this, tr("Ошибка загрузки склада"), storage->lastError());

    foreach (Goods* g, fGoodsModel->goods()) {
        connect(g, SIGNAL(priceChanged()), SLOT(goodsPriceChanged()));
    }

    ui->tvWarehouse->setModel(nullptr);
    ui->tvWarehouse->setModel(fGoodsModel);
}
