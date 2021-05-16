#pragma once

#include "interval.hpp"

#include <QObject>
#include <QSettings>

class Settings: public QObject
{
Q_OBJECT

public:
	explicit Settings(QObject *parent);

	auto getIntervals() -> QList<Interval>;
	void setIntervals(const QList<Interval> &intervals);

	auto getPath() -> QString;

private:
	QSettings settings;
};
