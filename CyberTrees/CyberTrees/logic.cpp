#include "logic.h"

Logic::Logic()
{
    for(int i=0;i<1000;i++){
        for(int j=0;j<100;j++){
            m_Items[i][j] = new Item();
            m_Items[i][j]->MakeNone();
        }
    }
}

void Logic::Start()
{
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < 100; j++){
            if(m_Items[i][j]->GetType() != Item::Type::NONE) m_Items[i][j]->MakeNone();
            m_Changed.emplace_back(Coordinates(i, j),Item::Type::NONE);
        }
    }
    for(size_t i = 10; i < 1000; i+=50){
        m_Trees.push_back(Tree());
        auto& item = m_Items[i][0];
        item->SetType(Item::Type::SPROUT);
        item->SetTree(std::prev(m_Trees.end()));
        m_Trees.back().AddItem(i,0);
        m_Changed.emplace_back(Coordinates(i, 0),Item::Type::SPROUT);
    }
}

void Logic::Play()
{
    std::list<Tree>newTrees;
    m_Changed.clear();
    m_Seeds.clear();
    for(size_t column = 0; column < m_Items.size(); column++){
        int level = 6;
        int wasWoods = 0;
        for(int i = m_Items[column].size()-1; i >= 0; i--){
            if(m_Seeds.count(std::make_pair(column, size_t(i)))) continue;
            switch(m_Items[column][i]->GetType()){
            case Item::Type::NONE : {
                level = level==6 ? 6 : level+1;
                break;
            }
            case Item::Type::SEED : {
                if(m_Items[column][i-1]->GetType() == Item::Type::NONE){
                    std::swap(m_Items[column][i-1], m_Items[column][i]);
                    m_Changed.emplace_back(Coordinates(column, i-1),Item::Type::SEED);
                    m_Changed.emplace_back(Coordinates(column, i),Item::Type::NONE);
                    if(i-1 == 0){
                        ActivateTree(column);
                        break;
                    }
                    m_Seeds.emplace(column, i-1);
                }
                else{
                    m_Changed.emplace_back(Coordinates(column, i),Item::Type::NONE);
                    m_Trees.erase(m_Items[column][i]->GetTree());
                    m_Items[column][i]->MakeNone();
                }
                break;
            }
            case Item::Type::SPROUT : {
                m_Items[column][i]->GetTree()->ChangeEnergy(-10);
                if(wasWoods <6){
                    m_Items[column][i]->SetEnergy(m_Items[column][i]->GetEnergy() + (level > 0 ? level : 0) * 3);
                }
                if(m_Items[column][i]->GetEnergy() > 17){
                    bool skip = false;
                    auto gen = m_Items[column][i]->GetTree()->GetGen(m_Items[column][i]->GetGen());
                    if(gen[4] < 15){
                        bool activeCondition = false;
                        switch (gen[4]) {
                        case 0: {
                            activeCondition = i > gen[5];
                            break;
                        }
                        case 1: {
                            activeCondition = i < gen[5];
                            break;
                        }
                        case 2: {
                            activeCondition = i == gen[5];
                            break;
                        }
                        case 3: {
                            activeCondition = m_Items[column][i]->GetTree()->GetItems().size() > gen[5]*4;
                            break;
                        }
                        case 4: {
                            activeCondition = m_Items[column][i]->GetTree()->GetItems().size() < gen[5]*4;
                            break;
                        }
                        case 5: {
                            activeCondition = m_Items[column][i]->GetTree()->GetItems().size() == gen[5]*4;
                            break;
                        }
                        case 6: {
                            activeCondition = 90 - m_Items[column][i]->GetTree()->GetAge() > gen[5]*2;
                            break;
                        }
                        case 7: {
                            activeCondition = 90 - m_Items[column][i]->GetTree()->GetAge() < gen[5]*2;
                            break;
                        }
                        case 8: {
                            activeCondition = 90 - m_Items[column][i]->GetTree()->GetAge() > gen[5]*2;
                            break;
                        }
                        case 9: {
                            activeCondition = 90 - m_Items[column][i]->GetTree()->GetAge() == gen[5]*2;
                            break;
                        }
                        case 10: {
                            activeCondition = m_Items[column][i]->GetTree()->GetEnergy() > gen[5]*100;
                            break;
                        }
                        case 11: {
                            activeCondition = m_Items[column][i]->GetTree()->GetEnergy() < gen[5]*100;
                            break;
                        }
                        case 12: {
                            activeCondition = m_Items[column][i]->GetTree()->GetEnergy() == gen[5]*100;
                            break;
                        }
                        case 13: {
                            activeCondition = (level > 0 ? level : 0) * 3 < 10;
                            break;
                        }
                        case 14: {
                            activeCondition = (level > 0 ? level : 0) * 3 == 0;
                            break;
                        }
                        }
                        if(activeCondition && gen[6] < 16){
                            gen = m_Items[column][i]->GetTree()->GetGen(gen[6]);
                        }
                        else if(activeCondition && gen[6] == 16){
                            skip = true;
                        }
                        else if(activeCondition && gen[6] == 17){
                            m_Items[column][i]->SetEnergy(0);
                            Tree tree(*m_Items[column][i]->GetTree(),100);
                            newTrees.push_back(tree);
                            m_Items[column][i]->SetTree(std::prev(newTrees.end()));
                            m_Items[column][i]->SetType(Item::Type::SEED);
                            m_Seeds.emplace(column, i);
                            if(i == 0){
                                ActivateTree(column);
                            }
                            skip = true;
                        }
                    }
                    if(!skip){
                        bool isWood = false;
                        bool isGen = false;
                        if(gen[0] < 16){
                            isGen = true;
                            if(i < 99 && m_Items[column][i+1]->GetType() == Item::Type::NONE){
                                m_Items[column][i+1]->SetType(Item::Type::SPROUT);
                                m_Items[column][i+1]->SetGen(gen[0]);
                                m_Items[column][i+1]->SetTree(m_Items[column][i]->GetTree());
                                m_Items[column][i]->GetTree()->AddItem(column, i+1);
                                isWood = true;
                                m_Changed.emplace_back(Coordinates(column, i+1),Item::Type::SPROUT);
                                m_Seeds.emplace(column, i+1);
                            }
                        }
                        if(gen[1] < 16){
                            isGen = true;
                            if(m_Items[(column+1)%m_Items.size()][i]->GetType() == Item::Type::NONE){
                                size_t pos = (column+1)%m_Items.size();
                                m_Items[pos][i]->SetType(Item::Type::SPROUT);
                                m_Items[pos][i]->SetGen(gen[1]);
                                m_Items[pos][i]->SetTree(m_Items[column][i]->GetTree());
                                m_Items[column][i]->GetTree()->AddItem(pos, i);
                                isWood = true;
                                m_Changed.emplace_back(Coordinates(pos, i),Item::Type::SPROUT);
                                m_Seeds.emplace(pos, i);
                            }
                        }
                        if(gen[2] < 16){
                            isGen = true;
                            if(i > 0 && m_Items[column][i-1]->GetType() == Item::Type::NONE){
                                size_t pos = i == 0 ? 0:i-1;
                                m_Items[column][pos]->SetType(Item::Type::SPROUT);
                                m_Items[column][pos]->SetGen(gen[2]);
                                m_Items[column][pos]->SetTree(m_Items[column][i]->GetTree());
                                m_Items[column][i]->GetTree()->AddItem(column, pos);
                                isWood = true;
                                m_Changed.emplace_back(Coordinates(column, pos),Item::Type::SPROUT);
                                m_Seeds.emplace(column, pos);
                            }
                        }
                        if(gen[3] < 16){
                            isGen = true;
                            if(m_Items[column == 0 ? m_Items.size()-1 : column-1][i]->GetType() == Item::Type::NONE){
                                size_t pos = column == 0 ? m_Items.size()-1 : column-1;
                                m_Items[pos][i]->SetType(Item::Type::SPROUT);
                                m_Items[pos][i]->SetGen(gen[3]);
                                m_Items[pos][i]->SetTree(m_Items[column][i]->GetTree());
                                m_Items[column][i]->GetTree()->AddItem(pos, i);
                                isWood = true;
                                m_Changed.emplace_back(Coordinates(pos, i),Item::Type::SPROUT);
                                m_Seeds.emplace(pos, i);
                            }
                        }
                        if(isWood || !isGen){
                            m_Items[column][i]->SetType(Item::Type::WOOD);
                            m_Changed.emplace_back(Coordinates(column, i),Item::Type::WOOD);
                        }
                        if(isWood){
                            m_Items[column][i]->GetTree()->ChangeEnergy(-18);
                        }
                    }
                }
                --level;
                wasWoods++;
                break;
            }
            case Item::Type::WOOD : {
                m_Items[column][i]->GetTree()->ChangeEnergy(-10);
                if(wasWoods <6){
                    m_Items[column][i]->GetTree()->ChangeEnergy((level > 0 ? level : 0) * 3);
                }
                --level;
                wasWoods++;
                break;
            }
            }
        }
    }
    auto it = m_Trees.begin();
    while(it!=m_Trees.end()){
        it->SetAge(it->GetAge()+1);
        if(it->GetEnergy() < 0 || it->GetAge() == 90){
            int numberOfSeeds = 0;
            for(auto& coordinates : it->GetItems()){
                if(m_Items[coordinates.x][coordinates.y]->GetType() == Item::Type::SPROUT){
                    ++numberOfSeeds;
                }
            }
            for(auto& coordinates : it->GetItems()){
                if(it->GetAge() == 90 && m_Items[coordinates.x][coordinates.y]->GetType() == Item::Type::SPROUT){
                    m_Items[coordinates.x][coordinates.y]->SetEnergy(0);
                    Tree tree(*it,300);
                    newTrees.push_back(tree);
                    m_Items[coordinates.x][coordinates.y]->SetTree(std::prev(newTrees.end()));
                    m_Items[coordinates.x][coordinates.y]->SetType(Item::Type::SEED);
                    m_Seeds.emplace(coordinates.x, coordinates.y);
                    if(coordinates.y == 0){
                        ActivateTree(coordinates.x);
                    }
                }
                else{
                    m_Items[coordinates.x][coordinates.y]->MakeNone();
                    m_Changed.emplace_back(Coordinates(coordinates.x, coordinates.y),Item::Type::NONE);
                }
            }
            if(std::prev(m_Trees.end()) == it){
                m_Trees.erase(it);
                break;
            }
            else{
                m_Trees.erase(it++);
                continue;
            }
        }
        ++it;
    }
    m_Trees.splice(m_Trees.end(),newTrees);
}

std::vector<std::pair<Logic::Coordinates, Logic::Item::Type>>& Logic::GetChanged()
{
    return m_Changed;
}

void Logic::ActivateTree(size_t col)
{
    auto& item = m_Items[col][0];
    item->GetTree()->SetAge(0);
    item->SetType(Item::Type::SPROUT);
    item->SetGen(0);
    item->GetTree()->AddItem(col, 0);
}

const std::array<std::array<Logic::Item*,100>,1000>& Logic::GetItems() const
{
    return m_Items;
}
