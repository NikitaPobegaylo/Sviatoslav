#ifndef EDITGOODSINCOMEDOCDIALOG_H
#define EDITGOODSINCOMEDOCDIALOG_H


#include <QDialog>
#include "GoodsIncomeDoc.h"
#include "CountableGoodsModel.h"


namespace Ui {
class EditGoodsIncomeDocDialog;
}


class EditGoodsDocumentDialog : public QDialog
{
    Q_OBJECT

private:
    Ui::EditGoodsIncomeDocDialog *ui;
    GoodsDocument* fDocument = nullptr;
    CountableGoodsModel* fGoodsModel;

public:
    explicit EditGoodsDocumentDialog(QWidget *parent = 0);
    ~EditGoodsDocumentDialog();

    GoodsDocument *document() const;

public slots:
    void refreshData();
    void setDocument(GoodsDocument * const &newDocument);
    void addNewGoodsRow();
    void accept();
};


#endif // EDITGOODSINCOMEDOCDIALOG_H
