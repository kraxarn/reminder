#include "trayicon.hpp"

TrayIcon::TrayIcon(QObject *parent)
	: QSystemTrayIcon(parent)
{
	setIcon(QIcon::fromTheme("notifications"));

	menu = new QMenu();

	auto *settings = menu->addAction(QIcon::fromTheme("configure"), "Settings");
	QAction::connect(settings, &QAction::triggered, this, &TrayIcon::openSettings);

	auto *quit = menu->addAction(QIcon::fromTheme("application-exit"), "Quit");
	QAction::connect(quit, &QAction::triggered, &QCoreApplication::quit);

	setContextMenu(menu);
}

void TrayIcon::openSettings(bool /*checked*/)
{
	if (Settings::getIntervals().empty())
	{
		Interval interval;
		interval.remindTime = QTime::currentTime();
		interval.message = "Example interval";

		// Example interval
		Settings::setIntervals({
			interval,
		});
	}

	QDesktopServices::openUrl(QUrl(Settings::getPath()));
}
