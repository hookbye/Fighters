#include "GameScene.h"

GameScene::GameScene(void):map(NULL),player(NULL)
{
	enemies = CCArray::create();
	enemies->retain();
}

GameScene::~GameScene(void)
{
	CC_SAFE_RELEASE(enemies);
	/*for( int i=0;i<4;i++) {
        cpShapeFree( m_pWalls[i] );
    }

    cpSpaceFree( m_pSpace );*/
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
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(GameScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
		origin.y+ visibleSize.height - pCloseItem->getContentSize().height));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    //CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    //
    //// position the label on the center of the screen
    //pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
    //                        origin.y + visibleSize.height - pLabel->getContentSize().height));
    //this->addChild(pLabel, 1);
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //this->addChild(pSprite, 0);

	loadMap(40001);
	//initPhysics();
    player = Player::create(20002);
	
	player->retain();
	addChild(player);
	initEnemies();
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
}
void GameScene::initEnemies()
{
	
	int enemiesar[] = {10001,10002,10003,10004,10005,10006};
	for (int i=0;i<sizeof(enemiesar)/sizeof(int);i++)
	{
		Enemy* ani = Enemy::create(enemiesar[i]);
		ani->setPosition(ccp(100*(i+1),200));
		addChild(ani);
		enemies->addObject(ani);
	}
	
}
CCArray* GameScene::getEnemies()
{
	CCArray* result = CCArray::create();
	int count = enemies->count();
	Animal* ani;
	for(int i=0;i<count;i++)
	{
		ani = (Animal*)enemies->objectAtIndex(i);
		if(player->canAttack(ani))
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
	Animal* ani = NULL;
	if(enemyAr->count()>0)
	{
		for(int i=0;i<enemyAr->count();i++)
		{
			ani = (Animal*)enemyAr->objectAtIndex(i);
			player->attack(ani,skillid);
		}
	}
	else
	{
		player->attack(ani,skillid);
	}
	
}
void GameScene::update(float dt)
{
	joyPad->update(dt);
	player->update(dt);

	//物理引擎刷新
	/*int steps = 2;
    float pdt = CCDirector::sharedDirector()->getAnimationInterval()/(float)steps;

    for(int i=0; i<steps; i++){
        cpSpaceStep(m_pSpace, pdt);
    }*/
}

//void GameScene::initPhysics()
//{
//	#if CC_ENABLE_CHIPMUNK_INTEGRATION    
//    // init chipmunk
//    //cpInitChipmunk();
//
//    m_pSpace = cpSpaceNew();
//
//    m_pSpace->gravity = cpv(0, 0);
//
//    //
//    // rogue shapes
//    // We have to free them manually
//    //
//    // bottom
//	CCRect mapRect = CCRect(map->getPositionX(),map->getPositionY(),
//		map->getContentSize().width,map->getContentSize().height);
//    m_pWalls[0] = cpSegmentShapeNew( m_pSpace->staticBody,
//		cpv(mapRect.origin.x,mapRect.origin.y),
//		cpv(mapRect.origin.x+mapRect.size.width, mapRect.origin.y), 0.0f);
//
//    // top
//    m_pWalls[1] = cpSegmentShapeNew( m_pSpace->staticBody, 
//		cpv(mapRect.origin.x, mapRect.origin.y+mapRect.size.height),
//        cpv(mapRect.origin.x+mapRect.size.width, mapRect.origin.y+mapRect.size.height), 0.0f);
//
//    // left
//    m_pWalls[2] = cpSegmentShapeNew( m_pSpace->staticBody,
//        cpv(mapRect.origin.x,mapRect.origin.y),
//        cpv(mapRect.origin.x,mapRect.origin.y+mapRect.size.height), 0.0f);
//
//    // right
//    m_pWalls[3] = cpSegmentShapeNew( m_pSpace->staticBody, 
//        cpv(mapRect.origin.x+mapRect.size.width, mapRect.origin.y+mapRect.size.height),
//        cpv(mapRect.origin.x+mapRect.size.width, mapRect.origin.y+mapRect.size.height), 0.0f);
//
//    for( int i=0;i<4;i++) {
//        m_pWalls[i]->e = 1.0f;
//        m_pWalls[i]->u = 1.0f;
//        cpSpaceAddStaticShape(m_pSpace, m_pWalls[i] );
//    }
//
//    // Physics debug layer
//    m_pDebugLayer = CCPhysicsDebugNode::create(m_pSpace);
//    this->addChild(m_pDebugLayer, 100);
//#endif
//}
//void GameScene::addAnimal(Animal* animal)
//{
//	CCPoint pos = ccp(100,100);
//	int width = animal->getBodySize().width,height = animal->getBodySize().height;
//	int num = 4;
//    cpVect verts[] = {
//        cpv(-width/2,-height/2),
//        cpv(-width/2, height/2),
//        cpv( width/2, height/2),
//        cpv( width/2,-height/2),
//    };
//
//    cpBody *body = cpBodyNew(1.0f, cpMomentForPoly(1.0f, num, verts, cpvzero));
//
//    body->p = cpv(pos.x, pos.y);
//    cpSpaceAddBody(m_pSpace, body);
//
//    cpShape* shape = cpPolyShapeNew(body, num, verts, cpvzero);
//    shape->e = 0.5f; shape->u = 0.5f;
//    cpSpaceAddShape(m_pSpace, shape);
//
//	addChild(animal);
//
//    animal->setCPBody(body);
//    animal->setPosition(pos);
//}
void GameScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
	initEnemies();
    //CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
