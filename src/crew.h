#ifndef CREW_H
#define CREW_H
//
#include "ui_crew.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class Crew : public QObject, public Ui::CrewWidget
{
    Q_OBJECT

public:
    Crew(LogSql &sql);
    ~Crew();

    void setupData();

private:
    TableViewWithValidator _tvb;
};
#endif




