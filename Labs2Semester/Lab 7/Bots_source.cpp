#include "Bots.h"

extern std::mt19937 mersenne;

Bot::Bot(int energy,int number_of_gens_of_action,int min_energy_for_division){
    this->energy=energy;
    this->number_of_gens_of_action=number_of_gens_of_action;
    this->min_energy_for_division=min_energy_for_division;
    posX = -1;
    posY = -1;
    counter = 0;
    view = mersenne()%8;
    alive = true;
    condition_for_attack=mersenne()%(energy+1);
    chance_of_mutation=10;
    irritation=10;
    color=1+mersenne()%6;
    superpower=color;
    this->age=0;

    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            gens_of_irritation[i][j]=mersenne() % 10;
        }
    }
    for(int i=0;i<8;i++){
        gens_of_irritation[i][6]=mersenne() % 9;
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        std::vector<int>to_add;
        gens_of_action.push_back(to_add);
        for (int j = 0; j < 6; j++) {
            gens_of_action[i].push_back(mersenne() % 10);
        }
    }
    for(int i=0;i<number_of_gens_of_action;i++){
        gens_of_action[i].push_back(mersenne() % 9);
    }
}

Bot::Bot(const Bot& another){
    for(int i=0;i<8;i++){
        for(int j=0;j<7;j++){
            this->gens_of_irritation[i][j]=another.gens_of_irritation[i][j];
        }
    }
    this->gens_of_action=another.gens_of_action;

    this->age=0;
    this->energy=another.energy;

    //changeless
    this->counter=0;
    this->posX=another.posX;
    this->posY=another.posY;
    this->view=another.view;
    this->alive=true;
    this->irritation=10;


    //changeable
    this->number_of_gens_of_action=another.number_of_gens_of_action;
    this->min_energy_for_division=another.min_energy_for_division;
    this->condition_for_attack=another.condition_for_attack;
    this->color=another.color;
    this->chance_of_mutation=another.chance_of_mutation;

    int is_mutation=mersenne()%100;
    int what_mutation=-1;
    if(is_mutation<chance_of_mutation){
        what_mutation=mersenne()%(56+number_of_gens_of_action*7+5);
        if(what_mutation==0){
            int half_chance=mersenne()%2;
            if(half_chance==0){
                if(number_of_gens_of_action>1){
                    int what_delete=mersenne()%(this->number_of_gens_of_action);
                    gens_of_action.erase(gens_of_action.begin()+what_delete);
                    this->number_of_gens_of_action--;
                }
            }
            else{
                std::vector<int>to_add;
                gens_of_action.push_back(to_add);
                for (int j = 0; j < 6; j++) {
                    gens_of_action[number_of_gens_of_action].push_back(mersenne() % 10);
                }
                gens_of_action[number_of_gens_of_action].push_back(mersenne() % 9);
                number_of_gens_of_action++;
            }
        }
        else if(what_mutation==1){
           min_energy_for_division*=((double(mersenne()%20+1))/10);
        }
        else if(what_mutation==2){
            condition_for_attack*=((double(mersenne()%20+1))/10);
        }
        else if(what_mutation==3){
            color=1+mersenne()%6;
        }
        else if(what_mutation==4){
            chance_of_mutation*=((double(mersenne()%20))/10);
            if(chance_of_mutation>99){
                chance_of_mutation=99;
            }
            else if(chance_of_mutation<1){
                chance_of_mutation=1;
            }
        }
        else{
            what_mutation-=5;
            if(what_mutation<56 && what_mutation%7==6){
                gens_of_irritation[what_mutation/7][6]=mersenne()% 9;
            }
            else if(what_mutation<56){
                gens_of_irritation[what_mutation/7][what_mutation%7]=mersenne()% 10;
            }
            else{
                what_mutation-=56;
                if(what_mutation%7==6){
                    gens_of_action[what_mutation/7][6]=mersenne()% 9;
                }
                else {
                    gens_of_action[what_mutation/7][what_mutation%7]=mersenne()% 10;
                }
            }
        }
    }

    this->superpower=this->color;

}

bool operator== (const Bot &first, const Bot &second){
    if(first.posX==second.posX && first.posY==second.posY){
        return true;
    }
    else{
        return false;
    }
}























