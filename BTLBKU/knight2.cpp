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
void BaseOpponent::Win_effect(ArmyKnights* ArmyKnight) {
    ArmyKnight->Army[ArmyKnight->quanlity - 1]->levelup();
    ArmyKnight->TakeGil(this->gil);
}
void BaseOpponent::Lose_effect(BaseKnight* knight) {
    knight->sethp(knight->gethp() - this->baseDamage * (this->levelO - knight->getlevel()));
}
void Tornbery::Win_effect(ArmyKnights* ArmyKnight) {
    ArmyKnight->Army[ArmyKnight->quanlity - 1]->levelup();
}
void Tornbery::Lose_effect(BaseKnight* knight) {
    if (knight->getantidote() >= 1)
    {
        knight->setantidote(knight->getantidote() - 1);
    }
    else {
        for (int i = 0; i < 3; i++)
            knight->DropItem();
    }
    knight->sethp(knight->gethp() - 10);
}
void QueenOfCards::Win_effect(ArmyKnights* ArmyKnight){
    ArmyKnight->TakeGil(ArmyKnight->Army[ArmyKnight->quanlity-1]->getgil()*2);
}
void QueenOfCards::Lose_effect(BaseKnight* knight){
    knight->setgil(knight->getgil() / 2);
}
void NinaDeRings::Win_effect(ArmyKnights* ArmyKnight){
    return;
}
void NinaDeRings::Lose_effect(BaseKnight* knight) {
    return;
}
void NinaDeRings::Effect(BaseKnight* knight) {
    if (knight->getgil() < 50)
        return;
    else if (knight->gethp() < knight->getmaxhp() / 3)
    {
        knight->setgil(knight->getgil() - 50);
        knight->sethp(knight->gethp() + knight->getmaxhp() / 5);
    }
}
void OmegaWeapon::Win_effect(ArmyKnights* ArmyKnight){
    ArmyKnight->defeatOmega = 1;
    ArmyKnight->lastKnight()->setlevel(10);
    ArmyKnight->lastKnight()->setgil(999);
}
void OmegaWeapon::Lose_effect(BaseKnight* knight){
    knight->sethp(0);
}
void Hades::Win_effect(ArmyKnights* ArmyKnight){
    ArmyKnight->PaladinShield = 1;
    ArmyKnight->defeatHades = 1;
}
void Hades::Lose_effect(BaseKnight* knight){
    knight->sethp(0);
}
void DurianGarden::Win_effect(ArmyKnights* ArmyKnight){
    return;
}
void DurianGarden::Lose_effect(BaseKnight* knight){
    return;
}
void DurianGarden::Effect(BaseKnight* knight) {
    knight->sethp(knight->getmaxhp());
}
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
void BaseKnight::levelup() {
    this->setlevel(this->getlevel() + 1);
}
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight()
    {
        this->knightType = LANCELOT;
        this->base_dmg = 0.05;
    }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight()
    {
        this->base_dmg = 0.075;
        this->knightType = DRAGON;
    }
};
class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight()
    {
        this->base_dmg = 0.06;
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
bool BaseKnight::knight_fight(BaseOpponent* opponent) {
    switch (opponent->Otype)
    {
        case 1:
            if (this->getlevel() >= opponent->levelO) {
                return true;
                break;
            }
            else {
                return false;
                break;
        }
        case 2:
            if (this->getlevel() >= opponent->levelO) {
                return true;
                break;
            }
            else {
                return false;
                break;
            }
        case 3:
            if (this->getlevel() >= opponent->levelO) {
                return true;
                break;
            }
            else {
                return false;
                break;
            }
        case 4:
            if (this->getlevel() >= opponent->levelO) {
                return true;
                break;
            }
            else {
                return false;
                break;
            }
        case 5:
            if (this->getlevel() >= opponent->levelO) {
                return true;
                break;
            }
            else {
                return false;
                break;
            }
        case 6:
            if (this->getlevel() >= opponent->levelO) {
                this->setlevel(this->getlevel() + 1);
                return true;
                break;
            }
            else {
                this->setpoison(true);
                if (this->getantidote() >= 1) {
                    this->setantidote(this->getantidote() - 1);
                    break;
                }
                else{
                    /* GỌI HÀM RỚT 3 MÓN ĐỒ
                    CẬP NHẬP LẠI MÁU
                    CẬP NHẬP LẠI TÚI ĐỒ
                    */
            }
            }
        case 7:
        case 8:
            if (this->getgil() < 50) break;
            else if (this->gethp() < this->getmaxhp() / 3 && this->getgil() >= 50) {
                this->setgil(this->getgil() - 50);
                this->sethp(this->gethp() + this->getmaxhp() / 5);
                break;
            }
        case 9:
            this->sethp(this->getmaxhp());
            break;
        case 10:
            if ((this->getlevel() == 10 && this->gethp() == this->getmaxhp()) || this->knightType == DRAGON) {
                this->setgil(999);
                this->setlevel(9);
                return true;
                break;
            }
            else {
                return false;
                break;
            }
        case 11:
            if (this->getlevel() == 10 || (this->getType() == PALADIN && this->getlevel() > 8)) {

                return true;

            }


    }
}
float BaseKnight::damage() {
    return hp * level * base_dmg;
}
BaseKnight::~BaseKnight() {
    delete [] bag;
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
BaseKnight* ArmyKnights::lastKnight() const {
    return Army[quanlity - 1];
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
    do
    {
        if (lastKnight()->knight_fight(opponent) == 1)
            return 1;
        quanlity--;
    } while (quanlity > 0);
    
    return 0;
}
bool ArmyKnights::hasPaladinShield() const {
    return this->PaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const {
    return this->LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const {
    return this->GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const {
    return this->ExcaliburSword;
}
void ArmyKnights::TakeGil(int gil) {
    for (int i = quanlity - 1; i >= 0; i--) {
        if (Army[i]->getgil() + gil > 999) {
            gil = Army[i]->getgil() + gil - 999;
            Army[i]->setgil(999);
        }
        else {
            Army[i]->setgil(Army[i]->getgil() + gil);
            return;
        }
    }
}
int ArmyKnights::count() const {
    return quanlity;
}
/* * * END implementation of class ArmyKnights * * */

KnightAdventure::KnightAdventure()
{
    armyKnights = nullptr;
    events = nullptr;
}

/* * * BEGIN implementation of class KnightAdventure * * */

/* * * END implementation of class Ultimecia * * */
Ultimecia::Ultimecia() {
    this->hp = 5000;
}
bool Ultimecia::fight(ArmyKnights*& ArmyKnight) {
    int quanlity = ArmyKnight->quanlity;
    for (int i = quanlity; i <=0 ; i--) {
        if (ArmyKnight->Army[i]->getType() < 3) {
            this->hp -= ArmyKnight->Army[i]->damage();
        }
    }
    if (hp <= 0)
        return 1;
    return 0;
}


/* * * BEGIN implementation of class Ultimecia * * */