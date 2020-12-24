#include "EditGoodsDocumentDialog.h"
#include "ui_EditGoodsIncomeDocDialog.h"
#include <QDebug>


EditGoodsDocumentDialog::EditGoodsDocumentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditGoodsIncomeDocDialog)
{
    ui->setupUi(this);

    fGoodsModel = new CountableGoodsModel(ui->tvGoods);
    ui->tvGoods->setModel(fGoodsModel);

    connect(ui->tbNewGoods, SIGNAL(pressed()), SLOT(addNewGoodsRow()));
    connect(ui->tbSave, SIGNAL(pressed()), SLOT(accept()));
    connect(ui->tbCancel, SIGNAL(pressed()), SLOT(reject()));

    refreshData();
}


EditGoodsDocumentDialog::~EditGoodsDocumentDialog()
{
    delete ui;
}


GoodsDocument *EditGoodsDocumentDialog::document() const
{
    return fDocument;
}


void EditGoodsDocumentDialog::refreshData()
{
    if (fDocument != nullptr) {
        GoodsIncomeDoc *incomeDoc = qobject_cast<GoodsIncomeDoc * const>(fDocument);
        if (incomeDoc != nullptr)
            ui->edtProviderName->setText(incomeDoc->providerName());
        ui->dtCreateDate->setDateTime(fDocument->createDate());
        fGoodsModel->setGoods(fDocument->goods());
        ui->tvGoods->setModel(nullptr);
        ui->tvGoods->setModel(fGoodsModel);
    }
}


void EditGoodsDocumentDialog::setDocument(GoodsDocument * const &newDocument)
{
    fDocument = newDocument;
    bool isIncomeDoc = qobject_cast<GoodsIncomeDoc * const>(fDocument) != nullptr;
    ui->lblProviderName->setVisible(isIncomeDoc);
    ui->edtProviderName->setVisible(isIncomeDoc);
    refreshData();
}


void EditGoodsDocumentDialog::addNewGoodsRow()
{
    CountableGoods* newGoods = new CountableGoods(fDocument);
    fDocument->addGoods(newGoods);
    fGoodsModel->addGoods(newGoods);
}


void EditGoodsDocumentDialog::accept()
{
    GoodsIncomeDoc *incomeDoc = qobject_cast<GoodsIncomeDoc * const>(fDocument);
    if (incomeDoc != nullptr)
        incomeDoc->setProviderName(ui->edtProviderName->text());
    QDialog::accept();
}
