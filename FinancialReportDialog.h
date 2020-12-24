#ifndef FINANCIALREPORTDIALOG_H
#define FINANCIALREPORTDIALOG_H


#include <QDialog>
#include <QDate>


namespace Ui {
class FinancialReportDialog;
}

class FinancialReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FinancialReportDialog(QWidget *parent = 0);
    ~FinancialReportDialog();

private:
    Ui::FinancialReportDialog *ui;

private slots:
    void reportDateChanged(QDate);

public slots:
    void refreshData();
};


#endif // FINANCIALREPORTDIALOG_H
