#ifdef ENABLE_TEST

#include <gtest/gtest.h>

#include "src/Time.h"

// Demonstrate some basic assertions.
TEST(TimeTest, time_from_second_should_be_inverse_of_to_second)
{
    // Expect equality.
    EXPECT_EQ(TimeCollector::Time::from_seconds(12345678).to_seconds(),
        12345678u);
}

#endif
