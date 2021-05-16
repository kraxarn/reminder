#include "trayicon.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("kraxarn");
	QCoreApplication::setApplicationName("reminder");

	QApplication a(argc, argv);
	TrayIcon i;
	i.show();
	return QApplication::exec();
}
