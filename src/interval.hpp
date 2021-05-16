#pragma once

#include <QTime>

struct Interval
{
	Interval() = default;

	/**
	 * At what time to remind
	 */
	QTime remindTime;

	/**
	 * How many minutes before to remind
	 */
	int minutesBefore = 0;

	/**
	 * Message to show in notification
	 */
	QString message;
};
