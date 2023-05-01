#pragma once
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

// Kiem tra nguyen to
bool isPrime(int x)
{
    if (x <= 1)
        return 0;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;
    return 1;
}
enum ItemType
{
    Antidote = 0,
    PhoenixdownI,
    PhoenixdownII,
    PhoenixdownIII,
    PhoenixdownIV
};
struct Node
{
    BaseItem* item;
    struct Node* pNext;
};
Node* createNode(BaseItem* item)
{
    Node* p = new Node;
    if (p == NULL)
        return NULL;
    p->item = item;
    p->pNext = NULL;
    return p;
}
class BaseBag
{
protected:
    int maxSize;
    BaseKnight* knight;
public:
    void createBag(BaseKnight* knight, int a, int b) {
        this->knight = knight;
        for (int i = 0; i <= a; i++)
        {
            phoenixdownI* temp = new phoenixdownI;
            insertFirst(temp);
        }
        if (knight->getType() != 2)
        {
            for (int i = 0; i <= b; i++)
            {
                antidote* temp = new antidote;
                insertFirst(temp);
            }
        }
    };
    Node* bag;
    virtual bool insertFirst(BaseItem* item) {
        if (countItem() == maxSize)
            return 0;
        Node* p = createNode(item);
        if (p == NULL)
            return 0;
        p->pNext = bag;
        bag = p;
        return 1;
    };
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
    int countItem() {
        int count = 0;
        Node* p = bag;
        while (p != NULL)
        {
            count++;
            p = p->pNext;
        }
        return count;
    };
    void init()
    {
        bag = NULL;
    }
};
class BaseOpponent
{
protected:
    int gil;
    int baseDamage;
    int levelO;
    int eventid;

public:
    int setlevelO(int i) {
        this->levelO = (i + eventid) % 10 + 1;
        return this->levelO;
    };
};
class MadBear : public BaseOpponent
{
public:
    MadBear()
    {
        this->baseDamage = 10;
        this->gil = 100;
        this->eventid = 1;
    }
    ~MadBear();
};
class Bandit : public BaseOpponent
{
public:
    Bandit()
    {
        this->baseDamage = 15;
        this->gil = 150;
        this->eventid = 2;
    }
    ~Bandit();

};
class LordLupin : public BaseOpponent
{
public:
    LordLupin()
    {
        this->baseDamage = 45;
        this->gil = 450;
        this->eventid = 3;
    }
    ~LordLupin();

};
class Elf : public BaseOpponent
{
public:
    Elf()
    {
        this->baseDamage = 75;
        this->gil = 750;
        this->eventid = 4;
    }
    ~Elf();
};
class Troll : public BaseOpponent
{
public:
    Troll()
    {
        this->baseDamage = 95;
        this->gil = 800;
        this->eventid = 5;
    }
    ~Troll();

};
class Tornbery : public BaseOpponent
{
    Tornbery() {
        this->eventid = 6;
    }
    ~Tornbery();
};
class QueenofCards : public BaseOpponent
{
    QueenofCards() {
        this->eventid = 7;
    }
    ~QueenofCards();
};

enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    bool poison;
    BaseBag* bag;
    KnightType knightType;

public:
    BaseKnight()
    {
        this->poison = false;
    }
    ~BaseKnight();
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    int const getmaxhp()
    {
        return this->maxhp;
    }
    int const gethp()
    {
        return this->hp;
    }
    int const getlevel()
    {
        return this->level;
    }
    int const getgil()
    {
        return this->gil;
    }
    int const getantidote()
    {
        return this->antidote;
    }
    bool const getpoison()
    {
        return this->poison;
    }
    KnightType const getType()
    {
        return knightType;
    };
    void setpoison(bool poison)
    {
        this->poison = poison;
    }
    void setantidote(int antidote)
    {
        this->antidote = antidote;
    }
    void sethp(int hp)
    {
        this->hp = hp;
    }
};

class ArmyKnights
{
public:
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;
    ArmyKnights(const string &file_armyknights)
    {
        int quanlity;
        ifstream input(file_armyknights, ios::in);
        if (input.fail())
        {
            cout << "Fail";
            return;
        }
        input >> quanlity;
        int id, maxhp, level, gil, antidote, phoenixdownI;
        input >> id >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        for (id = 1; id <= quanlity; id++)
        {
            *(Army + id - 1) = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    };
    ~ArmyKnights();
    BaseKnight **Army;
    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};
class BaseItem
{
public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
    ItemType type;
};
class antidote : public BaseItem
{
public:
    antidote()
    {
        type = Antidote;
    }
    ~antidote();
    bool canUse(BaseKnight* knight)
    {
        if (knight->getpoison())
            return true;
        else
            return false;
    }
    void use(BaseKnight* knight)
    {
        knight->setpoison(false);
        knight->setantidote(knight->getantidote() - 1);
    };
};
class phoenixdownI : public BaseItem
{
public:
    phoenixdownI()
    {
        type = PhoenixdownI;
    }
    ~phoenixdownI();
    bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() <= 0)
            return true;
        else
            return false;
    }
    void use(BaseKnight* knight)
    {
        knight->sethp(knight->getmaxhp());
    }
};
class phoenixdownII : public BaseItem
{
public:
    phoenixdownII()
    {
        type = PhoenixdownII;
    }
    ~phoenixdownII();
    bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->gethp() / 4))
            return true;
        else
            return false;
    }
    void use(BaseKnight* knight)
    {
        knight->sethp(knight->getmaxhp());
    }
};
class phoenixdownIII : public BaseItem
{
public:
    phoenixdownIII()
    {
        type = PhoenixdownIII;
    }
    ~phoenixdownIII();
    bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->gethp() / 3))
            return true;
        else
            return false;
    }
    void use(BaseKnight* knight)
    {
        if (knight->gethp() <= 0)
            knight->sethp(knight->getmaxhp() / 3);
        else
            knight->sethp(knight->gethp() + knight->getmaxhp() / 4);
    }
};
class phoenixdownIV : public BaseItem
{
public:
    phoenixdownIV()
    {
        type = PhoenixdownIV;
    }
    ~phoenixdownIV();
    bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->gethp() / 2))
            return true;
        else
            return false;
    }
    void use(BaseKnight* knight)
    {
        if (knight->gethp() <= 0)
            knight->sethp(knight->getmaxhp() / 2);
        else
            knight->sethp(knight->gethp() + knight->getmaxhp() / 5);
    }
};
class Events
{
private:
    int *arr;
    int size;

public:
    Events(string s);
    int count() const;
    int get(int i) const;
    ~Events();
};
Events::Events(string s)
{
    ifstream input(s, ios::in);
    input >> size;
    arr = new int[size + 1];
    for (int i = 0; i < size; i++)
    {
        input >> *(arr + i);
    }
};
int Events::count() const
{
    return size;
};
int Events::get(int i) const
{
    return arr[i];
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &inputarmy);
    void loadEvents(const string &inputevent);
    void run();
};
#endif // __KNIGHT2_H__