#ifndef INCOMEDOCSWINDOW_H
#define INCOMEDOCSWINDOW_H


#include <QWidget>
#include "GoodsDocumentModel.h"


namespace Ui {
class IncomeDocsWindow;
}


class DocsWindow : public QWidget
{
    Q_OBJECT

private:
    Ui::IncomeDocsWindow *ui;
    GoodsDocumentModel *fDocsModel = nullptr;
    GoodsDocumentType fDocumentType;

public:
    explicit DocsWindow(QWidget *parent = 0);
    ~DocsWindow();

public slots:
    void refreshDocuments();
    void createNewDocument();
    void editSelectedDocument();
    void deleteSelectedDocument();
    void applySelectedDocument();
    void setDocumentType(const GoodsDocumentType &newDocType);
};


#endif // INCOMEDOCSWINDOW_H
