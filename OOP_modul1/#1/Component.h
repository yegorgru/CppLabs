#pragma once

#include <string>
#include <set>
#include <cstdint>

#include "ComponentType.h"

template<typename ComponentTypeId, typename SubcomponentId>
class Component
{
public:
	Component(ComponentTypeId type, uint32_t cost,bool is_sub);
	ComponentTypeId get_type() const;
	uint32_t get_cost() const;
	std::set<SubcomponentId> get_subcomponents() const;
	void insert_subcomponent(const SubcomponentId& id);
	void erase_subcomponent(const SubcomponentId& id);
	bool is_sub();
private:
	ComponentTypeId type;
	uint32_t cost;
	std::set<SubcomponentId>subcomponents;
	bool sub;
};

template<typename ComponentTypeId, typename SubcomponentId>
Component<ComponentTypeId, SubcomponentId>::Component(ComponentTypeId type, uint32_t cost, bool is_sub):
	type(type),cost(cost),sub(is_sub) {}

template<typename ComponentTypeId, typename SubcomponentId>
ComponentTypeId Component<ComponentTypeId, typename SubcomponentId>::get_type() const
{
	return this->type;
}

template<typename ComponentTypeId, typename SubcomponentId>
inline uint32_t Component<ComponentTypeId, SubcomponentId>::get_cost() const
{
	return this->cost;
}

template<typename ComponentTypeId, typename SubcomponentId>
std::set<SubcomponentId> Component<ComponentTypeId, SubcomponentId>::get_subcomponents() const
{
	return subcomponents;
}

template<typename ComponentTypeId, typename SubcomponentId>
void Component<ComponentTypeId, SubcomponentId>::insert_subcomponent(const SubcomponentId& id)
{
	subcomponents.insert(id);
}

template<typename ComponentTypeId, typename SubcomponentId>
void Component<ComponentTypeId, SubcomponentId>::erase_subcomponent(const SubcomponentId& id)
{
	subcomponents.erase(id);
}

template<typename ComponentTypeId, typename SubcomponentId>
bool Component<ComponentTypeId, SubcomponentId>::is_sub()
{
	return sub;
}
