#pragma once
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

// Kiem tra nguyen to
bool isPrime(int x) {
    if (x <= 1)
        return 0;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return 0;
    return 1;
}
enum ItemType {/* TODO: */ };

class BaseBag {
public:
    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem* get(ItemType itemType);
    virtual string toString() const;
};

class BaseOpponent;

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag* bag;
    KnightType knightType;

public:
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight* temp;
    if (isPrime(temp->maxhp)) {
        temp = new PaladinKnight;
    }
    else if (maxhp == 888) {
        temp = new LancelotKnight;
    }
    else if (maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543) {
        temp = new DragonKnight;
    }
    else {
        temp = new NormalKnight;
    }
    temp->id = id;
    temp->maxhp = maxhp;
    temp->level = level;
    temp->gil = gil;
    temp->antidote = antidote;
    return temp;
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight() {
        this->knightType = LANCELOT;
   }
};
class DragonKnight : public BaseKnight {
public:
    DragonKnight() {
        this->knightType = DRAGON;
    }
};
class PaladinKnight : public BaseKnight {
public:
    PaladinKnight() {
        this->knightType = PALADIN;
    }
};
class NormalKnight : public BaseKnight {
public:
    NormalKnight() {
        this->knightType = NORMAL;
    }
};
class ArmyKnights {
public:
    static int knightid;
    ArmyKnights(const string& file_armyknights) {
        int quanlity;
        ifstream input(file_armyknights, ios::in);
        if (input.fail()) {
            cout << "Fail";
            return;
        }
        input >> quanlity;
        int id, maxhp, level, gil, antidote, phoenixdownI;
        input >> id >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        for (id = 1; id <= quanlity; id++) {
            *(Army + id - 1) = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    };
    ~ArmyKnights();
    BaseKnight** Army;
    bool fight(BaseOpponent* opponent);
    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};
class BaseItem {
public:
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};

class Events {
private:
    int* arr;
    int size;
public:
    Events(string s);
    int count() const;
    int get(int i) const;
    ~Events();
};
Events::Events(string s) {
    ifstream input(s, ios::in);
    input >> size;
    arr = new int[size + 1];
    for (int i = 0; i < size; i++) {
        input >> *(arr + i);
    }
};
int Events::count() const {
    return size;
};
int Events::get(int i) const {
    return arr[size];
};

class KnightAdventure {
private:
    ArmyKnights* armyKnights;
    Events* events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string&);
    void loadEvents(const string&);
    void run();
};

#endif // __KNIGHT2_H__