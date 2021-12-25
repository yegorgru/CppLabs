#include "System.h"

System::System(uint32_t money, int defect_chance) :
	mersenne(rd()),current_time(0),money(money),defect_chance(defect_chance) {}

size_t System::add_component_type(uint32_t cost)
{
	component_types.push_back(ComponentType<size_t, size_t>(cost));
	return component_types.size() - 1;
}

void System::insert_subcomponent_type(size_t component_type, size_t subcomponent_type)
{
	if (component_type!=subcomponent_type && component_type < component_types.size() && subcomponent_type < component_types.size()) {
		component_types[component_type].insert_subcomponent_type(subcomponent_type);
	}
	else {
		throw std::invalid_argument("incorrect");
	}
}

void System::insert_function_in_component_type(size_t component_type, size_t function)
{
	if (component_type < component_types.size() && function < functions.size()) {
		component_types[component_type].insert_function(function);
		functions_component_types[function].insert(component_type);
	}
	else {
		throw std::invalid_argument("incorrect");
	}
}

size_t System::add_component(size_t type, bool sub)
{
	if (type < component_types.size()) {
		components.push_back(Component<size_t, size_t>(type, component_types[type].get_cost(), sub));
		return components.size() - 1;
	}
	else {
		throw std::invalid_argument("incorrect");
	}
}

void System::insert_subcomponent_in_component(size_t component, size_t subcomponent)
{
	if (component != subcomponent && component < components.size() && subcomponent < components.size()
		&& !components[component].is_sub() && components[subcomponent].is_sub() && 
		component_types[components[component].get_type()].get_subcomponent_types().count(components[subcomponent].get_type())==1) {
		components[component].insert_subcomponent(subcomponent);
	}
	else {
		throw std::invalid_argument("incorrect");
	}
}

void System::erase_subcomponent_from_component(size_t component, size_t subcomponent)
{
	if (component != subcomponent && component < components.size() && subcomponent < components.size()) {
		components[component].erase_subcomponent(subcomponent);
	}
	else {
		throw std::invalid_argument("incorrect");
	}
}

size_t System::add_function(bool all_components, uint32_t number_of_components)
{
	functions.push_back(Function(all_components,number_of_components));
	return functions.size() - 1;
}

size_t System::add_defect_type(uint32_t cost, uint64_t time, int chance)
{
	defect_types.push_back(DefectType(cost, time, chance));
	return defect_types.size() - 1;
}

void System::simulate(uint64_t time, std::ostream& os, const std::set<size_t>& checked, bool is_steps)
{
	//протягом вказаного часу моделюю всі функції. Під час цього можуть виникати дефекти
	for (uint64_t sec = 0; sec < time; sec++) {
		if (is_steps) {
			os << "Time: " << current_time << std::endl;
		}
		if (mersenne() % 100 < this->defect_chance && defect_types.size()>0) {
			add_defect(mersenne() % defect_types.size(), mersenne() % components.size());
		}
		for (size_t f = 0; f < functions.size(); f++) {
			run_function(f,os,checked);
		}
		current_time++;
	}
}

void System::check_component(size_t component_id, uint64_t time, std::ostream& os)
{
	//перевіряю компонент component_id протягом часу time
	//дефекти в компоненті
	std::set<size_t>defects_in_component;
	for (const auto& i : components_functions_defects[component_id]) {
		defects_in_component.insert(i.second.begin(), i.second.end());
	}
	//всі компоненти які не працюють
	std::set<size_t>stopped = components[component_id].get_subcomponents();
	stopped.insert(component_id);
	for (uint64_t sec = 0; sec < time; sec++) {
		os << "Time: " << current_time << std::endl;
		//функції працююь, час йде
		simulate(1, os, stopped,false);
		for (auto defect : defects_in_component) {
			//може бути виявлено дефект
			if (mersenne() % 100 < defect_types[defects[defect].get_defect_type()].get_chance_be_detected()) {
				os << "Defect detected! Id: " << defect<<std::endl;
			}
		}
	}
}

