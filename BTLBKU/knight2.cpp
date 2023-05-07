#include "knight2.h"
/* * * BEGIN implementation of class BaseItem * * */


bool isPrime(int x)
{
	if (x <= 1)
		return 0;
	for (int i = 2; i * i <= x; i++)
		if (x % i == 0)
			return 0;
	return 1;
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag() {
	init();
	num = 0;
}
void BaseBag::init()
{
	bag = NULL;
}
Node* BaseBag::getBag()const {
	return bag;
}
void BaseBag::createBag(BaseKnight* knight, int a, int b) {
	this->knight = knight;
	for (int i = 0; i < a; i++)
	{
		phoenixdownI* temp = new phoenixdownI;
		insertFirst(temp);
	}
	if (knight->getType() != 2)
	{
		for (int i = 0; i < b; i++)
		{
			antidote* temp = new antidote;
			insertFirst(temp);
		}
	}
};

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
	num++;
	return 1;
};
BaseItem* BaseBag::get(ItemType itemType) {
	if (bag->item->type == itemType) {
		BaseItem* temp = bag->item;
		bag->item = NULL;
		temp->use(this->knight);
		delete_head();
		num--;
		return temp;
	}
	Node* p = bag;
	while (p->pNext != NULL && p->pNext->item->type != itemType)
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
string  BaseBag::toString() const {

	string s = "Bag[count=" + to_string(num) + ";";
	Node* p = bag;
	while (p != NULL) {
		switch (p->item->type)
		{
		case 0:
			s += "Antidote";
			break;
		case 1:
			s += "PhoenixI";
			break;
		case 2:
			s += "PhoenixII";
			break;
		case 3:
			s += "PhoenixIII";
			break;
		case 4:
			s += "PhoenixIV";
			break;
		default:
			break;
		}
		if (p->pNext != NULL)
			s += ",";
		p = p->pNext;
	}
	s += "]";
	return s;
}
DragonBag::DragonBag(BaseKnight* knight, int a, int b) {
	maxSize = 14;
	BaseBag::createBag(knight, a, 0);
};
bool DragonBag::insertFirst(BaseItem* item) {
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
PaladinBag::PaladinBag(BaseKnight* knight, int a, int b) {
	maxSize = 9999;
	BaseBag::createBag(knight, a, b);
};
LancelotBag::LancelotBag(BaseKnight* knight, int a, int b) {
	maxSize = 16;
	BaseBag::createBag(knight, a, b);
};
NormalBag::NormalBag(BaseKnight* knight, int a, int b) {
	maxSize = 19;
	BaseBag::createBag(knight, a, b);
};
/* * * END implementation of class BaseBag * * */
void BaseOpponent::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->TakeGil(this->gil);
}
void BaseOpponent::Lose_effect(BaseKnight* knight) {
	knight->sethp(knight->gethp() - this->baseDamage * (this->levelO - knight->getlevel()));
}
void Tornbery::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->lastKnight()->levelup();
}
void Tornbery::Lose_effect(BaseKnight* knight) {
	if (knight->getantidote() >= 1)
	{
		knight->setantidote(knight->getantidote() - 1);
		BaseItem* temp = knight->getBag()->get(Antidote);
		delete temp;
		knight->setpoison(false);
	}
	else {
		for (int i = 0; i < 3; i++)
			knight->DropItem();

		knight->sethp(knight->gethp() - 10);
		knight->setpoison(false);
	}
}
void QueenOfCards::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->TakeGil(ArmyKnight->Army[ArmyKnight->quanlity - 1]->getgil() * 2);
}
void QueenOfCards::Lose_effect(BaseKnight* knight) {
	if (knight->getType() == PALADIN) return;
	knight->setgil(knight->getgil() / 2);
}
void NinaDeRings::Win_effect(ArmyKnights* ArmyKnight) {
	if (ArmyKnight->lastKnight()->gethp() < ArmyKnight->lastKnight()->getmaxhp() / 3)
	{
		ArmyKnight->lastKnight()->setgil(ArmyKnight->lastKnight()->getgil() - 50);
		ArmyKnight->lastKnight()->sethp(ArmyKnight->lastKnight()->gethp() + ArmyKnight->lastKnight()->getmaxhp() / 5);
	}
}
void NinaDeRings::Lose_effect(BaseKnight* knight) {
	return;
}

