#-------------------------------------------------
#
# Project created by QtCreator 2018-04-20T13:18:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ShopAutomationSystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    AuthorizationDialog.cpp \
    Authorization/AuthSystem.cpp \
    Authorization/SQLAuthSystem.cpp \
    Goods.cpp \
    GoodsModel.cpp \
    CountableGoods.cpp \
    CountableGoodsModel.cpp \
    ShopInfoStorage/ShopInfoStorage.cpp \
    ShopInfoStorage/SqlShopInfoStorage.cpp \
    GoodsIncomeDoc.cpp \
    GoodsIncomeDocModel.cpp \
    GoodsDocument.cpp \
    GoodsDocumentModel.cpp \
    WarehouseWindow.cpp \
    DocsWindow.cpp \
    EditGoodsDocumentDialog.cpp \
    FinancialReportDialog.cpp

HEADERS += \
        MainWindow.h \
    AuthorizationDialog.h \
    Authorization/AuthSystem.h \
    Authorization/SQLAuthSystem.h \
    Goods.h \
    GoodsModel.h \
    CountableGoods.h \
    CountableGoodsModel.h \
    ShopInfoStorage/ShopInfoStorage.h \
    ShopInfoStorage/SqlShopInfoStorage.h \
    GoodsIncomeDoc.h \
    GoodsIncomeDocModel.h \
    GoodsDocument.h \
    GoodsDocumentModel.h \
    WarehouseWindow.h \
    DocsWindow.h \
    EditGoodsDocumentDialog.h \
    FinancialReportDialog.h

FORMS += \
        MainWindow.ui \
    AuthorizationDialog.ui \
    IncomeDocsWindow.ui \
    EditGoodsIncomeDocDialog.ui \
    WarehouseWindow.ui \
    FinancialReportDialog.ui

RESOURCES += \
    resources.qrc
