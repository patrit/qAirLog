#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H
//
#include "ui_miscellaneous.h"
#include "logsql.h"
#include "tableViewWithValidator.h"

//
class Miscellaneous : public QObject, public Ui::MiscellaneousWidget
{
    Q_OBJECT

public:
    Miscellaneous(LogSql &sql);
    ~Miscellaneous();

    void setupData();

private:
    TableViewWithValidator _countries;
    TableViewWithValidator _logBook;
private slots:
    void test();

};
#endif