void OmegaWeapon::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->defeatOmega = 1;
	ArmyKnight->lastKnight()->setlevel(10);
	ArmyKnight->lastKnight()->setgil(999);
}
void OmegaWeapon::Lose_effect(BaseKnight* knight) {
	knight->sethp(0);
}
void Hades::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->PaladinShield = 1;
	ArmyKnight->defeatHades = 1;
}
void Hades::Lose_effect(BaseKnight* knight) {
	knight->sethp(0);
}
void DurianGarden::Win_effect(ArmyKnights* ArmyKnight) {
	ArmyKnight->lastKnight()->sethp(ArmyKnight->lastKnight()->getmaxhp());
}
void DurianGarden::Lose_effect(BaseKnight* knight) {
	return;
}
/* * * BEGIN implementation of class BaseKnight * * */
string BaseKnight::toString() const
{
	string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
	// inefficient version, students can change these code
	//      but the format output must be the same
	string s("");
	s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
	return s;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
	BaseKnight* temp;
	if (isPrime(maxhp))
	{
		temp = new PaladinKnight(phoenixdownI, antidote);
	}
	else if (maxhp == 888)
	{
		temp = new LancelotKnight(phoenixdownI, antidote);
	}
	else if (maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543)
	{
		temp = new DragonKnight(phoenixdownI, antidote);
	}
	else
	{
		temp = new NormalKnight(phoenixdownI, antidote);
	}
	temp->maxhp = maxhp;
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
			return true;
			break;
		}
		else {
			return false;
			break;
		}

	case 7:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 8:
		if (this->getgil() < 50) {
			return false;
			break;
		}
		else if (this->gethp() < this->getmaxhp() / 3 && this->getgil() >= 50) {
			return true;
			break;
		}
	case 9:
		return true;
		break;
	case 10:
		if ((this->getlevel() == 10 && this->gethp() == this->getmaxhp())) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 11:
		if (this->getlevel() == 10) {

			return true;
			break;
		}
		else {
			return false;
			break;
		}
	}
}
float BaseKnight::damage() {
	return hp * level * base_dmg;
}
BaseKnight::~BaseKnight() {
	delete[] bag;
}
LancelotKnight::LancelotKnight(int phoenixI, int  antidote)
{
	this->knightType = LANCELOT;
	this->base_dmg = 0.05;
	bag = new LancelotBag(this, phoenixI, antidote);
}
bool LancelotKnight::knight_fight(BaseOpponent* opponent) {
	switch (opponent->Otype)
	{
	case 1:
		return true;
		break;
	case 2:
		return true;
		break;
	case 3:
		return true;
		break;
	case 4:
		return true;
		break;
	case 5:
		return true;
		break;
	case 6:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}

	case 7:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 8:
		if (this->getgil() < 50) {
			return false;
			break;
		}
		else if (this->gethp() < this->getmaxhp() / 3 && this->getgil() >= 50) {
			return true;
			break;
		}
	case 9:
		return true;
		break;
	case 10:
		if ((this->getlevel() == 10 && this->gethp() == this->getmaxhp())) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 11:
		if (this->getlevel() == 10) {

			return true;
			break;
		}
		else {
			return false;
			break;
		}
	}
}
DragonKnight::DragonKnight(int phoenixI, int  antidote)
{
	this->base_dmg = 0.075;
	this->knightType = DRAGON;
	bag = new DragonBag(this, phoenixI, antidote);
}
bool DragonKnight::knight_fight(BaseOpponent* opponent) {
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
			return true;
			break;
		}
		else {
			return false;
			break;
		}

	case 7:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 8:
		if (this->getgil() < 50) {
			return false;
			break;
		}
		else if (this->gethp() < this->getmaxhp() / 3 && this->getgil() >= 50) {
			return true;
			break;
		}
	case 9:
		return true;
		break;
	case 10:
		return true;
		break;
	case 11:
		if (this->getlevel() == 10) {

			return true;
			break;
		}
		else {
			return false;
			break;
		}
	}
}
PaladinKnight::PaladinKnight(int phoenixI, int  antidote)
{
	this->base_dmg = 0.06;
	this->knightType = PALADIN;
	bag = new PaladinBag(this, phoenixI, antidote);
}
bool PaladinKnight::knight_fight(BaseOpponent* opponent) {
	switch (opponent->Otype)
	{
	case 1:
		return true;
		break;
	case 2:
		return true;
		break;
	case 3:
		return true;
		break;
	case 4:
		return true;
		break;
	case 5:
		return true;
		break;
	case 6:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}

	case 7:
		if (this->getlevel() >= opponent->levelO) {
			return true;
			break;
		}
		else {
			return false;
			break;
		}
	case 8:
		if (this->gethp() < this->getmaxhp() / 3) {
			this->setgil(this->getgil() + 50);
			return true;
			break;
		}
	case 9:
		return true;
		break;
	case 10:
		return true;
		break;
	case 11:
		if (this->getlevel() > 8) {

			return true;
			break;
		}
		else {
			return false;
			break;
		}
	}
}
NormalKnight::NormalKnight(int phoenixI, int  antidote)
{
	this->knightType = NORMAL;
	bag = new NormalBag(this, phoenixI, antidote);
}



