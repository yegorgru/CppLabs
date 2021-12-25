#include <iostream>
#include <memory>
#include "Base.h"
#include "Tests.h"


int S = 0;

size_t Base::counter = 0;
size_t Alpha::counter_alpha = 0;
size_t Beta::counter_beta = 0;
size_t Gamma::counter_gamma = 0;

int main()
{
	TestRunner tr;
	RUN_TEST(tr, Test_predictor);
}