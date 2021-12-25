#include "logic.h"

#include <random>

static std::random_device dev;
static std::mt19937 mersenne(dev());

Logic::Tree::Tree():
    m_Energy(300),
    m_Age(0)
{
    for(auto& gen :m_Gens){
        for(size_t i = 0; i < 4; i++){
            gen[i] = mersenne()%32;
        }
        for(size_t i = 4; i < 6; i++){
            gen[i] = mersenne()%60;
        }
        gen[6] = mersenne()%17;
    }
}

Logic::Tree::Tree(const Logic::Tree& another, int32_t energy) :
    m_Gens(another.m_Gens),
    m_Energy(energy),
    m_Age(0)
{
    if(mersenne()%4 == 0){
        size_t posInGen = mersenne()%7;
        if(posInGen < 4){
            m_Gens[mersenne()%16][posInGen] = mersenne()%32;
        }
        else if(posInGen == 6){
            m_Gens[mersenne()%16][posInGen] = mersenne()%17;
        }
        else{
            m_Gens[mersenne()%16][posInGen] = mersenne()%60;
        }
    }
}

void Logic::Tree::ChangeEnergy(int change){
    m_Energy += change;
}

Logic::Tree::Gen Logic::Tree::GetGen(int pos)
{
    return m_Gens[pos];
}

void Logic::Tree::AddItem(size_t x, size_t y)
{
    m_Items.push_back({x,y});
}

int32_t Logic::Tree::GetEnergy() const
{
    return m_Energy;
}

const std::vector<Logic::Coordinates>& Logic::Tree::GetItems() const
{
    return m_Items;
}

int Logic::Tree::GetAge() const
{
    return m_Age;
}

void Logic::Tree::SetAge(int age)
{
    m_Age = age;
}
