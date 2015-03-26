#include "GameScene.h"

GameScene::GameScene(void):map(NULL),player(NULL)
{
	enemies = CCArray::create();
	enemies->retain();
}

GameScene::~GameScene(void)
{
	CC_SAFE_RELEASE(enemies);
}

CCScene* GameScene::scene()
{
    CCScene *scene = CCScene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
 //   CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
 //                                       "CloseNormal.png",
 //                                       "CloseSelected.png",
 //                                       this,
 //                                       menu_selector(GameScene::menuCloseCallback));
 //   
	//pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
 //                               origin.y + pCloseItem->getContentSize().height/2));

 //   // create menu, it's an autorelease object
 //   CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
 //   pMenu->setPosition(CCPointZero);
 //   this->addChild(pMenu, 1);
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));
    this->addChild(pLabel, 1);
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(pSprite, 0);
	loadMap(40001);
    player = Player::create(20001);
	player->retain();
	addChild(player);

	joyPad = JoyPad::create();
	joyPad->setGameLayer(this);
	addChild(joyPad);

	this->scheduleUpdate();
    return true;
}

void GameScene::loadMap(int mapId)
{
	map = Map::create(40001);
	map->retain();
	addChild(map);
	initEnemies();
}
void GameScene::initEnemies()
{
	Enemy* ani = Enemy::create(10001);
	ani->setPosition(ccp(200,200));
	addChild(ani);
	enemies->addObject(ani);
}
CCArray* GameScene::getEnemies()
{
	CCArray* result = CCArray::create();
	int count = enemies->count();
	Animal* ani;
	for(int i=0;i<count;i++)
	{
		ani = (Animal*)enemies->objectAtIndex(i);
		if(player->boundingBox().intersectsRect(ani->boundingBox()))
			result->addObject(ani);
	}
	return result;
}
void GameScene::move(CCPoint normal,bool isRun)
{
	player->walkTo(normal,isRun);
}
void GameScene::attack(int skillid)
{
	CCArray* enemyAr = getEnemies();
	Animal* ani;
	for(int i=0;i<enemyAr->count();i++)
	{
		ani = (Animal*)enemyAr->objectAtIndex(i);
		player->attack(ani,skillid);
	}
	
}
void GameScene::update(float dt)
{
	joyPad->update(dt);
	player->update(dt);
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
