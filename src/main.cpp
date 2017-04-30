#include <QtWidgets/QApplication>
#include "mainwindowimpl.h"
//
int main(int argc, char ** argv) {
	Q_INIT_RESOURCE (qAirLog);

	QApplication app(argc, argv);
	MainWindowImpl win;
	win.show();
	win.showMaximized();
	app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
	return app.exec();
}
