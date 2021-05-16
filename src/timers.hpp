#pragma once

#include "interval.hpp"

#include <QObject>
#include <QTimer>
#include <QSystemTrayIcon>

class Timers: QObject
{
Q_OBJECT

public:
	explicit Timers(QObject *parent);

	void load(const QList<Interval> &intervals);

private:
	void reset();
	void add(const Interval &interval);
	static auto timeTo(const QTime &time) -> int;
	auto getInterval(QTimer *timer) -> Interval;
	void notify(const Interval &interval);

	QHash<QTimer*, Interval> timers;
};