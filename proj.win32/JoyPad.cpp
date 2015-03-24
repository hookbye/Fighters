#include "JoyPad.h"
#include "GameScene.h"

JoyPad::JoyPad(void):gameLayer(NULL),stick(NULL),stickBg(NULL),
	stickCenterPos(CCPointZero),btouchDirStick(false),moveVec(CCPointZero)
{
}


JoyPad::~JoyPad(void)
{
}
bool JoyPad::init()
{
	do{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("joyStickImg.plist","joyStickImg.png");
		CC_BREAK_IF(!CCLayer::init());
		CC_BREAK_IF(!initDirController());
		CC_BREAK_IF(!initSkillController());
		
		setTouchEnabled(true);
		setTouchMode(kCCTouchesOneByOne);
		return true;
	}while(0);
	return false;
}

bool JoyPad::initDirController()
{
	
	do{
		stickCenterPos = ccp(100,100);
		stickBg = CCSprite::createWithSpriteFrameName("joyStick.png");
		//stick->setAnchorPoint(ccp(0,0));
		stickBg->retain();
		stickBg->setPosition(stickCenterPos);
		addChild(stickBg,0);
		stick = CCSprite::createWithSpriteFrameName("joyStickCenter.png");
		//stick->setAnchorPoint(ccp(0,0));
		stick->setPosition(stickCenterPos);
		stick->retain();
		addChild(stick);
		return true;
	}while(0);
	return false;
}
bool JoyPad::initSkillController()
{
	
	do{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCMenuItemSprite* skill1 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("joyStickButton.png"),CCSprite::createWithSpriteFrameName("joyStickButtonHighLight.png"),
			this,menu_selector(JoyPad::skillButtonCallback));
		//skill1->retain();
		skill1->setPosition(ccp(origin.x + visibleSize.width - skill1->getContentSize().width/2 ,
                                origin.y + skill1->getContentSize().height/2));
		CCMenuItemSprite* skill2 = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("joyStickskillButton.png"),
			CCSprite::createWithSpriteFrameName("joyStickskillButtonHighLight.png"),
			CCSprite::createWithSpriteFrameName("joyStickskillButtonGray.png"),
			this,menu_selector(JoyPad::skillButtonCallback));
		//skill1->retain();
		skill2->setPosition(ccp(origin.x + visibleSize.width - skill2->getContentSize().width - 50 -  skill1->getContentSize().width/2,
                                origin.y + skill1->getContentSize().height/2-30));

		CCMenu* menu = CCMenu::create(skill1,skill2,NULL);
		menu->setPosition(ccp(0,0));
		addChild(menu,1);
		
		return true;
	}while(0);
	return false;
}
void JoyPad::skillButtonCallback(CCObject* pSender)
{
}
void JoyPad::onEnter()
{
	CCLayer::onEnter();
}
void JoyPad::onExit()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("joyStickImg.plist");
	CCLayer::onExit();
}
bool JoyPad::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	CCPoint pos = pTouch->getLocation();
	if(stickBg->boundingBox().containsPoint(pos))
	{
		stick->setPosition(pos);
		CCPoint normal = ccpNormalize(ccpAdd(pos,ccp(-stickCenterPos.x,-stickCenterPos.y)));
		moveVec = normal;
		btouchDirStick = true;
	}
	return true;
}
void JoyPad::ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent)
{
	if(btouchDirStick)
	{
		CCPoint pos = pTouch->getLocation();
		CCPoint normal = ccpNormalize(ccpAdd(pos,ccp(-stickCenterPos.x,-stickCenterPos.y)));
		int stickRadius = stickBg->getContentSize().width/2;
		CCPoint targetPos = ccpAdd(stickCenterPos,ccp(stickRadius*normal.x,stickRadius*normal.y));
		int dis = ccpDistance(pos,stickCenterPos);
		if(dis<stickRadius)
		{
			stick->setPosition(pos);
		}else
		{
			stick->setPosition(targetPos);
		}
		moveVec = normal;
	}
}
void JoyPad::ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent)
{
	stick->setPosition(stickCenterPos);
	moveVec = CCPointZero;
	btouchDirStick = false;
}
void JoyPad::move(CCPoint normalize)
{
	gameLayer->move(normalize);
}

void JoyPad::update(float dt)
{
	if(btouchDirStick)
	{
		move(moveVec);
	}
}