#pragma once

#include <boost/fusion/adapted/struct.hpp>
#include <boost/phoenix.hpp>
#include <boost/spirit/include/qi.hpp>

#include "Time.h"

namespace Grammar
{

// Grammar definition
template <typename Iterator>
struct TimeGrammar : boost::spirit::qi::grammar<Iterator, TimeCollector::TimeExpression(), boost::spirit::ascii::space_type>
{
public:
    TimeGrammar() noexcept
        : TimeGrammar::base_type(_expression)
    {

        // Time parser (HH:MM:SS or HH:MM) with proper handling of optional seconds
        _time = (boost::spirit::qi::int_ >> ':' >> boost::spirit::qi::int_ >> -(':' >> boost::spirit::qi::int_)) [
            // Handle optional seconds: if seconds are missing, use 0
            boost::spirit::qi::_val = boost::phoenix::bind([](int h, int m, const boost::optional<int>& s_opt) {
                return TimeCollector::Time(h, m, s_opt ? *s_opt : 0);
            }, boost::spirit::qi::_1, boost::spirit::qi::_2, boost::spirit::qi::_3)
        ];

        // Time interval parser (start - end)
        _parentheses_interval = ('(' >> _time >> '-' >> _time >> ')') [
            boost::spirit::qi::_val = boost::phoenix::construct<TimeCollector::TimeInterval>(boost::spirit::qi::_1, boost::spirit::qi::_2)
        ];

        // Simple interval without parentheses (start - end)
        _simple_interval = (_time >> '-' >> _time) [
            boost::spirit::qi::_val = boost::phoenix::construct<TimeCollector::TimeInterval>(boost::spirit::qi::_1, boost::spirit::qi::_2)
        ];

        // Expression can be a series of intervals with + or just space separated
        _expression = (
            (_parentheses_interval | _simple_interval) % (-boost::spirit::qi::lit('+') | +boost::spirit::qi::space)
        ) [
            boost::spirit::qi::_val = boost::phoenix::construct<TimeCollector::TimeExpression>(boost::spirit::qi::_1)
        ];
    }

private:
    boost::spirit::qi::rule<Iterator, TimeCollector::Time(), boost::spirit::ascii::space_type> _time;
    boost::spirit::qi::rule<Iterator, TimeCollector::TimeInterval(), boost::spirit::ascii::space_type> _parentheses_interval;
    boost::spirit::qi::rule<Iterator, TimeCollector::TimeInterval(), boost::spirit::ascii::space_type> _simple_interval;
    boost::spirit::qi::rule<Iterator, TimeCollector::TimeExpression(), boost::spirit::ascii::space_type> _expression;
};

} // namespace Grammar