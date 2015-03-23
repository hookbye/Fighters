#pragma once
#include "cocos2d.h"
#include <iostream>
USING_NS_CC;
class Animal :
	public CCSprite
{
public:
	Animal(void);
	~Animal(void);
	enum AnimalStatus
	{
		IDLE,
		WALK,
		ATTACK,
		DIE,
	};
	static Animal* create(int roleId);
	virtual bool initAnimalData();
protected:
	void walkTo(CCPoint pos);
	void idle();
	void attack(Animal* target,int hurt);
	CCAnimation* getAnimationByName(const char* pzName,int num = 8);
private:
	int m_roleId;
	AnimalStatus m_status;
	//CCAnimation* m_animationNow;
	CCAnimation* walk;
	CCAnimation* hurt;
	CCAnimation* die;

};

