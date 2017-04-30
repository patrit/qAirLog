#include "airports.h"
#include "logsql.h"

#include <QSet>
#include <QMessageBox>
#include <QSqlRelationalDelegate>
#include <QRegExpValidator>

//
Airports::Airports(LogSql &sql) :
   _tvb(sql)
{
}
//

Airports::~Airports()
{
}

void Airports::setupData()
{
   _tvb.setTable("airports", airportsTable);
   _tvb.addEntry(0, tr("ICAO"), "", true, icao_lineEdit);
   _tvb.addEntry(1, tr("IATA"), "", true, iata_lineEdit);
   _tvb.addEntry(2, tr("Name"), "", true, name_lineEdit);
   _tvb.addEntry(3, tr("City"), "", true, city_lineEdit);
   _tvb.addEntry(4, tr("Country"), "", true, country_comboBox,
      new QSqlRelation("countries", "id", "name"));
   _tvb.addEntry(5, tr("Latitude Deg"), 0, false, latitude_spinBox_deg);
   _tvb.addEntry(6, tr("Latitude Min"), 0, false, latitude_spinBox_min);
   _tvb.addEntry(7, tr("Latitude Sec"), 0, false, latitude_spinBox_sec);
   _tvb.addEntry(8, tr("Latitude Dir"), "", false, latitude_lineEdit_dir);
   _tvb.addEntry(9, tr("Longitude Deg"), 0, false, longitude_spinBox_deg);
   _tvb.addEntry(10, tr("Longitude Min"), 0, false, longitude_spinBox_min);
   _tvb.addEntry(11, tr("Longitude Sec"), 0, false, longitude_spinBox_sec);
   _tvb.addEntry(12, tr("Longitude Dir"), "", false, longitude_lineEdit_dir);
   _tvb.addEntry(13, tr("Altitude"), 0, false, altitude_spinBox);
   _tvb.setupConnections(pushButton_new,
                         pushButton_delete,
                         pushButton_revert,
                         pushButton_submit);
   _tvb.setupView();
}

