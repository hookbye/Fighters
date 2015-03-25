#pragma once
#include "cocos2d.h"
#include "config.h"
#include <iostream>
USING_NS_CC;
class Animal :
	public CCSprite
{
public:
	Animal(void);
	~Animal(void);
	
	static Animal* create(int roleId);
	virtual bool initAnimalData();
	virtual void walkTo(CCPoint pos);
	virtual void idle();
	virtual void die();
	virtual void attack(Animal* target);
	virtual void beAttacked(Animal* attacker,int hurt);
protected:
	CCAnimation* getAnimationByName(const char* pzName,int num = 8,float defaultTime = 0.2);
	void playAnimation(CCAnimation* animation,int repeat = 1);
	void correctPos(float &x,float &y);
	void setStatus(AnimalStatus st);
	AnimalStatus getStatus(){return m_status;};
protected:
	int m_roleId;
	int speed;
	int blood;
	int attackNum;

	float width;
	float height;
	AnimalStatus m_status;
	//CCAnimation* m_animationNow;
	CCAnimation* ani_walk;
	CCAnimation* ani_hurt;
	
private:
};

