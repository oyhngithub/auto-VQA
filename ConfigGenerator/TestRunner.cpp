#include "TestRunner.h"
#include <cstdlib>


TestRunner::TestRunner()
{
}

TestRunner::TestRunner(std::string bashName) {
	system(bashName.c_str());
}

TestRunner::~TestRunner()
{
}
