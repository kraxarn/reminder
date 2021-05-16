#include "settings.hpp"

Settings::Settings(QObject *parent)
	: QObject(parent)
{
}

auto Settings::getIntervals() -> QList<Interval>
{
	QList<Interval> intervals;

	auto size = settings.beginReadArray("intervals");
	for (auto i = 0; i < size; i++)
	{
		settings.setArrayIndex(i);
		Interval interval;
		interval.message = settings.value("message").toString();
		interval.minutesBefore = settings.value("minutesBefore").toInt();
		interval.remindTime = QTime::fromString(settings.value("remindTime")
			.toString(), Qt::ISODate);
		intervals << interval;
	}

	settings.endArray();
	return intervals;
}

void Settings::setIntervals(const QList<Interval> &intervals)
{
	settings.beginWriteArray("intervals");
	for (auto i = 0; i < intervals.size(); i++)
	{
		settings.setArrayIndex(i);
		const auto &interval = intervals.at(i);
		settings.setValue("message", interval.message);
		settings.setValue("minutesBefore", interval.minutesBefore);
		settings.setValue("remindTime",
			interval.remindTime.toString(Qt::ISODate));
	}
	settings.endArray();
}

auto Settings::getPath() -> QString
{
	return settings.fileName();
}