/* * * END implementation of class BaseKnight * * */
/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const
{
	cout << "No. knights: " << this->count();
	if (this->count() > 0)
	{
		BaseKnight* lknight = lastKnight(); // last knight
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
	if (quanlity == 0)
		return NULL;
	return Army[quanlity - 1];
}
bool ArmyKnights::fight(BaseOpponent* opponent) {

	while (quanlity > 0)
	{
		BaseKnight* cur = this->lastKnight();
		if (opponent->Otype >= 1 && opponent->Otype <= 11) {
			if (cur->knight_fight(opponent) == 1) {
				opponent->Win_effect(this);
				this->UseItem(cur);
				return 1;
			}
			else {
				opponent->Lose_effect(cur);
				this->UseItem(cur);
				if (cur->gethp() <= 0) {
					if (Reborn(cur) == false)
					{
						quanlity--;
					}
					return 1;
				}
				return 1;
			}
		}
	}
	return 0;
}
void ArmyKnights::UseItem(BaseKnight* knight) {
	Node* p = knight->BaseKnight::getBag()->BaseBag::getBag();
	while (p != NULL) {
		if (p->item->canUse(knight)) {
			BaseItem* temp = knight->getBag()->get(p->item->type);
			delete temp;
			break;
		}
		p = p->pNext;
	}
}
bool ArmyKnights::Reborn(BaseKnight* knight) {
	UseItem(knight);
	if (knight->gethp() > 0) return true;
	if (knight->gethp() <= 0) {
		if (knight->getgil() >= 100) {
			knight->sethp(knight->getmaxhp() / 2);
			knight->setgil(knight->getgil() - 100);
			return true;
		}
		else return false;
	}
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
bool ArmyKnights::adventure(Events* events) {
	for (int i = 0; i < events->count(); i++) {
		if (events->get(i) <= 11)
		{
			BaseOpponent* temp = NULL;
			switch (events->get(i))
			{
			case 1:
				temp = new MadBear;
				temp->setlevelO(i);
				break;
			case 2:
				temp = new Bandit;
				temp->setlevelO(i);
				break;
			case 3:
				temp = new LordLupin;
				temp->setlevelO(i);
				break;
			case 4:
				temp = new Elf;
				temp->setlevelO(i);
				break;
			case 5:
				temp = new Troll;
				temp->setlevelO(i);
				break;
			case 6:
				temp = new Tornbery;
				temp->setlevelO(i);
				break;
			case 7:
				temp = new QueenOfCards;
				temp->setlevelO(i);
				break;
			case 8:
				temp = new NinaDeRings;
				break;
			case 9:
				temp = new DurianGarden;
				break;
			case 10:
				temp = new OmegaWeapon;
				break;
			case 11:
				temp = new Hades;
				break;
			}
			fight(temp);
		}
		else {
			switch (events->get(i))
			{
				case 112:
				{

					BaseItem* temp = new phoenixdownII;
					if (temp->canUse(lastKnight()))
						temp->use(lastKnight());
					else
						TakeItem(temp);
					break;
				}
				case 113:
				{
					BaseItem* temp = new phoenixdownIII;
					if (temp->canUse(lastKnight()))
						temp->use(lastKnight());
					else
						TakeItem(temp);
					break;
				}
				case 114:
				{
					BaseItem* temp = new phoenixdownIV;
					if (temp->canUse(lastKnight()))
						temp->use(lastKnight());
					else
						TakeItem(temp);
					break;
				}
				case 95:
					PaladinShield = 1;
					break;
				case 96:
					LancelotSpear = 1;
					break;
				case 97:
					GuinevereHair = 1;
					break;
				case 98: {
					if (hasGuinevereHair() == 1 && hasPaladinShield() == 1 && hasLancelotSpear() == 1)
						ExcaliburSword = 1;
					break;
				}
				case 99:
				{
					if (hasExcaliburSword()) {
						printInfo();
						return 1;
					}
					else if (hasGuinevereHair() == 1 && hasPaladinShield() == 1 && hasLancelotSpear() == 1) {
						Ultimecia* boss = new Ultimecia;
						bool result  = boss->fight(this);
						printInfo();
						return result;
					}
					else
					{
						Setquanlity(0);
						printInfo();
						return 0;
					}
				}
			}
		}
		printInfo();
	}
}
void ArmyKnights::TakeItem(BaseItem* temp) {
	for (int i = quanlity; i > 0; i--) {
		if (Army[i - 1]->getBag()->insertFirst(temp))
			break;
	}
}
ArmyKnights::ArmyKnights(const string& file_armyknights)
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
	Army = new BaseKnight * [quanlity];
	int id, maxhp, level, gil, antidote, phoenixdownI;
	for (id = 1; id <= quanlity; id++)
	{
		input >> maxhp >> level >> phoenixdownI >> gil >> antidote;
		BaseKnight* temp = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
		*(Army + id - 1) = temp;
	}
}
ArmyKnights::~ArmyKnights() {
	delete[] Army;
}
/* * * END implementation of class ArmyKnights * * */

KnightAdventure::KnightAdventure()
{
	armyKnights = nullptr;
	events = nullptr;
}

/* * * BEGIN implementation of class KnightAdventure * * */\
void KnightAdventure::loadArmyKnights(const string& inputarmy) {
	armyKnights = new ArmyKnights(inputarmy);
}
void KnightAdventure::loadEvents(const string& inputevent) {
	events = new Events(inputevent);
}
void KnightAdventure::run() {
	armyKnights->printResult(armyKnights->adventure(events));
}
KnightAdventure::~KnightAdventure() {
	delete events;
	delete armyKnights;
}
/* * * END implementation of class KnightAdventure * * */


/* * * BEGIN implementation of class Ultimecia * * */
Ultimecia::Ultimecia() {
	this->hp = 5000;
}
bool Ultimecia::fight(ArmyKnights* ArmyKnight) {
	int quanlity = ArmyKnight->quanlity;
	if (quanlity == 0)
		return 0;
	for (int i = quanlity; i > 0; i--) {
		BaseKnight* knight = ArmyKnight->Army[i - 1];
		if (knight->getType() < 3) {
			this->hp -= knight->damage();
		}
		if (hp <= 0) {
			return 1;
		}
		ArmyKnight->Setquanlity(ArmyKnight->Getquanlity() - 1);
	}

	return 0;
}

/* * * END implementation of class Ultimecia * * */



Events::~Events() {
	delete[] arr;
}
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