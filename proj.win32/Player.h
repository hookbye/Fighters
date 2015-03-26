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

	void attack(Animal* target,int skillid = 1);
	void run();
	void initFSM();

	virtual void onAttack();
	virtual void onRun();
	virtual void onSkill();
	virtual void onHurt();
	virtual void onStand();

	void update(float dt);
private:
	float attackInterval;
	int attackIndex;
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

