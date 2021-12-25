#include "DefectType.h"

DefectType::DefectType(uint32_t cost, uint64_t time, int chance)
{
	this->cost = cost;
	this->time = time;
	this->chance = chance;
}

uint32_t DefectType::get_cost()
{
	return cost;
}

uint64_t DefectType::get_time()
{
	return time;
}

int DefectType::get_chance_be_detected()
{
	return chance;
}
