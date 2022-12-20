// RPGcharectercreator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <random>

using namespace std;

class Player
{
private:
	string m_name;
	string m_ancestry;
	string m_class;
public:
	int strength = 0;
	int dexterity = 0;
	int constitution = 0;
	int wisdom = 0;
	int intelligence = 0;
	int charisma = 0;
	string getName();
	void setname(string name);
	string getAncestry();
	void setAncestry(string Ancestry);
	string getClass();
	void setClass(string Class);
};

string Player::getName()
{
	return m_name; 
}

void Player::setname(string name) {
	m_name = name;
}

string Player::getAncestry()
{
	return m_ancestry;
}

void Player::setAncestry(string Ancestry)
{
	m_ancestry = Ancestry;
}

string Player::getClass()
{
	return m_class;
}

void Player::setClass(string Class)
{
	m_class = Class;
}

int askNumber(string question, int high, int low);

int main()
{
	int ancestryChoose;
	int classChoose;
	int redoChoose;

	do
	{
		srand(static_cast<unsigned int> (time(0)));
		Player player;
		std::cout << "RPGcharactercreater\n\n";
		std::cout << "please enter a name: ";
		string name;
		std::cin >> name;
		player.setname(name);
		std::cout << "\n\nok," << player.getName() << ". tell me about youself.\n\n";
		std::cout << "what is your ancestry?\n";
		std::cout << "[1] Human\n";
		std::cout << "[2] Elf\n";
		std::cout << "[3] Half-elf\n";
		std::cout << "[4] Dwarf\n";
		std::cout << "[5] Halfling\n";
		ancestryChoose = askNumber("", 5, 1);
		switch (ancestryChoose)
		{
		case 1:
			//humen
			player.setAncestry("Human");
			player.strength += 1;
			player.constitution += 1;
			player.dexterity += 1;
			player.intelligence += 1;
			player.wisdom += 1;
			player.charisma += 1;
			break;
		case 2:
			player.setAncestry("Elf");
			player.dexterity += 2;
			player.wisdom += 2;
			break;
		case 3:
			player.setAncestry("Half-elf");
			player.dexterity += 1;
			player.wisdom += 1;
			player.charisma += 2;
			break;
		case 4:
			player.setAncestry("Dwarf");
			player.constitution += 2;
			player.strength += 2;
			break;
		case 5:
			player.setAncestry("Halfling");
			player.charisma += 2;
			player.dexterity += 2;
			break;
		default:
			std::cout << "\n\nError\n";
			break;
		}

		std::cout << "\nWhat is your class?\n";
		std::cout << "[1] Fighter\n";
		std::cout << "[2] Rogue\n";
		std::cout << "[3] Wizard\n";
		std::cout << "[4] Druid\n";
		std::cout << "[5] Paladin\n";

		classChoose = askNumber("", 5, 1);

		switch (ancestryChoose)
		{
		case 1:
			player.setClass("Fighter");
			player.strength += 18;
			player.constitution += (rand() % 18 + 6);
			player.dexterity += (rand() % 18 + 6);
			player.intelligence += (rand() % 18 + 6);
			player.wisdom += (rand() % 18 + 6);
			player.charisma += (rand() % 18 + 6);
			break;
		case 2:
			player.setClass("Rogue");
			player.strength += (rand() % 18 + 6);
			player.constitution += (rand() % 18 + 6);
			player.dexterity += 18;
			player.intelligence += (rand() % 18 + 6);
			player.wisdom += (rand() % 18 + 6);
			player.charisma += (rand() % 18 + 6);
			break;
		case 3:
			player.setClass("Wizard");
			player.strength += (rand() % 18 + 6);
			player.constitution += (rand() % 18 + 6);
			player.dexterity += (rand() % 18 + 6);
			player.intelligence += 18;
			player.wisdom += (rand() % 18 + 6);
			player.charisma += (rand() % 18 + 6);
			break;
		case 4:
			player.setClass("Druid");
			player.strength += (rand() % 18 + 6);
			player.constitution += (rand() % 18 + 6);
			player.dexterity += (rand() % 18 + 6);
			player.intelligence += (rand() % 18 + 6);
			player.wisdom += 18;
			player.charisma += (rand() % 18 + 6);
			break;
		case 5:
			player.setClass("Paladin");
			player.strength += (rand() % 18 + 6);
			player.constitution += (rand() % 18 + 6);
			player.dexterity += (rand() % 18 + 6);
			player.intelligence += (rand() % 18 + 6);
			player.wisdom += (rand() % 18 + 6);
			player.charisma += 18;
			break;
		default:
			std::cout << "Error";
			break;
		}

		std::cout << "\n\nYou are named " << player.getName() << ".";
		std::cout << "\nYou are a " << player.getAncestry() << " " << player.getClass();
		std::cout << "\nThese are your stats:";
		std::cout << "\nSTR: " << player.strength << "\nDEX: " << player.dexterity << "\nCON: " << player.constitution << "\nINT" << player.intelligence << "\nWIS" << player.wisdom << "\nCHA" << player.charisma;

		std::cout << "\n\nWould you like to redo or are you good with this character?\n";
		std::cout << "\n(1) Redo";
		std::cout << "\n(2) Confirm character\n";
		redoChoose = askNumber("", 2, 1);
	} while (redoChoose != 2);
	return 0;
}

int askNumber(string question, int high, int low)
{
	int number;
	do
	{
		cout << question << "\n(" << low << "-" << high << "): ";
		cin >> number;
		if (number > high || number < low)
		{
			cout << "Pick a valid option.\n";
		}
	} while (number > high || number < low);
	return number;
}