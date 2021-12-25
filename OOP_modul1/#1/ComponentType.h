#pragma once

#include <set>
#include <string>

template<typename ComponentTypeId, typename FunctionId>
class ComponentType
{
public:
	ComponentType(uint32_t cost);
	std::set<ComponentTypeId> get_subcomponent_types();
	std::set<FunctionId> get_functions();

	uint32_t get_cost();

	void insert_subcomponent_type(const ComponentTypeId& component_type);
	void insert_function(const FunctionId& function);
private:
	std::set<ComponentTypeId>subcomponent_types;
	std::set<FunctionId>functions;

	uint32_t cost;
};

template<typename ComponentTypeId, typename FunctionId>
ComponentType<ComponentTypeId, FunctionId>::ComponentType(uint32_t cost) :cost(cost) {}

template<typename ComponentTypeId, typename FunctionId>
std::set<ComponentTypeId> ComponentType<ComponentTypeId, FunctionId>::get_subcomponent_types()
{
	return this->subcomponent_types;
}

template<typename ComponentTypeId, typename FunctionId>
inline std::set<FunctionId> ComponentType<ComponentTypeId, FunctionId>::get_functions()
{
	return this->functions;
}

template<typename ComponentTypeId, typename FunctionId>
uint32_t ComponentType<ComponentTypeId, FunctionId>::get_cost()
{
	return this->cost;
}

template<typename ComponentTypeId, typename FunctionId>
void ComponentType<ComponentTypeId, FunctionId>::insert_subcomponent_type(const ComponentTypeId& component_type)
{
	this->subcomponent_types.insert(component_type);
}

template<typename ComponentTypeId, typename FunctionId>
void ComponentType<ComponentTypeId, FunctionId>::insert_function(const FunctionId& function)
{
	this->functions.insert(function);
}