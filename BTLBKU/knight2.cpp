#include "knight2.h"
/* * * BEGIN implementation of class BaseBag * * */


void BaseBag::delete_head() {
    if (bag == NULL)
        return;
    Node* p = bag;
    bag = bag->pNext;
    p->pNext = NULL;
    delete p;
}
Node* createNode(BaseItem* item)
{
    Node* p = new Node;
    if (p == NULL)
        return NULL;
    p->item = item;
    p->pNext = NULL;
    return p;
}
int BaseBag::countItem() {
    int count = 0;
    Node* p = bag;
    while (p != NULL)
    {
        count++;
        p = p->pNext;
    }
    return count;
};
bool BaseBag::insertFirst(BaseItem* item) {
    if (countItem() == maxSize)
        return 0;
    Node* p = createNode(item);
    if (p == NULL)
        return 0;
    p->pNext = bag;
    bag = p;
    return 1;
};
BaseItem* BaseBag::get(ItemType itemType) {
    if (bag->item->type == itemType) {
        BaseItem* temp = bag->item;
        bag->item = NULL;
        temp->use(this->knight);
        delete_head();
        return temp;
    }
    Node* p = bag;
    while (p->pNext!= NULL && p->pNext->item->type != itemType)
        p = p->pNext;
    if (p->pNext == NULL)
        return NULL;
    Node* temp = p->pNext;
    p->pNext = temp->pNext;
    temp->pNext = bag;
    bag = temp;
    BaseItem* Item_temp = temp->item;
    temp->item = NULL;
    Item_temp->use(this->knight);
    delete_head();
    return Item_temp;
}
class DragonBag : public BaseBag
{
public:
    DragonBag(BaseKnight* knight, int a, int b) {
        maxSize = 14;
        BaseBag::createBag(knight, a, 0);
    };
    bool insertFirst(BaseItem* item) {
        if (item->type == 0)
            return 0;
        if (countItem() == maxSize)
            return 0;
        Node* p = createNode(item);
        if (p == NULL)
            return 0;
        p->pNext = bag;
        bag = p;
        return 1;
    };
};
class PaladinBag : public BaseBag
{
public:
    PaladinBag(BaseKnight* knight, int a, int b) {
        maxSize = INT_MAX;
        BaseBag::createBag(knight, a, b);
    };
};
class NormalBag : public BaseBag
{
    NormalBag(BaseKnight* knight, int a, int b) {
        maxSize = 19;
        BaseBag::createBag(knight, a, b);

    };
};
class LancelotBag : public BaseBag
{
    LancelotBag(BaseKnight* knight, int a, int b) {
        maxSize = 16;
        BaseBag::createBag(knight, a, b);
    };
};
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight* temp;
    if (isPrime(temp->maxhp))
    {
        temp = new PaladinKnight;
    }
    else if (maxhp == 888)
    {
        temp = new LancelotKnight;
    }
    else if (maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543)
    {
        temp = new DragonKnight;
    }
    else
    {
        temp = new NormalKnight;
    }
    temp->id = id;
    temp->hp = maxhp;
    temp->level = level;
    temp->gil = gil;
    temp->antidote = antidote;
    return temp;
};
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight()
    {
        this->knightType = LANCELOT;
    }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight()
    {
        this->knightType = DRAGON;
    }
};
class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight()
    {
        this->knightType = PALADIN;
    }
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight()
    {
        this->knightType = NORMAL;
    }
};
/* * * END implementation of class BaseKnight * * */
/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}
BaseKnight* ArmyKnights::lastKnight() const {
    return Army[quanlity - 1];
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
    for (int i = quanlity - 1; i <= 0; i++) {
        if (Army[i]->knight_fight(opponent) == NULL)
            return 1;
    }
    return 0;
}
/* * * END implementation of class ArmyKnights * * */

KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * BEGIN implementation of class KnightAdventure * * */
