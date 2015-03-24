#pragma once
#include "animal.h"
class Player :
	public Animal
{
public:
	Player(void);
	~Player(void);
	static Player* create(int roleId);
	virtual bool initAnimalData();
private:

};

