#pragma once

#include "settings.hpp"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QUrl>

class TrayIcon: public QSystemTrayIcon
{
Q_OBJECT

public:
	explicit TrayIcon(QObject *parent = nullptr);

private:
	QMenu *menu = nullptr;

	void openSettings(bool checked);
	void reload(bool checked);
};
