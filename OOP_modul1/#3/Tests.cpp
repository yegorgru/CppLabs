#include "Tests.h"

//намагаюсь зробити різні комбінації елементів і порівнюю передбачене значення S з реальним
void Test_predictor()
{
	int check = 0;
	{	
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Base>());
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Alpha>());
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Beta>());
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Gamma>());
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Base>());
		v.push_back(make_shared<Alpha>());
		v.push_back(make_shared<Beta>());
		v.push_back(make_shared<Gamma>());
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Base>());
		v[0]->add_base();
		v[0]->add_alpha();
		v[0]->add_beta();
		v[0]->add_gamma();
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Alpha>());
		v[0]->add_base();
		v[0]->add_alpha();
		v[0]->add_beta();
		v[0]->add_gamma();
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Beta>());
		v[0]->add_base();
		v[0]->add_alpha();
		v[0]->add_beta();
		v[0]->add_gamma();
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Gamma>());
		v[0]->add_base();
		v[0]->add_alpha();
		v[0]->add_beta();
		v[0]->add_gamma();
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	S = 0;
	check = 0;
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Gamma>());
		v[0]->add_base();
		v[0]->add_alpha();
		v[0]->add_beta();
		v[0]->add_gamma();
		v[0]->access(0).add_gamma();
		v[0]->access(1).add_beta();
		v[0]->access(2).add_alpha();
		v[0]->access(3).add_base();
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Gamma>());
		v.push_back(make_shared<Alpha>());
		v.push_back(make_shared<Base>());
		v.push_back(make_shared<Beta>());
		v[0]->add_base();
		v[1]->add_alpha();
		v[2]->add_beta();
		v[3]->add_gamma();
		v[1]->add_base();
		v[2]->add_alpha();
		v[3]->add_beta();
		v[0]->add_gamma();
		v[2]->add_base();
		v[3]->add_alpha();
		v[0]->add_beta();
		v[1]->add_gamma();
		v[3]->add_base();
		v[0]->add_alpha();
		v[1]->add_beta();
		v[2]->add_gamma();

		v[1]->access(0).add_gamma();
		v[2]->access(1).add_beta();
		v[3]->access(2).add_alpha();
		v[0]->access(3).add_base();

		v[2]->access(0).add_gamma();
		v[3]->access(1).add_beta();
		v[0]->access(2).add_alpha();
		v[1]->access(3).add_base();

		v[3]->access(0).add_gamma();
		v[0]->access(1).add_beta();
		v[1]->access(2).add_alpha();
		v[2]->access(3).add_base();

		v[0]->access(0).add_gamma();
		v[1]->access(1).add_beta();
		v[2]->access(2).add_alpha();
		v[3]->access(3).add_base();
		
		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
	{
		std::vector<std::shared_ptr<Base>>v;
		v.push_back(make_shared<Gamma>());
		v.push_back(make_shared<Alpha>());
		v.push_back(make_shared<Base>());
		v.push_back(make_shared<Beta>());
		v[0]->add_base();
		v[1]->add_alpha();
		v[2]->add_beta();
		v[3]->add_gamma();
		v[1]->add_base();
		v[2]->add_alpha();
		v[3]->add_beta();
		v[0]->add_gamma();
		v[2]->add_base();
		v[3]->add_alpha();
		v[0]->add_beta();
		v[1]->add_gamma();
		v[3]->add_base();
		v[0]->add_alpha();
		v[1]->add_beta();
		v[2]->add_gamma();

		v[1]->access(0).add_gamma();
		v[2]->access(1).add_beta();
		v[3]->access(2).add_alpha();
		v[0]->access(3).add_base();

		v[2]->access(0).add_gamma();
		v[3]->access(1).add_beta();
		v[0]->access(2).add_alpha();
		v[1]->access(3).add_base();

		v[3]->access(0).add_gamma();
		v[0]->access(1).add_beta();
		v[1]->access(2).add_alpha();
		v[2]->access(3).add_base();

		v[0]->access(0).add_gamma();
		v[1]->access(1).add_beta();
		v[2]->access(2).add_alpha();
		v[3]->access(3).add_base();

		v[1]->access(3).add_gamma();
		v[2]->access(2).add_beta();
		v[3]->access(1).add_alpha();
		v[0]->access(0).add_base();

		v[2]->access(3).add_gamma();
		v[3]->access(2).add_beta();
		v[0]->access(1).add_alpha();
		v[1]->access(0).add_base();

		v[3]->access(3).add_gamma();
		v[0]->access(2).add_beta();
		v[1]->access(1).add_alpha();
		v[2]->access(0).add_base();

		v[0]->access(3).add_gamma();
		v[1]->access(2).add_beta();
		v[2]->access(1).add_alpha();
		v[3]->access(0).add_base();

		v[1]->access(3).access(0).add_gamma();
		v[0]->access(3).access(0).add_base();
		v[1]->access(1).access(0).add_beta();
		v[2]->access(2).access(0).add_alpha();
		v[3]->access(3).access(1).add_base();
		v[1]->access(2).access(1).add_base();
		v[2]->access(1).access(1).add_beta();
		v[3]->access(3).access(1).add_gamma();

		check = S_predictor(v, S);
	}
	ASSERT_EQUAL(check, S);
}
