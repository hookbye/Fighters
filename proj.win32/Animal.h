#pragma once
#include "cocos2d.h"
#include "config.h"
#include "FSM.h"
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
	virtual void walkTo(CCPoint pos,bool isRun = false);
	virtual void idle();
	virtual void die();
	virtual void run();
	virtual void attack(Animal* target,int skillid = 1);
	virtual void beAttacked(Animal* attacker,int hurt);

	virtual void onWalk();
	virtual void onIdle();
	virtual void onHurt();
	 
protected:
	CCAnimation* getAnimationByName(const char* pzName,float defaultTime = 0.1f,int num = 20);
	void playAnimation(CCAnimation* animation,int repeat = 1);
	void animationCallBack();
	void correctPos(float &x,float &y);
	//void setStatus(AnimalStatus st);
	std::string getStatus(){return fsm->getState();};

	virtual void initFSM();
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
	
	FSM* fsm;
private:
	
};

