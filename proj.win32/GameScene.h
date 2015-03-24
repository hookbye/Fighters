#pragma once
#include "cocos2d.h"
#include "Animal.h"
#include "Map.h"
#include "JoyPad.h"

USING_NS_CC;
class GameScene :
	public CCLayer
{
public:
	GameScene(void);
	~GameScene(void);
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void loadMap(int mapId);
	void move(CCPoint normal);
	void update(float dt);
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
private:
	Map* map;
	Animal* player;
	JoyPad* joyPad;
};

