#include "Time.h"

#include <cinttypes>

#include <iostream>
#include <vector>

namespace TimeCollector {

Time::Time() noexcept
    : _hours(0)
    , _minutes(0)
    , _seconds(0)
{
}

Time::Time(std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept
    : _hours(hours)
    , _minutes(minutes)
    , _seconds(seconds)
{
}

std::uint32_t Time::to_seconds(bool is_end) const noexcept
{
    std::int32_t hours { _hours };
    if (is_end)
        hours = (_hours == 0 ? 24 : _hours);
    return hours * 3600 + _minutes * 60 + _seconds;
}

// Create from total seconds
Time Time::from_seconds(std::uint32_t total_seconds) noexcept
{
    std::int32_t hours = total_seconds / 3600;
    std::int32_t remaining = total_seconds % 3600;
    std::int32_t minutes = remaining / 60;
    std::int32_t seconds = remaining % 60;

    return Time(hours, minutes, seconds);
}

// Overload operators for time calculations
Time Time::operator-(const Time& other) const noexcept
{
    return Time::from_seconds(this->to_seconds(true) - other.to_seconds());
}

Time Time::operator+(const Time& other) const noexcept
{
    return Time::from_seconds(this->to_seconds() + other.to_seconds());
}

Time Time::operator*(double ratio) const noexcept
{
    return Time::from_seconds(this->to_seconds() * ratio);
}

TimeInterval::TimeInterval(const Time& start, const Time& end) noexcept
    : _start { start }
    , _end { end }
{
}

void TimeInterval::setTimeIntervalPair(std::pair<Time, Time> time_interval_pair) noexcept
{
    _start = std::move(time_interval_pair.first);
    _end = std::move(time_interval_pair.second);
}

std::pair<Time, Time> TimeInterval::getTimeIntervalPair() const noexcept
{
    return { _start, _end };
}

TimeExpression::TimeExpression(std::vector<TimeInterval> intervals) noexcept
    : _intervals(std::move(intervals))
{
}

void TimeExpression::setIntervals(std::vector<TimeInterval> intervals)
{
    _intervals = std::move(intervals);
}

const std::vector<TimeInterval> TimeExpression::getIntervals() const noexcept
{
    return _intervals;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    os << std::setw(2) << std::setfill('0') << time._hours << ":"
       << std::setw(2) << std::setfill('0') << time._minutes << ":"
       << std::setw(2) << std::setfill('0') << time._seconds;
    return os;
}

} // namespace TimeCollector