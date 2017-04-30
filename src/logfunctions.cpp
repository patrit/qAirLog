#include "logfunctions.h"
#include "logsql.h"

#include <QSet>
#include <QMessageBox>


//
LogFunctions::LogFunctions(LogSql &sql) :
   _fltRules(sql),
   _acFunc(sql),
   _pilFunc(sql),
   _acOps(sql)
{
}
//

LogFunctions::~LogFunctions()
{
}

void LogFunctions::setupData()
{
   _fltRules.setTable("flt_rules", fltRulesTable);
   _fltRules.addEntry(0, tr("Rules"), "", true, "[A-Z]");
   _fltRules.addEntry(1, tr("Description"), "", true);
   _fltRules.addEntry(2, tr("ReqTime"), "", true);
   _fltRules.setupConnections(pushButton_new,
                              pushButton_delete,
                              pushButton_revert,
                              pushButton_submit);
   _fltRules.setupView();


   _acFunc.setTable("ac_func", aircraftFunctionTable);
   _acFunc.addEntry(0, tr("Function"), "", true, "[A-Z]{1,3}");
   _acFunc.addEntry(1, tr("Description"), "", true);
   _acFunc.addEntry(2, tr("Type"), "", true);
   _acFunc.setupConnections(pushButton_new_2,
                            pushButton_delete_2,
                            pushButton_revert_2,
                            pushButton_submit_2);
   _acFunc.setupView();


   _pilFunc.setTable("pil_func", pilotFunctionTable);
   _pilFunc.addEntry(0, tr("Function"), "", true);
   _pilFunc.addEntry(1, tr("Related"), "", true);
   _pilFunc.addEntry(2, tr("Log As"), "", true);
   _pilFunc.setupConnections(pushButton_new_3,
                             pushButton_delete_3,
                             pushButton_revert_3,
                             pushButton_submit_3);
   _pilFunc.setupView();


   _acOps.setTable("ac_ops", aircraftOperationTable);
   _acOps.addEntry(0, tr("Operation"), "", true);
   _acOps.addEntry(1, tr("Description"), "", true);
   _acOps.setupConnections(pushButton_new_4,
                           pushButton_delete_4,
                           pushButton_revert_4,
                           pushButton_submit_4);
   _acOps.setupView();


// CREATE TABLE flt_rules  (
//                         rules           VARCHAR(1) PRIMARY KEY,
//                         description     TEXT,
//                         //checkbox wäri nätt...
//                         req_time        BOOLEAN);
// CREATE TABLE "ac_func" (
//                         func VARCHAR(3)  PRIMARY KEY NOT NULL,
//                         description VARCHAR NOT NULL
//                         type VARCHAR NOT NULL);
// CREATE TABLE "ac_ops" (
//                         operation VARCHAR(7)  PRIMARY KEY NOT NULL,
//                         description TEXT(40)
// CREATE TABLE pil_func   (
//                         function        VARCHAR(10),
//                         //SIM oder FLT
//                         related VARCHAR(3)
//                         //PIC, COPI, DUAL, INSTR, TRAINEE
//                         logAs   VARCHAR(7));

}

