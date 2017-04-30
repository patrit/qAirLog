#ifndef AIRPORTS_H
#define AIRPORTS_H

#include <string>
//
#include "ui_airports.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class Airports : public QObject, public Ui::AirportsWidget
{
   Q_OBJECT

   public:
      Airports(LogSql &sql);
      ~Airports();

      void setupData();

   private:
      TableViewWithValidator _tvb;

};
#endif




