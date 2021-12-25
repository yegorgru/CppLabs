#include "Base.h"

Base::Base()
{
	this->N = ++counter;
	this->inheritor_N = 0;
}

Base::~Base()
{
	S = 3 * S - N + 35;
}

size_t Base::add_base()
{
	this->nested_list.push_back(std::make_shared<Base>());
	return this->nested_list.size();
}

size_t Base::add_alpha()
{
	this->nested_list.push_back(std::make_shared<Alpha>());
	return this->nested_list.size();
}

size_t Base::add_beta()
{
	this->nested_list.push_back(std::make_shared<Beta>());
	return this->nested_list.size();
}

size_t Base::add_gamma()
{
	this->nested_list.push_back(std::make_shared<Gamma>());
	return this->nested_list.size();
}

Base& Base::access(size_t pos)
{
	if (pos < this->nested_list.size()) {
		return *nested_list[pos];
	}
	else {
		throw std::invalid_argument("Incorrect pos");
	}
}

int Base::predict(int S)
{
	int  newS = 3 * S - N + 35;
	newS = S_predictor(this->nested_list, newS);
	return newS;
}

Alpha::Alpha()
{
	this->inheritor_N = ++counter_alpha;
}

Alpha::~Alpha()
{
	S = S - inheritor_N + 35;
}

int Alpha::predict(int S)
{
	int newS = S - inheritor_N + 35;
	newS = 3 * newS - N + 35;
	newS = S_predictor(this->nested_list, newS);
	return newS;
}

Beta::Beta()
{
	this->inheritor_N = ++counter_beta;
}

Beta::~Beta()
{
	S += inheritor_N;
}

int Beta::predict(int S)
{
	int newS = S + inheritor_N;
	newS = 3 * newS - N + 35;
	newS = S_predictor(this->nested_list, newS);
	return newS;
}

Gamma::Gamma()
{
	this->inheritor_N = ++counter_gamma;
}

Gamma::~Gamma()
{
	S = S + 2 * inheritor_N - 17;
}

int Gamma::predict(int S)
{
	int newS = S + 2*inheritor_N - 17;
	newS = 3 * newS - N + 35;
	newS = S_predictor(this->nested_list, newS);
	return newS;
}

int S_predictor(std::vector<std::shared_ptr<Base>> objects, int S)
{
	for (const auto& obj : objects) {
		S = obj->predict(S);
	}
	return S;
}
