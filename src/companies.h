#ifndef COMPANIES_H
#define COMPANIES_H
//
#include "ui_companies.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class Companies : public QObject, public Ui::CompaniesWidget
{
   Q_OBJECT

   public:
      Companies(LogSql &sql);
      ~Companies();

      void setupData();

   private:
      TableViewBase _tvb;
};
#endif




