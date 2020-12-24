#include "DocsWindow.h"
#include "ui_IncomeDocsWindow.h"
#include "ShopInfoStorage/ShopInfoStorage.h"
#include "EditGoodsDocumentDialog.h"
#include "GoodsIncomeDocModel.h"
#include <QMessageBox>
#include <QDebug>


DocsWindow::DocsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IncomeDocsWindow)
{
    ui->setupUi(this);

    connect(ui->tbRefresh, SIGNAL(pressed()), SLOT(refreshDocuments()));
    connect(ui->tbNewIncomeDoc, SIGNAL(pressed()), SLOT(createNewDocument()));
    connect(ui->tbEditIncomeDoc, SIGNAL(pressed()), SLOT(editSelectedDocument()));
    connect(ui->tbDeleteIncomeDoc, SIGNAL(pressed()), SLOT(deleteSelectedDocument()));
    connect(ui->tbApplyIncomeDoc, SIGNAL(pressed()), SLOT(applySelectedDocument()));

    setDocumentType(Income);
}


DocsWindow::~DocsWindow()
{
    delete ui;
}


void DocsWindow::refreshDocuments()
{
    // Удаляем старые объекты приходных документов
    QList<GoodsDocument*> oldDocs = fDocsModel->documents();
    foreach(GoodsDocument* doc, oldDocs) {
        if (doc != nullptr)
            delete doc;
    }

    // Загружаем актуальный перечень приходных документов
    ShopInfoStorage *storage = ShopInfoStorage::currentStorage;
    fDocsModel->setDocuments(storage->getDocuments(fDocumentType, fDocsModel));
    if (!storage->lastError().isNull())
        QMessageBox::critical(this, tr("Ошибка загрузки перечня документов"), storage->lastError());
    ui->tvIncomeDocs->setModel(nullptr);
    ui->tvIncomeDocs->setModel(fDocsModel);
}


void DocsWindow::createNewDocument()
{
    EditGoodsDocumentDialog* dlg = new EditGoodsDocumentDialog(this);
    dlg->setDocument(ShopInfoStorage::currentStorage->createNewDocument(fDocumentType, dlg));
    dlg->setWindowTitle((fDocumentType == Income)?tr("Оформление прихода товаров"):tr("Продажа товаров"));
    if (dlg->exec() == QDialog::Accepted) {
        ShopInfoStorage::currentStorage->saveDocument(dlg->document());
        if (!ShopInfoStorage::currentStorage->lastError().isNull())
            QMessageBox::critical(this, tr("Ошибка сохранения документа"), ShopInfoStorage::currentStorage->lastError());
        refreshDocuments();
    }
    delete dlg;
}


void DocsWindow::editSelectedDocument()
{
    QModelIndex curIdx = ui->tvIncomeDocs->currentIndex();
    if (!curIdx.isValid()) {
        QMessageBox::warning(this, tr("Редактирование документа"), tr("Не выбран документ!"));
        return;
    }

    EditGoodsDocumentDialog* dlg = new EditGoodsDocumentDialog(this);
    dlg->setDocument(fDocsModel->documents()[curIdx.row()]);
    dlg->setWindowTitle((fDocumentType == Income)?tr("Оформление прихода товаров"):tr("Продажа товаров"));
    if (dlg->exec() == QDialog::Accepted) {
        ShopInfoStorage::currentStorage->saveDocument(dlg->document());
        if (!ShopInfoStorage::currentStorage->lastError().isNull())
            QMessageBox::critical(this, tr("Ошибка изменения приходного документа"), ShopInfoStorage::currentStorage->lastError());
        refreshDocuments();
    }
    delete dlg;
}


void DocsWindow::deleteSelectedDocument()
{
    QModelIndex curIdx = ui->tvIncomeDocs->currentIndex();
    if (!curIdx.isValid()) {
        QMessageBox::warning(this, tr("Удаление документа"), tr("Не выбран документ!"));
        return;
    }

    GoodsDocument *delDoc = fDocsModel->documents()[curIdx.row()];
    int userConfirm = QMessageBox::question(this, tr("Удаление документа"),
                                            tr("Вы действительно хотите удалить документ №%1?").arg(delDoc->id()));
    if (userConfirm == QMessageBox::Yes) {
        ShopInfoStorage::currentStorage->deleteDocument(delDoc->id());
        if (!ShopInfoStorage::currentStorage->lastError().isNull())
            QMessageBox::critical(this, tr("Ошибка удаления документа"), ShopInfoStorage::currentStorage->lastError());
        refreshDocuments();
    }
}


void DocsWindow::applySelectedDocument()
{
    QModelIndex curIdx = ui->tvIncomeDocs->currentIndex();
    if (!curIdx.isValid()) {
        QMessageBox::warning(this, tr("Применение документа"), tr("Не выбран документ!"));
        return;
    }

    GoodsDocument *applyDoc = fDocsModel->documents()[curIdx.row()];
    int userConfirm = QMessageBox::question(this, tr("Применение документа"),
                                            tr("Вы действительно хотите применить документ №%1?").arg(applyDoc->id()));
    if (userConfirm == QMessageBox::Yes) {
        ShopInfoStorage::currentStorage->applyDocument(applyDoc);
        if (!ShopInfoStorage::currentStorage->lastError().isNull())
            QMessageBox::critical(this, tr("Ошибка применения приходного документа"), ShopInfoStorage::currentStorage->lastError());
        refreshDocuments();
    }
}


void DocsWindow::setDocumentType(const GoodsDocumentType &newDocType)
{
    if (fDocumentType != newDocType) {
        fDocumentType = newDocType;

        // Пересоздаем модель под тип документов
        if (fDocsModel != nullptr)
            delete fDocsModel;
        switch (fDocumentType) {
        case Income:
            fDocsModel = new GoodsIncomeDocModel(ui->tvIncomeDocs);
            break;
        default:
            fDocsModel = new GoodsDocumentModel(ui->tvIncomeDocs);
            break;
        }

        refreshDocuments();
    }
}
