#include <cinttypes>

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Grammar.h"
#include "Time.h"

TimeCollector::Time calculate_total_time(const TimeCollector::TimeExpression& expr)
{
    TimeCollector::Time total;
    for (const auto& interval : expr.getIntervals()) {
        const auto& [time_interval_start, time_interval_end] = interval.getTimeIntervalPair();
        total = total + (time_interval_end - time_interval_start);
    }
    return total;
}

double promptRatio(const std::string& prompt, double default_value)
{
    std::string line;
    while (true) {
        std::cout << prompt << " (default: " << default_value << "): ";
        std::getline(std::cin, line);

        // 1. User pressed only Enter (use the default)
        if (line.empty())
            return default_value;

        // 2. Try to parse what they typed
        char* end {};
        errno = 0;
        double result = std::strtod(line.c_str(), &end);

        // end must point to the string-terminator
        // no range error (ERANGE)
        // at least one digit was parsed
        if (end != line.c_str() && *end == '\0' && errno != ERANGE)
            return result;
    }
}

auto main() -> int
{
    std::cout << "Time Calculator" << std::endl;
    std::cout << "Enter time expressions like:" << std::endl;
    std::cout << "(00:30 - 06:30) + (08:30 - 12:45) + (13:30 - 17:15)" << std::endl;
    std::cout << "or" << std::endl;
    std::cout << "00:30 - 06:30 08:30 - 12:45 13:30 - 17:15\n"
              << std::endl;

    Grammar::TimeGrammar<std::string::const_iterator> grammar;

    std::string input;
    while (true) {
        std::cout << "\nYour Expression : ";

        if (!std::getline(std::cin, input))
            break;

        TimeCollector::TimeExpression expr;
        std::string::const_iterator iter = input.begin();
        std::string::const_iterator end = input.end();

        bool success = boost::spirit::qi::phrase_parse(iter, end, grammar, boost::spirit::ascii::space, expr);

        if (success && iter == end) {
            // Calculating total time
            TimeCollector::Time total = calculate_total_time(expr);

            // Calculating remote time
            double default_remote_ratio = 8.75 / 6.00;
            double input_remote_ratio = promptRatio("Enter remote time ratio", default_remote_ratio);
            TimeCollector::Time remote_work = total * input_remote_ratio;

            // Show total time
            std::cout << "Total time: " << total << std::endl;

            // Show remote time
            std::cout << "Remote Work Time (ratio: " << input_remote_ratio << "): " << remote_work << std::endl;

            // Show individual intervals
            std::cout << "Intervals:" << std::endl;
            for (const auto& interval : expr.getIntervals()) {
                const auto& [time_interval_start, time_interval_end] = interval.getTimeIntervalPair();
                TimeCollector::Time duration = time_interval_end - time_interval_start;
                std::cout << "  " << time_interval_start << " - " << time_interval_end
                          << " = " << duration << std::endl;
            }

            std::cout << std::endl;
        } else {
            std::cout << "Invalid input. Could not parse at: "
                      << std::string(iter, end) << '\n'
                      << std::endl;
        }
    }

    return 0;
}
