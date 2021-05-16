#include "trayicon.hpp"
#include "icon.xpm"

TrayIcon::TrayIcon(QObject *parent)
	: timers(this),
	QSystemTrayIcon(parent)
{
	setIcon(QIcon(QPixmap(icon_xpm)));

	menu = new QMenu();

	auto *settings = menu->addAction(QIcon::fromTheme("configure"), "Settings");
	QAction::connect(settings, &QAction::triggered, this, &TrayIcon::openSettings);

	auto *reload = menu->addAction(QIcon::fromTheme("reload"), "Reload");
	QAction::connect(reload, &QAction::triggered, this, &TrayIcon::reload);

	auto *quit = menu->addAction(QIcon::fromTheme("application-exit"), "Quit");
	QAction::connect(quit, &QAction::triggered, &QCoreApplication::quit);

	setContextMenu(menu);

	timers.load(Settings::getIntervals());
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

void TrayIcon::reload(bool /*checked*/)
{
	auto intervals = Settings::getIntervals();
	auto actives = 0;
	for (const auto &interval : intervals)
	{
		if (interval.active)
		{
			actives++;
		}
	}

	timers.load(intervals);

	showMessage("reminder", QString("Loaded %1 %2 (%3 active)")
		.arg(intervals.size())
		.arg(intervals.size() == 1 ? "interval" : "intervals")
		.arg(actives));
}