#pragma once

#include "interval.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QSettings>
#include <QStandardPaths>

class Settings
{
public:
	static auto getIntervals() -> QList<Interval>;
	static void setIntervals(const QList<Interval> &intervals);

	static auto getPath() -> QString;

private:
	Settings() = default;

	static auto load() -> QJsonObject;
	static void save(const QJsonObject &json);
};
