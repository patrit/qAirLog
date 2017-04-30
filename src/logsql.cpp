#include "logsql.h"

#include <iostream>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QTextStream>
#include <qt5/QtWidgets/QMessageBox>
#include <qt5/QtNetwork/QNetworkAccessManager>
#include <qt5/QtNetwork/QNetworkRequest>
#include "csv.h"
//
LogSql::LogSql( QString dbName ) :
   _db(QSqlDatabase::addDatabase("QSQLITE"))
{
   _db.setDatabaseName(dbName);
   _db.open();
   checkTables();
}

//
LogSql::~LogSql()
{
   _db.close();
}


void LogSql::checkTables()
{
   struct {
      QString name;
      QString table;
   } const tables[] = {
      { "fltLog", "id_flt         INTEGER PRIMARY KEY AUTOINCREMENT,"\
                  "flt_date       DATE NOT NULL,"\
                  "dep_apt        VARCHAR(4) NOT NULL,"\
                  "dep_time       TIME NOT NULL,"\
                  "arr_apt        VARCHAR(4) NOT NULL,"\
                  "arr_time       TIME NOT NULL,"\
                  "ac_reg         VARCHAR(5),"\
                  "pic_3lc        VARCHAR(3) NOT NULL,"\
                  "flt_rules      VARCHAR(1) NOT NULL,"\
                  "ldg_day        INTEGER,"\
                  "ldg_nit        INTEGER,"\
                  "t_sse          TIME,"\
                  "t_sme          TIME,"\
                  "t_mcc          TIME,"\
                  "t_tot          TIME,"\
                  "t_nit          TIME,"\
                  "t_ifr          TIME,"\
                  "t_pic          TIME,"\
                  "t_copi         TIME,"\
                  "t_dual         TIME,"\
                  "t_inst         TIME,"\
                  "remarks        TEXT" },
      { "simLog", "id_sim         INTEGER PRIMARY KEY AUTOINCREMENT,"\
                  "date           DATE NOT NULL,"\
                  "type           VARCHAR NOT NULL,"\
                  "authno         VARCHAR NOT NULL,"\
                  "level          VARCHAR(1) NOT NULL,"\
                  "t_trainee      TIME NOT NULL,"\
                  "t_sfisfe       TIME NOT NULL,"\
                  "aut_nr         VARCHAR NOT NULL,"\
                  "remarks        TEXT" },
      {"sims",    "id              INTEGER PRIMARY KEY AUTOINCREMENT,"\
                  "authno          VARCHAR,"\
                  "type            VARCHAR NOT NULL,"\
                  "level           VARCHAR(1) NOT NULL"},
      {"airports", "icao           VARCHAR(4) PRIMARY KEY NOT NULL,"\
                   "iata           VARCHAR(3),"\
                   "name           VARCHAR,"\
                   "city           VARCHAR,"\
                   "country        VARCHAR,"\
                   "latDeg         INTEGER(2),"\
                   "latMin         INTEGER(2),"\
                   "latSec         INTEGER(2),"\
                   "latDir         VARCHAR(1),"\
                   "longDeg        INTEGER(2),"\
                   "longMin        INTEGER(2),"\
                   "longSec        INTEGER(2),"\
                   "longDir        VARCHAR(1),"\
                   "altitude       INTEGER(4)" },
      {"aircraft", "registration   VARCHAR(5) PRIMARY KEY NOT NULL,"\
                   "model          VARCHAR(4) NOT NULL,"\
                   "variant        VARCHAR,"\
                   "ac_func        VARCHAR(3) NOT NULL,"\
                   "operation      VARCHAR,"\
                   "msn            INTEGER,"\
                   "dom            INTEGER,"\
                   "doi            INTEGER,"\
                   "mtom           INTEGER,"\
                   "mlm            INTEGER,"\
                   "mzfm           INTEGER,"\
                   "max_payload    INTEGER,"\
                   "max_range      INTEGER,"\
                   "manufacturer   TEXT,"\
                   "picture        BLOB" },
      { "crew", "id_crew        VARCHAR(3) PRIMARY KEY NOT NULL,"\
                "f_name         VARCHAR,"\
                "l_name         VARCHAR,"\
                "c_phone        VARCHAR,"\
                "id_cie         VARCHAR(3)" },
      { "company", "id_cie         VARCHAR(3) PRIMARY KEY NOT NULL,"\
                   "name           VARCHAR,"\
                   "phone          VARCHAR,"\
                   "fax            VARCHAR,"\
                   "mail           VARCHAR,"\
                   "sita           VARCHAR(7),"\
                   "vhf            VARCHAR(7),"\
                   "address        VARCHAR,"\
                   "zip_code       INTEGER,"\
                   "city           VARCHAR,"\
                   "country        VARCHAR,"\
                   "airport        VARCHAR(4)" },
      { "flt_rules", "rules          VARCHAR(1) PRIMARY KEY NOT NULL,"\
                     "description    TEXT,"\
                     //checkbox wäri nätt...
                     "req_time       BOOLEAN" },
      { "ac_func", "func           VARCHAR(3) PRIMARY KEY NOT NULL,"\
                   "description    VARCHA(time.hour()+(time.minute()/60)R NOT NULL,"\
                   "type           VARCHAR NOT NULL" },
      { "ac_ops", "operation      VARCHAR(7) PRIMARY KEY NOT NULL,"\
                  "description    TEXT(40)" },
      { "pil_func", "function       VARCHAR(10) PRIMARY KEY NOT NULL,"\
                    //SIM oder FLT
                    "related        VARCHAR(3),"\
                    //PIC, COPI, DUAL, INSTR, TRAINEE
                    "logAs          VARCHAR(7)" },
      { "countries", "id       VARCHAR PRIMARY KEY NOT NULL,"\
                     "name     TEXT" },
      { "books",     "book     INTEGER,"\
                     "pages    INTEGER,"\
                     "rows     INTEGER" },
   };

   for( uint i=0; i< (sizeof tables / sizeof *tables); ++i )
   {
      QSqlQuery query(_db);
      QString const& str = QString("%1 %2 (%3);")
         .arg("CREATE TABLE IF NOT EXISTS")
         .arg(tables[i].name)
         .arg(tables[i].table);
      const bool retVal = query.exec(str);
      if( !retVal )
         QMessageBox::critical(NULL,
            tr("Failed checking database tables"),
            tr("Error checking tables in the database:\%1").arg(query.lastError().text()));
   }
   //this->updateOnline("http://openflights.svn.sourceforge.net/viewvc/openflights/openflights/data/airports.dat","");
}
void LogSql::updateOnline(QString url,QString table)
{
    QNetworkRequest req;
    req.setUrl(url);
    
    //QNetworkAccessManager httpGet;
    //QNetworkReply * reply = httpGet.get(req);
    //CSV _csv(reply->get);
    //QString s = _csv.readLine();
    //buff->open(IO_ReadOnly);
    //QTextStream stream(&buff);
    //buff->close();
    //QMessageBox::critical(NULL,tr("CSV TEST"),s);

}


