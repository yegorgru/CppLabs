#ifndef BOTS_H
#define BOTS_H

#include <ctime>
#include <random>

struct Bot
{
    int gens_of_irritation[8][7];
    std::vector<std::vector<int>>gens_of_action;
    int energy;
    int counter;
    int posX;
    int posY;
    int number_of_gens_of_action;
    int min_energy_for_division;
    int condition_for_attack;
    int view;
    int color;
    bool alive;
    int chance_of_mutation;
    int irritation;
    int age;

    int superpower;

    Bot(){};
    Bot(int energy,int number_of_gens_of_action,int min_energy_for_division);
    Bot(const Bot& another);

    friend bool operator== (const Bot &first, const Bot &second);
};


#endif // BOTS_H
