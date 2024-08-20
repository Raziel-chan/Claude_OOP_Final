// Claude_OOP_multiInheritance_RuleOfFive.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
Exercise 1: std::unique_ptr
Rewrite your Wizard class to use a std::unique_ptr for storing a dynamic resource. For example, you could add a spell book to your Wizard:
*/

#include <iostream>
//access to smart pointer
#include <memory> 
using namespace std;

class Player {
private:
	string name;
public:
	virtual string castingMagic() {
		return "casting some sort of Magic!";
	};

	Player() : name("No Name") {
	}

	Player(string playerName) : name(playerName) {
	}

	void setPlayerName(string playerName) {
		name = playerName;
	}

	string getPlayerName() const {
		return name;
	}
};

class MagicType : virtual public Player {
private:
	string type = "";
public:
	//default constructor
	MagicType(string type) {
		this->type = type;
	}

	void setMagicType(string type) {
		this->type = type;
	}

	string getMagicType() const {
		return type;
	}
};

class TypeOfMana : virtual public Player {
private:
	string mana = "";
public:
	//default constructor
	TypeOfMana(string mana) {
		this->mana = mana;
	}

	void setManaType(string mana) {
		this->mana = mana;
	}

	string getManaType() const {
		return mana;
	}
};

//really basic class to store the spell
class SpellBook
{
private:
string spell = "";
public:
	//default constructor
	SpellBook(string spell) {
		this->spell = spell;
	}

	void setSpell(string spell) {
		this->spell = spell;
	}

	string getSpell() const {
		return spell;
	}
};

class Wizard : public MagicType, public TypeOfMana {
private:
	//unique pointer to spell book to store dynamic resource
	unique_ptr<SpellBook> spellBook = nullptr;
public:
	//default constructor
	Wizard() : Player("No Name"), MagicType("No Magic"), TypeOfMana("No Mana"){}
	//constructor
	Wizard(string name, string typeOfMagic, string typeOfMana) : Player(name), MagicType(typeOfMagic), TypeOfMana(typeOfMana){}
	//copy constructor
	Wizard(Wizard& newWizard) : Player(newWizard.getPlayerName()), MagicType(newWizard.getMagicType()), TypeOfMana(newWizard.getManaType()) {}
	//copy assignment operator
	Wizard& operator=(Wizard& newWizard) {
		if (this != &newWizard) {
			this->setPlayerName(newWizard.getPlayerName());
			this->setMagicType(newWizard.getMagicType());
			this->setManaType(newWizard.getManaType());
		}
		return *this;
	}
	//move constructor
	Wizard(Wizard&& newWizard) noexcept : Player(newWizard.getPlayerName()), MagicType(newWizard.getMagicType()), TypeOfMana(newWizard.getManaType()) {
	}
	//move assignment operator
	Wizard& operator=(Wizard&& newWizard) noexcept {
		if (this != &newWizard) {
			this->setPlayerName(newWizard.getPlayerName());
			this->setMagicType(newWizard.getMagicType());
			this->setManaType(newWizard.getManaType());
		}
		return *this;
	}
	//since my variable is private, I need to create a setter and getter for spell book
	//and since I am using unique pointer, I need to use move semantics and get reference to the unique pointer
	void setSpellBook(unique_ptr<SpellBook> &spellBook) {
		this->spellBook = move(spellBook);
	}

	//we use this to get the spell book and check if the unique pointer spell book is not null
	string getSpellBook() const {
		return (spellBook != nullptr) ? spellBook->getSpell() : "this wizard does not have a spell book";
	}
};

void displayPlayerInfo(const Wizard &wizard) {
	cout << "Name: " << wizard.getPlayerName() << endl;
	cout << "Type of Magic: " << wizard.getMagicType() << endl;
	cout << "Type of Mana: " << wizard.getManaType() << endl;
	cout << "Spell Book: " << wizard.getSpellBook() << endl << endl;
}

int main()
{
	//unique pointer to store dynamic resource which use SpellBook constructor
	unique_ptr<SpellBook> spellBook(new SpellBook("Fireball"));
    Wizard wizard("Merlin", "Fire", "Red");
	//we set the value of the spell book to the wizard
	wizard.setSpellBook(spellBook);
	displayPlayerInfo(wizard);
	cout << wizard.getPlayerName() << " is " << wizard.castingMagic() << endl;

	Wizard wizard2;
	wizard2 = wizard;
	displayPlayerInfo(wizard2);

	return 0;
}