#ifndef LOGFUNCTIONS_H
#define LOGFUNCTIONS_H
//
#include "ui_logfunctions.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

#include <QSqlTableModel>
#include <QDataWidgetMapper>

//
class LogFunctions : public QObject, public Ui::LogFunctionsWidget
{
   Q_OBJECT

   public:
      LogFunctions(LogSql &sql);
      ~LogFunctions();

      void setupData();

   private:
      TableViewWithValidator _fltRules;
      TableViewWithValidator _acFunc;
      TableViewWithValidator _pilFunc;
      TableViewWithValidator _acOps;

};
#endif




