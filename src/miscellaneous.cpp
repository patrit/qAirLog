#include "miscellaneous.h"
#include "ui_miscellaneous.h"
#include "logsql.h"

#include <qt5/QtCore/QSet>
#include <qt5/QtWidgets/QMessageBox>


Miscellaneous::Miscellaneous(LogSql &sql) :
    _countries(sql),
    _logBook(sql)
{
}

Miscellaneous::~Miscellaneous()
{
}

void Miscellaneous::setupData()
{
    //Test Slot
    connect( pushButton, SIGNAL(clicked()), this, SLOT(test()) );

    //REAL STUFF
    _countries.setTable("countries", countriesTable);
    _countries.addEntry(0, tr("Id"), "", true);
    _countries.addEntry(1, tr("Country Name"), "", true);
    _countries.setupConnections(pushButton_new,
                                pushButton_delete,
                                pushButton_revert,
                                pushButton_submit);
    _countries.setupView();


    /*
    _logBook.setTable("books", logBookTable);
    _logBook.addEntry(0, tr("Book"), "", true);
    _logBook.addEntry(1, tr("Pages"), "", true);
    _logBook.addEntry(2, tr("Rows"), "", true);
    _logBook.setupConnections(pushButton_new_2,
                              pushButton_delete_2,
                              pushButton_revert_2,
                              pushButton_submit_2);
                              */
    _logBook.setupView();
}

void Miscellaneous::test()
{
}
