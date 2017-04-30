#ifndef FLIGHTENTRY_H
#define FLIGHTENTRY_H

#include <qt5/QtWidgets/QWidget>
#include "ui_flightEntry.h"
#include "logsql.h"
#include "tableViewWithValidator.h"
#include "tableViewBase.h"


class flightentry : public QObject, public Ui::fltLogEntryForm
{
    Q_OBJECT

public:
    flightentry(LogSql &sql);
    ~flightentry();

    void setupData();
    void setupGui();

private:
    TableViewBase _tvb;

private slots:
    void calculateTimes();
};

#endif // FLIGHTENTRY_H
