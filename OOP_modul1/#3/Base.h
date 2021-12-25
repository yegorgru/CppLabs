#pragma once
#include <vector>
#include <memory>
#include <stdexcept>

extern int S;

class Base
{
public:
	Base();
	~Base();
	size_t add_base();
	size_t add_alpha();
	size_t add_beta();
	size_t add_gamma();
	Base& access(size_t pos);

	virtual int predict(int S);

	static size_t counter;
protected:
	size_t N;
	std::vector<std::shared_ptr<Base>>nested_list;
	size_t inheritor_N;
};

class Alpha:public Base
{
public:
	Alpha();
	~Alpha();
	static size_t counter_alpha;
	int predict(int S) override;
};

class Beta :public Base
{
public:
	Beta();
	~Beta();
	static size_t counter_beta;
	int predict(int S) override;
};

class Gamma :public Base
{
public:
	Gamma();
	~Gamma();
	static size_t counter_gamma;
	int predict(int S) override;
};

//Функція яка передабачає S
int S_predictor(std::vector<std::shared_ptr<Base>> objects, int S);
