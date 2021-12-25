#pragma once

#include <vector>
#include <list>
#include <utility>
#include <array>
#include <set>

class Logic
{
public:
    struct Coordinates{
        Coordinates(size_t x, size_t y):
            x(x), y(y) {}
        size_t x, y;
    };

    class Tree
    {
    public:
        using Gen = std::array<int, 7>;

        Tree();

        Tree(const Tree& another, int32_t energy);

        void ChangeEnergy(int change);

        Gen GetGen(int pos);

        int32_t GetEnergy() const;

        const std::vector<Coordinates>& GetItems() const;

        int GetAge() const;

        void SetAge(int age);

        void AddItem(size_t x, size_t y);
    private:
        std::array<Gen,16>m_Gens;
        std::vector<Coordinates>m_Items;
        int32_t m_Energy;
        int m_Age;
    };

    class Item {
    public:

        Item();

        void MakeNone();

        enum class Type {
            SEED,
            SPROUT,
            WOOD,
            NONE
        };

        void SetTree(std::list<Tree>::iterator tree);

        std::list<Tree>::iterator GetTree() const;

        int GetGen() const;

        void SetGen(int gen);

        Type GetType() const;

        void SetType(Type type);

        int GetEnergy() const;

        void SetEnergy(int value);
    private:
        std::list<Tree>::iterator m_Tree;
        int m_ActiveGen;
        Type m_Type;
        int m_PersonalEnergy;
    };

    Logic();

    std::vector<std::pair<Coordinates, Item::Type>>& GetChanged();

    void Play();

    void Start();

    void ActivateTree(size_t col);

    const std::array<std::array<Item*,100>,1000>& GetItems() const;

private:
    std::array<std::array<Item*,100>,1000>m_Items;
    std::set<std::pair<size_t, size_t>>m_Seeds;
    std::list<Tree>m_Trees;
    std::vector<std::pair<Coordinates, Item::Type>>m_Changed;
};

