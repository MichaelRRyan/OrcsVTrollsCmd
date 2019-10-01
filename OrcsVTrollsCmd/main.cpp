/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 01/10/2019
/// @Time 12:32
/// </summary>

#include <iostream>

using namespace std;

class Character {
public:
	void flip() { cout << "I know how to flip and I will flipping do it" << endl; }
	virtual void walk() { cout << "just in case they are too young to walk yet" << endl; }
	virtual void fly() = 0; //pure virtual function
};

class Orc : public Character {
public:
	void barrelRoll() { cout << "rooooooolllllllllllinggggggg" << endl; }
	void walk() { cout << "Doopers have a really cool walk!" << endl; }
	void fly() { cout << "Dooper is flapping and flying" << endl; }
};

class Troll : public Character {
public:
	void fly() { cout << "Average Dooper is flapping and flying" << endl; }
};

int main()
{
	cout << "Let go virtual" << endl;
	/*Character character;
	character.flip();
	character.walk();*/

	cout << "Let go create an Orc" << endl;
	Orc orc;
	orc.walk();
	orc.fly();
	orc.flip();

	cout << "Let go create an Troll" << endl;
	Troll troll;
	troll.walk();
	troll.fly();
	troll.flip();

	Character* npc = &orc;
	npc->flip();
	npc->fly();
	npc->walk();

	npc = &troll;
	npc->flip();
	npc->fly();
	npc->walk();

	cin.get();

	return EXIT_SUCCESS;
}