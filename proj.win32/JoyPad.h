#pragma once
#include "cocos2d.h"
class GameScene;
USING_NS_CC;
class JoyPad :
	public CCLayer
{
public:
	JoyPad(void);
	~JoyPad(void);
	virtual bool init();
	CREATE_FUNC(JoyPad);
	void setGameLayer(GameScene* game){gameLayer = game;}
	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);

	bool initDirController();
	bool initSkillController();
	//void transToDir(CCPoint normalize);
	void move(CCPoint normalize,bool isRun = false);
	void skillButtonCallback(CCObject* pSender);

	void update(float dt);
private:
	GameScene* gameLayer;
	CCSprite* stick;
	CCSprite* stickBg;
	CCPoint stickCenterPos;
	bool btouchDirStick;
	bool isToRun;
	CCPoint moveVec;
};

