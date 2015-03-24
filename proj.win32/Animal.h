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
	void walkTo(CCPoint pos);
	void idle();
	void attack(Animal* target,int hurt);
protected:
	CCAnimation* getAnimationByName(const char* pzName,int num = 8);
	void playAnimation(CCAnimation* animation);
	void correctPos(float &x,float &y);
private:
	int m_roleId;
	int speed;
	float width;
	float height;
	AnimalStatus m_status;
	//CCAnimation* m_animationNow;
	CCAnimation* ani_walk;
	CCAnimation* ani_hurt;
	CCAnimation* ani_die;


};

