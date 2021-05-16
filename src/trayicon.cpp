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
	Settings settings(this);

	if (settings.getIntervals().empty())
	{
		// Example interval
		settings.setIntervals({
			Interval{
				QTime::currentTime(),
				0,
				"Example interval",
			}
		});
	}

	QDesktopServices::openUrl(QUrl(settings.getPath()));
}
