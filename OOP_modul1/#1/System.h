#pragma once

#include <map>
#include <set>
#include <cstdint>
#include <unordered_map>
#include <vector>
#include <random>
#include <iostream>
#include <utility>

#include "Component.h"
#include "ComponentType.h"
#include "Function.h"
#include "Defect.h"
#include "DefectType.h"

class System
{
public:
	System(uint32_t money, int defect_chance);
	size_t add_component_type(uint32_t cost);
	void insert_subcomponent_type(size_t component_type, size_t subcomponent_type);
	void insert_function_in_component_type(size_t component_type, size_t function);

	size_t add_component(size_t type, bool sub);
	void insert_subcomponent_in_component(size_t component,size_t subcomponent);
	void erase_subcomponent_from_component(size_t component, size_t subcomponent);

	size_t add_function(bool all_components, uint32_t number_of_components);

	size_t add_defect_type(uint32_t cost, uint64_t time, int chance);

	void simulate(uint64_t time, std::ostream& os, const std::set<size_t>& checked = {}, bool is_steps=true);

	void check_component(size_t component_id, uint64_t time,std::ostream& os);
	void fix_defect(size_t component_id,size_t defect_id, std::ostream& os);
	void replace_component(size_t component_id, std::ostream& os);

	void get_defects(std::ostream& os);
private:
	size_t add_defect(size_t defect_type,size_t component);
	void run_function(size_t function_number, std::ostream& os,const std::set<size_t>& checked);

	std::random_device rd;
	std::mt19937 mersenne;

	uint64_t current_time;
	uint32_t money;
	
	//id компонентів, функцій, типів компонентів, дефектів, типів дефектів виступає їх номер у відповідному векторі
	//у map-ах ці id пов'язані таким чином як вказано в назві map:
	std::vector<ComponentType<size_t, size_t>>component_types;
	std::vector<Component<size_t, size_t>>components;
	std::vector<Function>functions;
	std::map<size_t, std::set<size_t>>functions_component_types;
	std::vector<Defect<size_t>>defects;
	std::vector<DefectType>defect_types;
	std::map<size_t, std::map<size_t,std::set<size_t>>>components_functions_defects;

	int defect_chance;
};

