#include "logic.h"

Logic::Item::Item() :
    m_ActiveGen(0),
    m_Type(Type::NONE),
    m_PersonalEnergy(0) {}

void Logic::Item::MakeNone(){
    m_ActiveGen = 0;
    m_Type = Type::NONE;
    m_PersonalEnergy = 0;
}

void Logic::Item::SetTree(std::list<Logic::Tree>::iterator tree)
{
    m_Tree = tree;
}

std::list<Logic::Tree>::iterator Logic::Item::GetTree() const
{
    return m_Tree;
}

int Logic::Item::GetGen() const
{
    return m_ActiveGen;
}

void Logic::Item::SetGen(int gen)
{
    m_ActiveGen = gen;
}

Logic::Item::Type Logic::Item::GetType() const{
    return m_Type;
}

void Logic::Item::SetType(Logic::Item::Type type){
    m_Type = type;
}

int Logic::Item::GetEnergy() const
{
    return m_PersonalEnergy;
}

void Logic::Item::SetEnergy(int value)
{
    m_PersonalEnergy = value;
}
