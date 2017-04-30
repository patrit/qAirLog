#include "companies.h"

#include <QSet>
#include <QMessageBox>
#include <QSqlRelationalDelegate>


//
Companies::Companies(LogSql &sql) :
   _tvb(sql)
{
}
//

Companies::~Companies()
{
}

void Companies::setupData()
{
   _tvb.setTable("company", companiesTable);
   _tvb.addEntry(0, tr("Company ID"), "", true, id_lineEdit);
   _tvb.addEntry(1, tr("Name"), "", true, name_lineEdit);
   _tvb.addEntry(2, tr("Phone"), "", true, phone_lineEdit);
   _tvb.addEntry(3, tr("Fax"), "", true, fax_lineEdit);
   _tvb.addEntry(4, tr("Mail"), "", true, mail_lineEdit);
   _tvb.addEntry(5, tr("SITA"), "", false, sita_lineEdit);
   _tvb.addEntry(6, tr("VHF"), "", false, vhf_lineEdit);
   _tvb.addEntry(7, tr("Address"), "", false, address_lineEdit);
   _tvb.addEntry(8, tr("ZIP-Code"), 0, false, zip_spinBox);
   _tvb.addEntry(9, tr("City"), "", false);
   _tvb.addEntry(10, tr("Country"), "", false, country_comboBox,
      new QSqlRelation("countries", "id", "name"));
   _tvb.addEntry(11, tr("Airport"), "", false, airport_comboBox,
      new QSqlRelation("airports", "icao", "name"));
   _tvb.setupConnections(pushButton_new,
                              pushButton_delete,
                              pushButton_revert,
                              pushButton_submit);
   _tvb.setupView();
}


/*
CREATE TABLE company    (id_cie         VARCHAR(3) PRIMARY KEY,
                        name            VARCHAR,
                        phone           VARCHAR,
                        fax             VARCHAR,
                        mail            VARCHAR,
                        sita            VARCHAR(7),
                        vhf             VARCHAR(7),
                        address         VARCHAR,
                        zip_code        INTEGER,
                        city            VARCHAR,
                        country         VARCHAR,
                        airport         VARCHAR(4));*/
