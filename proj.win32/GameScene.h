#pragma once
#include "chipmunk.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Animal.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "JoyPad.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GameScene :
	public CCLayer
{
public:
	GameScene(void);
	~GameScene(void);
	virtual bool init();  
	static cocos2d::CCScene* scene();
	void loadMap(int mapId);
	void initEnemies();

	void move(CCPoint normal,bool isRun = false);
	void attack(int skillid);
	CCArray* getEnemies();

	void update(float dt);
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
private:
//	void initPhysics();
//	void addAnimal(Animal* animal);
//    CCTexture2D* m_pSpriteTexture; // weak ref
//#if CC_ENABLE_CHIPMUNK_INTEGRATION    
//    CCPhysicsDebugNode* m_pDebugLayer; // weak ref
//#endif
//    cpSpace* m_pSpace; // strong ref
//    cpShape* m_pWalls[4];
private:
	Map* map;
	Player* player;
	JoyPad* joyPad;

	CCArray* enemies;
};

