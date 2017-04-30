#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <qt5/QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "logsql.h"
#include "companies.h"
#include "crew.h"
#include "airports.h"
#include "aircrafts.h"
#include "miscellaneous.h"
#include "logfunctions.h"
#include "simentry.h"
#include "flightentry.h"
//
class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindowImpl( QWidget * parent = 0 );

private:
    Ui::MainWindow _mainW;
    LogSql _sql;
    Companies _companies;
    Crew _crew;
    Airports _airports;
    Aircrafts _aircrafts;
    LogFunctions _logFunctions;
    Miscellaneous _misc;
    simentry _simentry;
    flightentry _fltentry;
};
#endif




