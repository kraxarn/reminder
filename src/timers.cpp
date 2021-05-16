#include "timers.hpp"

Timers::Timers(QObject *parent)
	: QObject(parent)
{
}

void Timers::load(const QList<Interval> &intervals)
{
	reset();
	for (const auto &interval : intervals)
	{
		add(const_cast<Interval &>(interval));
	}
}

void Timers::reset()
{
	QHashIterator<QTimer *, Interval> iter(timers);
	while (iter.hasNext())
	{
		iter.next();
		iter.key()->stop();
		iter.key()->deleteLater();
	}
	timers.clear();
}

void Timers::add(const Interval &interval)
{
	auto timer = new QTimer(this);
	timer->setSingleShot(true);
	timer->setInterval(timeTo(interval.remindTime));

	QTimer::connect(timer, &QTimer::timeout, [this, timer]()
	{
		auto i = this->getInterval(timer);
		if (!i.active)
		{
			timer->stop();
			return;
		}
		this->notify(i);
		timer->setInterval(Timers::timeTo(i.remindTime));
	});

	timers.insert(timer, interval);
	timer->start();
}

auto Timers::timeTo(const QTime &time) -> int
{
	auto current = QTime::currentTime();
	auto diff = current.msecsTo(time);

	// Today
	if (diff > 0)
	{
		return diff;
	}

	// Tomorrow
	// current > 00:00 > time
	constexpr int msInDay = 1000 * 60 * 60 * 24;
	return (msInDay - current.msecsSinceStartOfDay()) + time.msecsSinceStartOfDay();
}

auto Timers::getInterval(QTimer *timer) -> Interval
{
	return timers.contains(timer)
		? timers[timer]
		: Interval();
}

void Timers::notify(const Interval &interval)
{
	auto *trayIcon = dynamic_cast<QSystemTrayIcon *>(parent());
	if (trayIcon == nullptr)
	{
		return;
	}
	trayIcon->showMessage("reminder", QString("It's \"%1\"!")
		.arg(interval.message));
}
