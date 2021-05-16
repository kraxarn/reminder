#pragma once

#include "interval.hpp"

#include <QObject>
#include <QSettings>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QDir>
#include <QJsonObject>

class Settings: public QObject
{
Q_OBJECT

public:
	static auto getIntervals() -> QList<Interval>;
	static void setIntervals(const QList<Interval> &intervals);

	static auto getPath() -> QString;

private:
	explicit Settings(QObject *parent);

	static auto load() -> QJsonObject;
	static void save(const QJsonObject &json);
};
