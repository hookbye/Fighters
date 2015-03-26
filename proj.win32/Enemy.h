#pragma once
#include "animal.h"
class Enemy :
	public Animal
{
public:
	Enemy(void);
	~Enemy(void);
	static Enemy* create(int roleId);
	virtual bool initAnimalData();

	void attack(Animal* target);
	void beAttacked(Animal* attacker,int hurt);
	void die();
	void initFSM();
protected:
	CCAnimation* ani_die;
	/*CCAnimation* ani_run;
	CCAnimation* ani_attack;
	CCAnimation* ani_skill;
	CCAnimation* attack_effect;
	CCAnimation* skill_effect;
	CCArray* attacks;

	CCNode* attEffNode;
	CCNode* skillEffNode;*/
};

