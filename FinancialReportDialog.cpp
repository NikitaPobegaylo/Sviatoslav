#include "FinancialReportDialog.h"
#include "ui_FinancialReportDialog.h"
#include "ShopInfoStorage/ShopInfoStorage.h"


FinancialReportDialog::FinancialReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinancialReportDialog)
{
    ui->setupUi(this);

    ui->dtDateStart->setDate(QDate::currentDate().addMonths(-1));
    ui->dtDateEnd->setDate(QDate::currentDate());

    connect(ui->dtDateStart, SIGNAL(dateChanged(QDate)), SLOT(reportDateChanged(QDate)));
    connect(ui->dtDateEnd, SIGNAL(dateChanged(QDate)), SLOT(reportDateChanged(QDate)));

    refreshData();
}


FinancialReportDialog::~FinancialReportDialog()
{
    delete ui;
}


void FinancialReportDialog::reportDateChanged(QDate)
{
    refreshData();
}


void FinancialReportDialog::refreshData()
{
    QDateTime dateStart = ui->dtDateStart->dateTime();
    QDateTime dateEnd = ui->dtDateEnd->dateTime().addDays(1);
    double moneyIncome = ShopInfoStorage::currentStorage->getMoneyIncome(dateStart, dateEnd);
    double moneyOutcome = ShopInfoStorage::currentStorage->getMoneyOutcome(dateStart, dateEnd);
    ui->lblMoneyIncome->setText(tr("Доходы: %1").arg(moneyIncome));
    ui->lblMoneyOutcome->setText(tr("Расходы: %1").arg(moneyOutcome));
}
