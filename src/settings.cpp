#include "settings.hpp"

Settings::Settings(QObject *parent)
	: QObject(parent)
{
}

auto Settings::getIntervals() -> QList<Interval>
{
	auto json = load();
	auto array = json.contains("Intervals")
		? json["Intervals"].toArray()
		: QJsonArray();

	QList<Interval> intervals;
	for (const auto &item : array)
	{
		const auto &obj = item.toObject();
		Interval interval;
		interval.message = obj["message"].toString();
		interval.minutesBefore = obj["minutes_before"].toInt();
		interval.remindTime = QTime::fromString(obj["remind_time"].toString(),
			Qt::ISODate);
		interval.active = obj["active"].toBool();
		intervals << interval;
	}
	return intervals;
}

void Settings::setIntervals(const QList<Interval> &intervals)
{
	QJsonArray array;
	for (const auto &interval : intervals)
	{
		array << QJsonObject({
			QPair<QString, QString>("message", interval.message),
			QPair<QString, int>("minutes_before", interval.minutesBefore),
			QPair<QString, QString>("remind_time",
				interval.remindTime.toString(Qt::ISODate)),
			QPair<QString, bool>("active", interval.active),
		});
	}

	save({
		QPair<QString, QJsonArray>("Intervals", array),
	});
}

auto Settings::getPath() -> QString
{
	return QString("%1.json")
		.arg(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation));
}

auto Settings::load() -> QJsonObject
{
	QFile file(getPath());
	file.open(QIODevice::ReadOnly);

	auto data = file.readAll();
	if (data.isEmpty())
	{
		qDebug() << "No such file:" << getPath();
		return QJsonObject();
	}

	QJsonParseError error;
	auto json = QJsonDocument::fromJson(data, &error);
	file.close();

	if (error.error != QJsonParseError::NoError)
	{
		qCritical() << "Failed to parse settings:" << error.errorString();
		return QJsonObject();
	}

	return json.object();
}

void Settings::save(const QJsonObject &json)
{
	QDir::root().mkpath(QFileInfo(getPath()).absolutePath());
	QFile file(getPath());
	file.open(QIODevice::WriteOnly);
	file.write(QJsonDocument(json).toJson(QJsonDocument::Indented));
	file.close();
}
