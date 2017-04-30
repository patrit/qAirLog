#include "mainwindowimpl.h"
#include "logsql.h"
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QMainWindow>


//
MainWindowImpl::MainWindowImpl( QWidget * parent) :
    QMainWindow(parent),
    _companies(_sql),
    _crew(_sql),
    _airports(_sql),
    _aircrafts(_sql),
    _logFunctions(_sql),
    _misc(_sql),
    _simentry(_sql),
    _fltentry(_sql)
{
    _mainW.setupUi(this);
    _companies.setupUi(_mainW.tabCompanies);
    _crew.setupUi(_mainW.tabCrew);
    _airports.setupUi(_mainW.tabAirports);
    _aircrafts.setupUi(_mainW.tabAircrafts);
    _logFunctions.setupUi(_mainW.tabLogFunctions);
    _misc.setupUi(_mainW.tabMisc);
    _simentry.setupUi(_mainW.tabSimulator);
    _fltentry.setupUi(_mainW.tabFlights);

    _companies.setupData();
    _crew.setupData();
    _airports.setupData();
    _aircrafts.setupData();
    _logFunctions.setupData();
    _misc.setupData();
    _simentry.setupData();
    _fltentry.setupData();
    _fltentry.setupGui();
}
//

