#include "Function.h"


Function::Function(bool all_components, uint32_t number_of_components):
	all_components(all_components), number_of_components(number_of_components){}

bool Function::is_all_components()
{
	return this->all_components;
}

uint32_t Function::get_number_of_components()
{
	return this->number_of_components;
}
