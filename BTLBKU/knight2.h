#pragma once
#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define DEBUG
class BaseKnight;
class BaseItem;
class ArmyKnights;
class BaseBag;
class Events;
class KnightAdventure;
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

class BaseBag
{
protected:
    int maxSize;
    BaseKnight* knight;
    Node* bag;
public:
    BaseBag();
    void delete_head();
    void createBag(BaseKnight* knight, int a, int b);
    virtual bool insertFirst(BaseItem* item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString() const;
    int countItem();
    void init();
    Node* getBag()const;
};
enum OpponentType {
    MadBeartype=1,
    Bandittype,
    LordLupintype,
    Elftype,
    Trolltype,
    Tornberytype,
    QueenofCardstype,
    NinaDeRingstype,
    DurianGardentype,
    OmegaWeapontype,
    Hadestype,
};
class BaseOpponent
{
public:
    int gil;
    int baseDamage;
    int levelO;
    int eventid;
    OpponentType Otype;
    virtual void Win_effect(ArmyKnights* ArmyKnight);
    virtual void Lose_effect(BaseKnight* knight);
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
        this->Otype = MadBeartype;
    }
};
class Bandit : public BaseOpponent
{
public:
    Bandit()
    {
        this->baseDamage = 15;
        this->gil = 150;
        this->eventid = 2;
        this->Otype = Bandittype;
    }

};
class LordLupin : public BaseOpponent
{
public:
    LordLupin()
    {
        this->baseDamage = 45;
        this->gil = 450;
        this->eventid = 3;
        this->Otype = LordLupintype;
    }

};
class Elf : public BaseOpponent
{
public:
    Elf()
    {
        this->baseDamage = 75;
        this->gil = 750;
        this->eventid = 4;
        this->Otype = Elftype;
    }
};
class Troll : public BaseOpponent
{
public:
    Troll()
    {
        this->baseDamage = 95;
        this->gil = 800;
        this->eventid = 5;
        this->Otype = Trolltype;
    }

};
class Tornbery : public BaseOpponent
{
public:
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
    Tornbery() {
        this->eventid = 6;
        this->Otype = Tornberytype;
    }
};
class QueenOfCards : public BaseOpponent
{
public:
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
    QueenOfCards() {
        this->eventid = 7;
        this->Otype = QueenofCardstype;
    }
};
class NinaDeRings : public BaseOpponent {
public:
    NinaDeRings() {
        this->eventid = 8;
        this->Otype = NinaDeRingstype;
    }
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
    void Effect(BaseKnight* knight);
};
class DurianGarden :public BaseOpponent
{
public:
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
    void Effect(BaseKnight* knight);
    DurianGarden() {
        this->eventid = 9;
        this->Otype = DurianGardentype;
    }
};
class OmegaWeapon :public BaseOpponent
{
public:
    OmegaWeapon() {
        this->eventid = 10;
        this->Otype = OmegaWeapontype;
    }
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
};
class Hades : public BaseOpponent {
public:
    Hades() {
        this->eventid = 11;
        this->Otype = Hadestype;
    }
    void Win_effect(ArmyKnights* ArmyKnight);
    void Lose_effect(BaseKnight* knight);
};
enum KnightType
{
    PALADIN = 0,LANCELOT,DRAGON,NORMAL
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
    int phoenixI;
    double base_dmg;
public:
    BaseKnight()
    {
        this->poison = false;
    }
    ~BaseKnight();
    void levelup();
    float damage();
    virtual bool knight_fight(BaseOpponent* opponent);
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    void DropItem() {
        bag->delete_head();
    }
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
    double const get_base_dmg() {
        return this->base_dmg;
    }
    bool const getpoison()
    {
        return this->poison;
    }
    BaseBag* const getBag() {
        return bag;
    }
    KnightType const getType()
    {
        return knightType;
    };
    void setpoison(bool poison)
    {
        this->poison = poison;
    }
    void setgil(int gil) {
        this->gil = gil;
    }
    void setantidote(int antidote)
    {
        this->antidote = antidote;
    }
    void sethp(int hp)
    {
        this->hp = hp;
    }
    void setlevel(int level) {
        if (level >= 0 && level < 10) {
            this->level = level;
        }
    }

};
class LancelotKnight : public BaseKnight
{
public:
    bool knight_fight(BaseOpponent* opponent);
    LancelotKnight()
    {
        this->knightType = LANCELOT;
        this->base_dmg = 0.05;
        bag = new LancelotBag(this, phoenixI, antidote);
    }
};
class DragonKnight : public BaseKnight
{
public:
    bool knight_fight(BaseOpponent* opponent);
    DragonKnight()
    {
        this->base_dmg = 0.075;
        this->knightType = DRAGON;
        bag = new DragonBag(this, phoenixI, antidote);
    }
};
class PaladinKnight : public BaseKnight
{
public:
    bool knight_fight(BaseOpponent* opponent);
    PaladinKnight()
    {
        this->base_dmg = 0.06;
        this->knightType = PALADIN;
        bag = new PaladinBag(this, phoenixI, antidote);
    }
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight()
    {
        bag = new NormalBag(this, phoenixI, antidote);
        this->knightType = NORMAL;
    }
};
class ArmyKnights
{
public:
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;
    int quanlity;
    bool defeatOmega;
    bool defeatHades;
    ArmyKnights(const string &file_armyknights)
    {
        this->PaladinShield = false;
        this->LancelotSpear = false;
        this->GuinevereHair = false;
        this->ExcaliburSword = false;
        ifstream input(file_armyknights, ios::in);
        if (input.fail())
        {
            cout << "Fail";
            return;
        }
        input >> quanlity;
        Army = new BaseKnight*[quanlity];
        int id, maxhp, level, gil, antidote, phoenixdownI;
        input >> id >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        for (id = 1; id <= quanlity; id++)
        {
            BaseKnight* temp = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
            *(Army + id - 1) = temp;
        }
    }
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
    bool getdefeatOmega() {
        return this->defeatOmega;
    }
    void setdefeatOmega(bool defatOmega) {
        this->defeatOmega = defeatOmega;
    }
    bool getdefeatHades() {
        return this->defeatHades;
    }
    void setdefeatHades(bool defeatHades) {
        this->defeatHades = defeatHades;
    }
    void TakeGil(int gil);
    void TakeItem(BaseItem* Item);
    void UseItem(BaseKnight* knight);
    void Reborn(BaseKnight* knight);
};
class BaseItem
{
public:
    bool virtual canUse(BaseKnight* knight) = 0;
    void virtual use(BaseKnight* knight) = 0;
    ItemType type;
};
// Kiem tra nguyen to
bool isPrime(int x);
class antidote : public BaseItem
{
public:
    antidote()
    {
        type = Antidote;
    }
    bool canUse(BaseKnight* knight)
    {
        if (knight->getpoison())
            return true;
        return false;
    }
    void use(BaseKnight* knight) 
    {
        knight->setpoison(false);
        knight->setantidote(knight->getantidote() - 1);
    }
};
class phoenixdownI : public BaseItem
{
public:
    phoenixdownI()
    {
        type = PhoenixdownI;
    }
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
class Ultimecia {
private:
    float hp;
public:
    Ultimecia();
    // 1 win -  0 lose
     bool fight(ArmyKnights* ArmyKnight);
};
#endif // __KNIGHT2_H__