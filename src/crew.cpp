#include "crew.h"

#include <QSet>
#include <QMessageBox>
#include <QSqlRelationalDelegate>


Crew::Crew(LogSql &sql) :
    _tvb(sql)
{
}

Crew::~Crew()
{
}

void Crew::setupData()
{
    _tvb.setTable("crew", crewTable);
    _tvb.addEntry(0, tr("Crew ID"), "", true);
    _tvb.addEntry(1, tr("First Name"), "", true);
    _tvb.addEntry(2, tr("Last Name"), "", true);
    _tvb.addEntry(3, tr("Company Phone"), "", true);
    _tvb.addEntry(4, tr("Company"), "", true, NULL,
                  new QSqlRelation("company", "id_cie", "name"));
    _tvb.setupConnections(pushButton_new,
                          pushButton_delete,
                          pushButton_revert,
                          pushButton_submit);
    _tvb.setupView();
}

// CREATE TABLE crew       (id_crew        VARCHAR(3) PRIMARY KEY,
//                         f_name          VARCHAR,
//                         l_name          VARCHAR,
//                         c_phone         VARCHAR,
//                         id_cie          VARCHAR(3));
