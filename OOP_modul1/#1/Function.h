#pragma once

#include <cstdint>

class Function
{
public:
	Function(bool all_components, uint32_t number_of_components=0);

	bool is_all_components();
	uint32_t get_number_of_components();
private:
	bool all_components;
	uint32_t number_of_components;
};

