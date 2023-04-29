#include "knight2.h"
/* * * BEGIN implementation of class BaseBag * * */

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

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */

int BaseBag::countItem()
{
    int count = 0;
    Node *p = bag;
    while (p != NULL)
    {
        count++;
        p = p->pNext;
    }
    return count;
}
bool BaseBag::insertFirst(BaseItem *item)
{
    if (countItem() == maxSize)
        return 0;
    Node *p = createNode(item);
    if (p == NULL)
        return 0;
    p->pNext = bag;
    bag = p;
    return 1;
}
BaseBag::BaseBag(BaseKnight *knight, int a, int b)
{
    for (int i = 0; i <= a; i++)
    {
        phoenixdownI *temp = new phoenixdownI;
        insertFirst(temp);
    }
    if (knight->getType() != 2)
    {
        for (int i = 0; i <= b; i++)
        {
            antidote *temp = new antidote;
            insertFirst(temp);
        }
    }
}

PaladinBag::PaladinBag(BaseKnight *knight, int a, int b)
{
    maxSize = INT_MAX;
    BaseBag::BaseBag(knight, a, b);
}
LancelotBag::LancelotBag(BaseKnight *knight, int a, int b)
{
    maxSize = 16;
    BaseBag::BaseBag(knight, a, b);
}
DragonBag::DragonBag(BaseKnight *knight, int a, int b)
{
    maxSize = 14;
    BaseBag::BaseBag(knight, a, 0);
}
bool DragonBag::insertFirst(BaseItem *item)
{
    if (item->type == 0)
        return 0;
    if (BaseBag::countItem() == maxSize)
        return 0;
    Node* p = createNode(item);
    if (p == NULL)
        return 0;
    p->pNext = bag;
    bag = p;
    return 1;
}
NormalBag::NormalBag(BaseKnight *knight, int a, int b)
{
    maxSize = 19;
    BaseBag::BaseBag(knight, a, b);
}
