#include <gtest/gtest.h>

auto main(int argc, char **argv) -> int
{
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
