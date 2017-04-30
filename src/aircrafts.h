#ifndef AIRCRAFTS_H
#define AIRCRAFTS_H
//
#include "ui_aircrafts.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class Aircrafts : public QObject, public Ui::AircraftsWidget
{
   Q_OBJECT

   public:
      Aircrafts(LogSql &sql);
      ~Aircrafts();

      void setupData();

   private:
      TableViewWithValidator _tvb;
   private slots:
      void uploadPicture();
};
#endif




