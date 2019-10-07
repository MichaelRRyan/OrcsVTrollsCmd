#ifndef ORC_H
#define ORC_H

/// <summary>
/// @Author Michael Rainsford Ryan
/// @Date 07/10/2019
/// </summary>

#include "Character.h"

class Orc : public Character
{
public:
	Orc();
	void barrelRoll() { std::cout << "rooooooolllllllllllinggggggg" << std::endl; }
	void walk() { std::cout << "Doopers have a really cool walk!" << std::endl; }
	void fly() { std::cout << "Dooper is flapping and flying" << std::endl; }
};

#endif // !ORC_H