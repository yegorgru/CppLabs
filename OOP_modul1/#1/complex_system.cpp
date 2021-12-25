#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cstdint>
#include "System.h"

//Функція, яка моделює роботу системи протягом деякого часу time
void modeling(uint64_t time) {
    //наповнення системи. Початкова кількість "грошей" = 1000000, шанс виникнення дефекту = 0.1
    System system(1000000, 10);
    system.add_component_type(10);
    system.add_component_type(5);
    system.add_component_type(20);
    system.add_component(0, 0);
    system.add_component(0, 1);
    system.add_component(1, 0);
    system.add_component(1, 1);
    system.add_component(2, 0);
    system.add_component(2, 1);
    system.insert_subcomponent_type(0, 1);
    system.insert_subcomponent_type(0, 2);
    system.insert_subcomponent_type(1, 0);
    system.insert_subcomponent_type(1, 2);
    system.insert_subcomponent_type(2, 1);
    system.insert_subcomponent_type(2, 0);
    system.insert_subcomponent_in_component(2, 1);
    system.insert_subcomponent_in_component(4, 3);
    system.insert_subcomponent_in_component(0, 5);
    system.add_function(1, 1);
    system.add_function(0, 1);
    system.add_function(1, 2);
    system.insert_function_in_component_type(0, 0);
    system.insert_function_in_component_type(1, 1);
    system.insert_function_in_component_type(2, 2);
    system.add_defect_type(5, 6, 50);
    system.add_defect_type(7, 3, 30);
    system.add_defect_type(10, 10, 40);
    //запам'ятовуємо, які компоненти виконують які функції
    std::map<size_t, std::vector<size_t>> functions_components = { {0,{0,1}},
        {1,{2,3}},
        {2,{4,5}}
    };
    //весь вивід буде тут
    std::ostringstream global_os;
    //цикл моделювання
    for (uint64_t i = 0; i < time; i++) {
        std::ostringstream local_os;
        system.simulate(1, local_os);
        global_os << local_os.str() << std::endl;
        std::istringstream is(local_os.str());
        //окремо розглядаємо вивід у пошуку несправних функцій
        while (!is.eof()) {
            std::string check;
            std::getline(is, check);
            std::istringstream check_stream(check);
            check_stream >> check;
            size_t number;
            check_stream >> number;
            check_stream >> check;
            //якщо знайшли несправну функцію, то намагаємося виправити дефект в ній
            if (check == "failed") {
                for (auto i : functions_components[number]) {
                    std::ostringstream check_os;
                    system.check_component(i, 10, check_os);
                    global_os << check_os.str();
                    std::istringstream check_comp_is(check_os.str());
                    bool end = false;
                    //перевіряємо чи знайдено дефект
                    while (!check_comp_is.eof()) {
                        std::string check;
                        check_comp_is >> check;
                        //якщо дефект знайдено, то намагаємося спочатку виправити його протягом 10с, якщо не виправлено, то замінюємо компонент
                        if (check == "detected!") {
                            check_comp_is >> check;
                            size_t defect;
                            check_comp_is >> defect;
                            std::ostringstream fix_os;
                            //намагаємося виправити дефект
                            system.fix_defect(i, defect, fix_os);
                            global_os << fix_os.str();
                            std::istringstream check_fix_is(fix_os.str());
                            std::string check;
                            while (!check_fix_is.eof()) {
                                check_fix_is >> check;
                                //якщо дефект не був виправлений
                                if (check == "wasn't") {
                                    std::ostringstream replace_os;
                                    system.replace_component(i, replace_os);
                                    global_os << replace_os.str();
                                }
                            }
                            end = true;
                            break;
                        }
                    }
                    if (end) {
                        break;
                    }
                }
            }
        }
    }
    //отримую список дефектів
    system.get_defects(global_os);
    //результат
    std::cout << global_os.str();
}

//майже не відрізняється від минулої функції, лише рахує виявлені дефекти
void modeling_defects(int defects) {
    int count=0;
    System system(1000000, 10);
    system.add_component_type(10);
    system.add_component_type(5);
    system.add_component_type(20);
    system.add_component(0, 0);
    system.add_component(0, 1);
    system.add_component(1, 0);
    system.add_component(1, 1);
    system.add_component(2, 0);
    system.add_component(2, 1);
    system.insert_subcomponent_type(0, 1);
    system.insert_subcomponent_type(0, 2);
    system.insert_subcomponent_type(1, 0);
    system.insert_subcomponent_type(1, 2);
    system.insert_subcomponent_type(2, 1);
    system.insert_subcomponent_type(2, 0);
    system.insert_subcomponent_in_component(2, 1);
    system.insert_subcomponent_in_component(4, 3);
    system.insert_subcomponent_in_component(0, 5);
    system.add_function(1, 1);
    system.add_function(0, 1);
    system.add_function(1, 2);
    system.insert_function_in_component_type(0, 0);
    system.insert_function_in_component_type(1, 1);
    system.insert_function_in_component_type(2, 2);
    system.add_defect_type(5, 6, 50);
    system.add_defect_type(7, 3, 30);
    system.add_defect_type(10, 10, 40);
    std::map<size_t, std::vector<size_t>> functions_components = { {0,{0,1}},
        {1,{2,3}},
        {2,{4,5}}
    };
    std::ostringstream global_os;
    while(true) {
        std::ostringstream local_os;
        system.simulate(1, local_os);
        global_os << local_os.str() << std::endl;
        std::istringstream is(local_os.str());
        while (!is.eof()) {
            std::string check;
            std::getline(is, check);
            std::istringstream check_stream(check);
            check_stream >> check;
            size_t number;
            check_stream >> number;
            check_stream >> check;
            if (check == "failed") {
                for (auto i : functions_components[number]) {
                    std::ostringstream check_os;
                    system.check_component(i, 10, check_os);
                    global_os << check_os.str();
                    std::istringstream check_comp_is(check_os.str());
                    bool end = false;
                    while (!check_comp_is.eof()) {
                        std::string check;
                        check_comp_is >> check;
                        if (check == "detected!") {
                            count++;
                            if (count >= defects) {
                                system.get_defects(global_os);
                                std::cout << global_os.str();
                                return;
                            }
                            check_comp_is >> check;
                            size_t defect;
                            check_comp_is >> defect;
                            std::ostringstream fix_os;
                            system.fix_defect(i, defect, fix_os);
                            global_os << fix_os.str();
                            std::istringstream check_fix_is(fix_os.str());
                            std::string check;
                            while (!check_fix_is.eof()) {
                                check_fix_is >> check;
                                if (check == "wasn't") {
                                    std::ostringstream replace_os;
                                    system.replace_component(i, replace_os);
                                    global_os << replace_os.str();
                                }
                            }
                            end = true;
                            break;
                        }
                    }
                    if (end) {
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    modeling(50);
    modeling_defects(50);
}