void System::fix_defect(size_t component_id, size_t defect_id, std::ostream& os)
{
	if (component_id < components.size() && defect_id < defects.size() && defects[defect_id].is_detected()) {
		//вартість починки
		uint32_t sum = components[component_id].get_cost()/2 + defect_types[defects[defect_id].get_defect_type()].get_cost();
		if (this->money > sum) {
			//виправити дефект можливо
			//непрацюючі компоненти
			std::set<size_t>stopped = components[component_id].get_subcomponents();
			stopped.insert(component_id);
			//функціїї працюють, час йде
			simulate(defect_types[defects[defect_id].get_defect_type()].get_time(), os, stopped);
			//виправлення дефекту
			this->money -= sum;
			defects[defect_id].fix(current_time);
			for (auto& i : components_functions_defects[component_id]) {
				i.second.erase(defect_id);
			}
			os << "Defect " << defect_id << " in component " << component_id << " was fixed. System spent "<<sum<<"coins. System has "<<money<<" coins."<<std::endl;
		}
		else {
			//виправити дефект неможливо
			os << "Defect " << defect_id << " in component " << component_id << " wasn't fixed. System has only " << money << " coins. Required: "<<sum<<"." << std::endl;
		}
	}
}

void System::replace_component(size_t component_id, std::ostream& os)
{
	if (component_id < components.size()) {
		//заміна компоненту
		uint32_t sum = components[component_id].get_cost();
		if (this->money > sum) {
			//замінити можна
			std::set<size_t>stopped = components[component_id].get_subcomponents();
			stopped.insert(component_id);
			//проходить 1 одиниця часу
			simulate(1, os, stopped);
			this->money -= sum;
			std::set<size_t>defects_in_component;
			for (const auto& i : components_functions_defects[component_id]) {
				defects_in_component.insert(i.second.begin(), i.second.end());
			}
			for (size_t def : defects_in_component) {
				defects[def].fix(current_time);
			}
			components_functions_defects[component_id].clear();
			os << "Component " << component_id << " was replaced with new one. System spent " << sum << "coins. System has " << money << " coins." << std::endl;
		}
		else {
			//замінити не можна
			os << "Component " << component_id << " wasn't replaced with new one. System has only " << money << " coins. Required: " << sum << "." << std::endl;
		}
	}
}

void System::get_defects(std::ostream& os)
{
	std::vector<Defect<size_t>>result;
	//переношу в результат лише виявлені дефекти
	for (auto& i : defects) {
		if (i.is_detected()) {
			result.push_back(i);
		}
	}
	//сортую їх за вказаним правилом
	std::sort(result.begin(), result.end(), [](const Defect<size_t>& lhs, const Defect<size_t>& rhs) {
		if (!lhs.is_fixed() && rhs.is_fixed()) {
			return true;
		}
		else if (lhs.is_fixed() && !rhs.is_fixed()) {
			return false;
		}
		else if (lhs.is_fixed() && rhs.is_fixed()) {
			return lhs.get_duration() > rhs.get_duration();
		}
		return false;
		});
	size_t pos = 0;
	//вивожу у потік виводу
	for (auto& def : result) {
		pos++;
		os << "Defect: " << pos;
		if (def.is_fixed()) {
			os << ". Fixed. Time: " << def.get_duration() << std::endl;
		}
		else {
			os << ". Not fixed."<<std::endl;
		}
	}
}

size_t System::add_defect(size_t defect_type, size_t component)
{
	if (component < components.size() && defect_type < defect_types.size()) {
		defects.push_back(Defect<size_t>(defect_type, current_time));
		for (auto function : component_types[components[component].get_type()].get_functions()) {
			if (mersenne() % 2) {
				components_functions_defects[component][function].insert(defects.size() - 1);
			}
		}
		return defects.size() - 1;
	}
}

void System::run_function(size_t function_number, std::ostream& os, const std::set<size_t>& checked)
{
	bool all = functions[function_number].is_all_components();
	bool fail=false;
	uint32_t required = functions[function_number].get_number_of_components();
	//кіькість успішно відпрацювавших компонентів
	uint32_t successful = 0;
	for (size_t comp_id = 0; comp_id < components.size();comp_id++) {
		bool must_run = functions_component_types[function_number].count(components[comp_id].get_type());
		if (must_run && (components_functions_defects.size() == 0 || components_functions_defects[comp_id].size() == 0 || components_functions_defects[comp_id][function_number].size() == 0)
			&& (checked.size() ==0 ||checked.count(comp_id) == 0) ) {
			successful++;
		}
		else if(must_run){
			if (all) {
				fail = true;
				break;
			}
		}
	}
	if(fail && all || !all && successful<required){
		os << "Function " << function_number << " failed" << std::endl;
	}
	else {
		money++;
		os << "Function " << function_number << " was correct" << std::endl;
	}
}
