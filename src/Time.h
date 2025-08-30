#pragma once

#include <cinttypes>

#include <iomanip>
#include <iostream>
#include <vector>

namespace TimeCollector {

class Time final {
    friend std::ostream& operator<<(std::ostream&, const Time&);

public:
    Time() noexcept;

    Time(std::int32_t hours, std::int32_t minutes, std::int32_t seconds) noexcept;

    std::uint32_t to_seconds(bool is_end = false) const noexcept;

    // Create from total seconds
    static Time from_seconds(std::uint32_t total_seconds) noexcept;

    // Overload operators for time calculations
    Time operator-(const Time& other) const noexcept;

    Time operator+(const Time& other) const noexcept;

    Time operator*(double ratio) const noexcept;

private:
    std::int32_t _hours;
    std::int32_t _minutes;
    std::int32_t _seconds;
};

// AST node types
class TimeInterval final {
public:
    TimeInterval() = default;

    TimeInterval(const Time& start, const Time& end) noexcept;

    void setTimeIntervalPair(std::pair<Time, Time> time_interval_pair) noexcept;

    std::pair<Time, Time> getTimeIntervalPair() const noexcept;

private:
    Time _start;
    Time _end;
};

struct TimeExpression final {
    TimeExpression() noexcept = default;

    explicit TimeExpression(std::vector<TimeInterval> intervals) noexcept;

    void setIntervals(std::vector<TimeInterval> intervals);

    const std::vector<TimeInterval> getIntervals() const noexcept;

private:
    std::vector<TimeInterval> _intervals;
};

std::ostream& operator<<(std::ostream& os, const Time& time);

} // namespace TimeCollector