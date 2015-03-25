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

	void attack(Animal* target);
protected:
	CCAnimation* ani_stand;
	CCAnimation* ani_run;
	CCAnimation* ani_attack;
	CCAnimation* ani_skill;
	CCAnimation* attack_effect;
	CCAnimation* skill_effect;
	CCArray* attacks;

	CCNode* attEffNode;
	CCNode* skillEffNode;
	 
};

