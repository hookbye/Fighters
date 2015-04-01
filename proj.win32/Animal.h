#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "config.h"
#include "FSM.h"
#include <iostream>
USING_NS_CC;
USING_NS_CC_EXT;
class Animal :
	public CCNode
{
	///////////////// 实现 物理引擎刚体 /////////
//protected:
//    bool    m_bIgnoreBodyRotation;
//#if CC_ENABLE_CHIPMUNK_INTEGRATION
//    cpBody  *m_pCPBody;
//
//#elif CC_ENABLE_BOX2D_INTEGRATION
//    b2Body  *m_pB2Body;
//
//    // Pixels to Meters ratio
//    float   m_fPTMRatio;
//#endif // CC_ENABLE_CHIPMUNK_INTEGRATION
//public:
//    virtual bool isDirty();
//
//    /** Keep the sprite's rotation separate from the body. */
//    bool isIgnoreBodyRotation() const;
//    void setIgnoreBodyRotation(bool bIgnoreBodyRotation);
//
//    virtual const CCPoint& getPosition();
//    virtual void getPosition(float* x, float* y);
//    virtual float getPositionX();
//    virtual float getPositionY();
//    virtual void setPosition(const CCPoint &position);
//    virtual float getRotation();
//    virtual void setRotation(float fRotation);
//    virtual CCAffineTransform nodeToParentTransform();
//
//#if CC_ENABLE_CHIPMUNK_INTEGRATION
//    /** Body accessor when using regular Chipmunk */
//    cpBody* getCPBody() const;
//    void setCPBody(cpBody *pBody);
//#elif CC_ENABLE_BOX2D_INTEGRATION
//    /** Body accessor when using box2d */
//    b2Body* getB2Body() const;
//    void setB2Body(b2Body *pBody);
//
//    float getPTMRatio() const;
//    void setPTMRatio(float fPTMRatio);
//#endif // CC_ENABLE_BOX2D_INTEGRATION
//
//protected:
//    void updatePosFromPhysics();
// /////////////////// end ///////////////////////////
public:
	Animal(void);
	~Animal(void);
	
	static Animal* create(int roleId);
	virtual bool initAnimalData();
	virtual void initBasicData();
	virtual void setPosition(CCPoint pos);

	virtual void walkTo(CCPoint pos,bool isRun = false);
	virtual void idle();
	virtual void die();
	virtual void run();
	virtual void attack(Animal* target,int skillid = 1);
	virtual void beAttacked(Animal* attacker,int hurt);

	virtual void onWalk();
	virtual void onIdle();
	virtual void onHurt();

	bool canAttack(Animal* target);
	void setHp(float hp);
	void updateHp();
private:
	//void initPhysicsBody();

protected:
	CCAnimation* getAnimationByName(const char* pzName,float defaultTime = 0.1f,int num = 20);
	void playAnimation(CCAnimation* animation,int repeat = 1);
	void animationCallBack();
	void correctPos(float &x,float &y);
	//void setStatus(AnimalStatus st);
	std::string getStatus(){return fsm->getState();};
	
	virtual void initFSM();
	CC_SYNTHESIZE(CCSize, bodySize,BodySize);
	CC_SYNTHESIZE(CCRect, bodyRect,BodyRect);
	CC_SYNTHESIZE(CCRect, attackRect,AttackRect);
	CC_SYNTHESIZE(float, attackDis,AttackDis);
protected:
	
protected:
	int m_roleId;
	int speed;
	int walkspeed;
	int runspeed;
	float blood;
	float hp;
	int attackNum;

	float width;
	float height;
	CCAnimation* m_animationNow;
	CCAnimation* ani_walk;
	CCAnimation* ani_hurt;
	

	FSM* fsm;
protected:
	CCSprite* body;
	CCLabelTTF* hurmLabel;
	CCProgressTimer* hpBar;
	CCProgressTimer* mpBar;
	 
};
class AnimalNode
	:public CCNode
{

};
