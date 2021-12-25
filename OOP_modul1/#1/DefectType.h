#pragma once

#include <cstdint>

class DefectType
{
public:
	DefectType(uint32_t cost, uint64_t time, int chance);
	
	uint32_t get_cost();
	uint64_t get_time();
	int get_chance_be_detected();
private:
	uint32_t cost;
	uint64_t time; 
	int chance;
};

