#ifndef SIMENTRY_H
#define SIMENTRY_H

#include "ui_simentry.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class simentry : public QObject, public Ui::simentryForm
{
   Q_OBJECT

   public:
      simentry(LogSql &sql);
      ~simentry();

      void setupData();

   private:
      TableViewWithValidator _simulators;
      TableViewWithValidator _simlog;
      QTimeEdit t_trainee;
      QTimeEdit t_sfisfe;


private slots:
    void pilotfunc();
};
#endif // SIMENTRY_H
