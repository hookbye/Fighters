#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene :
	public CCLayer
{
public:
	GameScene(void);
	~GameScene(void);
	virtual bool init();  
	static cocos2d::CCScene* scene();
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
};

