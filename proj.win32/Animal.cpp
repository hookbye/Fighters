#include "Animal.h"

const int ATTACK_TAG = 10010;

Animal::Animal(void):body(NULL),speed(0),walkspeed(1),runspeed(2),blood(100),hp(100),attackNum(5),
	ani_walk(NULL),ani_hurt(NULL),hurmLabel(NULL),m_animationNow(NULL),
	hpBar(NULL),mpBar(NULL),
	attackDis(0),attackRect(CCRectZero),bodyRect(CCRectZero),bodySize(CCSizeZero),
	width(0),height(0)
	//,m_bIgnoreBodyRotation(false)
//#if CC_ENABLE_CHIPMUNK_INTEGRATION
//, m_pCPBody(NULL)
//#elif CC_ENABLE_BOX2D_INTEGRATION
//, m_pB2Body(NULL)
//, m_fPTMRatio(0.0f)
//#endif
{
	fsm = FSM::create("idleing");
	fsm->retain();
}


Animal::~Animal(void)
{
	CC_SAFE_RELEASE(fsm);
}

void Animal::initFSM()
{
	fsm->addState("walking",[&](){onWalk();})
		->addState("idleing",[&](){onIdle();})
		->addState("hurting",[&](){onHurt();})
		;
	fsm->addEvent("walk","idleing","walking")
		->addEvent("idle","walking","idleing")
		->addEvent("idle","hurting","idleing")
		->addEvent("hurt","walking","hurting")
		->addEvent("hurt","idleing","hurting")
		;
	

}

Animal* Animal::create(int roleId)
{
	Animal* ani = new Animal();
	
	if (ani && ani->init())
	{
		ani->autorelease();
		ani->m_roleId = roleId;
		ani->initAnimalData();
		ani->initBasicData();
		ani->initFSM();
		return ani;
	}
	CC_SAFE_DELETE(ani);
	return NULL;
}
void Animal::initBasicData()
{
	CCFileUtils::sharedFileUtils()->addSearchPath("fightUI/");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fightUI.plist","fightUI.png");
	
	CCSprite* barSpr = CCSprite::createWithSpriteFrameName("fightUI_greenBar.png");
	hpBar = CCProgressTimer::create(barSpr);
	hpBar->setType(kCCProgressTimerTypeBar);
	hpBar->setPercentage(100);
	hpBar->setMidpoint(ccp(0,0));
	hpBar->setBarChangeRate(ccp(1,0));
	hpBar->setScaleX((blood)/barSpr->getContentSize().width);
	hpBar->setScaleY(0.3);
	hpBar->retain();
	hpBar->setPosition(ccp(getContentSize().width/2,getContentSize().height/2+getBodySize().height/2));
    this->addChild(hpBar, 1);
	//CCLog("888888888888   %f,  %f,%f",getContentSize().width/2,getContentSize().height/2,getContentSize().height/2+getBodySize().height/2);
	hurmLabel  = CCLabelTTF::create("100", "arial", 18);
	hurmLabel->retain();
    // position the label on the center of the screen
    hurmLabel->setPosition(ccp(getContentSize().width/2,getContentSize().height/2+getBodySize().height/2));
    this->addChild(hurmLabel, 2);

	CCLayerColor* center = CCLayerColor::create(ccc4(255,255,0,128),10,10);
	center->setPosition(ccp(getContentSize().width/2,getContentSize().height/2));
	addChild(center,33);
	CCLayerColor* border = CCLayerColor::create(ccc4(255,0,0,128),body->getContentSize().width,body->getContentSize().height);
	//border->setPosition(ccp(-body->getContentSize().width/2,-body->getContentSize().height/2));
	//body->addChild(border,33);
	
}
bool Animal::initAnimalData()
{
	
	CCString * findPath = CCString::createWithFormat("model/%d",m_roleId);
	CCFileUtils::sharedFileUtils()->addSearchPath(findPath->getCString());
	ani_walk = getAnimationByName("walk");
	ani_walk->retain();

	CCString *frameName = CCString::createWithFormat("%d_walk_%04d.png",m_roleId,0);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	body = CCSprite::createWithSpriteFrameName(frameName->getCString());
	//body->setAnchorPoint(ccp(0,0));
	body->setPosition(ccp(0,0));
	body->retain();
	addChild(body);

	bodySize.width = frame->getRect().size.width;
	bodySize.height = frame->getRect().size.height;
	CCLog("%f,%f",bodySize.width,bodySize.height);
	float posx = getPositionX(),posy = getPositionY();
	
	bodyRect = CCRect(posx - bodySize.width/2,posy - bodySize.height/2,bodySize.height/2,bodySize.height);

	attackRect = CCRect(posx - bodySize.width/2,posy - bodySize.height/2,bodySize.height,bodySize.height);

	ani_hurt =  getAnimationByName("hurt",0.2);
	ani_hurt->retain();


	

	return true;
}
void Animal::playAnimation(CCAnimation* animation,int repeat)
{
	body->stopAllActions();
	if(animation)
	{
		CCAnimate * animate = CCAnimate::create(animation);
		if(repeat > 0)
			body->runAction(CCSequence::createWithTwoActions( CCRepeat::create(animate,repeat),
			CCCallFunc::create(this,callfunc_selector(Animal::animationCallBack))));
		else
			body->runAction(CCRepeatForever::create(animate));
	}else{
	}
}
void Animal::animationCallBack()
{
	fsm->doEvent("idle");
}
CCAnimation* Animal::getAnimationByName(const char* pzName,float defaultTime,int num)
{
	CCString * strPlist = CCString::createWithFormat("%d_%s.plist",m_roleId,pzName);
	CCString * strPng = CCString::createWithFormat("%d_%s.png",m_roleId,pzName);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(strPlist->getCString(),strPng->getCString());
	CCAnimation* animation = CCAnimation::create();
	
	CCSpriteFrame* frame;
	int realNum = 1.0f;
	for (int i=0;i<num;i++)
	{
		CCString *frameName = CCString::createWithFormat("%d_%s_%04d.png",m_roleId,pzName,i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
		if(frame)
			animation->addSpriteFrame(frame);
		else
			break;
		realNum = i;
	}
	//CCLog("frame time : %f, %f,%d",defaultTime/realNum,defaultTime,realNum);
	animation->setDelayPerUnit(defaultTime);
	return animation;
}
void Animal::correctPos(float &x,float &y)
{
	//CCLog("%d,%d : %f,%f",width,height,x,y);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int w = winSize.width,h = winSize.height;
	if(x < width/2)
		x=width/2;
	if(x > w- width/2)
		x= w- width/2;
	if(y<height/2)
		y=height/2;
	if(y>h-height/2)
		y=h-height/2;
}
	

void Animal::walkTo(CCPoint pos,bool isRun)
{
	if(pos.x == 0 && pos.y == 0)
	{
		//setStatus(IDLE);
		fsm->doEvent("idle");
		return;
	}
	CCPoint tpos = ccpAdd(getPosition(),ccp(pos.x*speed,pos.y*speed));
	correctPos(tpos.x,tpos.y);
	if(tpos.x < getPositionX())
	{
		body->setFlipX(true);
	}
	else
	{
		body->setFlipX(false);
	}
	setPosition(tpos);
	if(fsm->getState() != "walking" && fsm->getState() != "running")
	{
		fsm->doEvent("walk");
		//playAnimation(ani_walk,-1);
	}else if(isRun && fsm->getState() != "running" )
	{
		fsm->doEvent("walk");
	}else if(!isRun && fsm->getState() != "walking")
	{
		fsm->doEvent("walk");
	}
	
}
void Animal::setPosition(CCPoint tpos)
{
	CCNode::setPosition(tpos);
	if(body->isFlipX())
	{
		attackRect = CCRect(tpos.x - bodySize.width*1.5,tpos.y - bodySize.height/2,attackDis,bodySize.height);
	}
	else
	{
		attackRect = CCRect(tpos.x - bodySize.width/2,tpos.y - bodySize.height/2,attackDis,bodySize.height);
	}
	bodyRect = CCRect(tpos.x - bodySize.width/2,tpos.y - bodySize.height/2,bodySize.width,bodySize.height);
	//setContentSize(bodySize);
	setZOrder(480-tpos.y);
}
void Animal::idle()
{
}
void Animal::run()
{
}
bool Animal::canAttack(Animal* target)
{
	if(!target)
		return false;
	CCRect attRect = getAttackRect();
	CCRect eneBody = target->getBodyRect();
	if(attRect.intersectsRect(eneBody)&& (abs(getPositionY() - target->getPositionY()) < 50))
		return true;
	return false;

}
void Animal::attack(Animal* target,int skillid)
{
	if(target && target->getStatus() != "die")
	{
		target->beAttacked(this,attackNum);
		
	}
}
void Animal::beAttacked(Animal* attacker,int hurt)
{
	hp -= hurt;
	CCString* str = CCString::createWithFormat("%.0f",hp>0?hp:0);
	hurmLabel->setString(str->getCString());
	hpBar->setPercentage(hp/blood*100);
	if(hp <= 0)
	{
		//
	}
	else
	{
		
		fsm->doEvent("hurt");
	}
}
void Animal::die()
{
	removeFromParent();
}

void Animal::onWalk()
{
	speed = walkspeed;
	playAnimation(ani_walk,-1);
}
void Animal::onIdle()
{
	speed = 1;
	playAnimation(nullptr);
}
void Animal::onHurt()
{
	playAnimation(ani_hurt);
}


////////////////////////////  物理引擎实现  //////////////////////////////////

//
//bool Animal::isDirty()
//{
//    return true;
//}
//
//bool Animal::isIgnoreBodyRotation() const
//{
//    return m_bIgnoreBodyRotation;
//}
//
//void Animal::setIgnoreBodyRotation(bool bIgnoreBodyRotation)
//{
//    m_bIgnoreBodyRotation = bIgnoreBodyRotation;
//}
//
//// Override the setters and getters to always reflect the body's properties.
//const CCPoint& Animal::getPosition()
//{
//    updatePosFromPhysics();
//    return CCNode::getPosition();
//}
//
//void Animal::getPosition(float* x, float* y)
//{
//    updatePosFromPhysics();
//    return CCNode::getPosition(x, y);
//}
//
//float Animal::getPositionX()
//{
//    updatePosFromPhysics();
//    return m_obPosition.x;
//}
//
//float Animal::getPositionY()
//{
//    updatePosFromPhysics();
//    return m_obPosition.y;
//}
//
//#if CC_ENABLE_CHIPMUNK_INTEGRATION
//
//cpBody* Animal::getCPBody() const
//{
//    return m_pCPBody;
//}
//
//void Animal::setCPBody(cpBody *pBody)
//{
//    m_pCPBody = pBody;
//}
//
//void Animal::updatePosFromPhysics()
//{
//    cpVect cpPos = cpBodyGetPos(m_pCPBody);
//    m_obPosition = ccp(cpPos.x, cpPos.y);
//}
//
//void Animal::setPosition(const CCPoint &pos)
//{
//    cpVect cpPos = cpv(pos.x, pos.y);
//    cpBodySetPos(m_pCPBody, cpPos);
//}
//
//float Animal::getRotation()
//{
//    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() : -CC_RADIANS_TO_DEGREES(cpBodyGetAngle(m_pCPBody)));
//}
//
//void Animal::setRotation(float fRotation)
//{
//    if (m_bIgnoreBodyRotation)
//    {
//        CCSprite::setRotation(fRotation);
//    }
//    else
//    {
//        cpBodySetAngle(m_pCPBody, -CC_DEGREES_TO_RADIANS(fRotation));
//    }
//}
//
//// returns the transform matrix according the Chipmunk Body values
//CCAffineTransform Animal::nodeToParentTransform()
//{
//    // Although scale is not used by physics engines, it is calculated just in case
//	// the sprite is animated (scaled up/down) using actions.
//	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
//	cpVect rot = (m_bIgnoreBodyRotation ? cpvforangle(-CC_DEGREES_TO_RADIANS(m_fRotationX)) : m_pCPBody->rot);
//	float x = m_pCPBody->p.x + rot.x * -m_obAnchorPointInPoints.x * m_fScaleX - rot.y * -m_obAnchorPointInPoints.y * m_fScaleY;
//	float y = m_pCPBody->p.y + rot.y * -m_obAnchorPointInPoints.x * m_fScaleX + rot.x * -m_obAnchorPointInPoints.y * m_fScaleY;
//	
//	if (m_bIgnoreAnchorPointForPosition)
//    {
//		x += m_obAnchorPointInPoints.x;
//		y += m_obAnchorPointInPoints.y;
//	}
//	
//	return (m_sTransform = CCAffineTransformMake(rot.x * m_fScaleX, rot.y * m_fScaleX,
//                                                 -rot.y * m_fScaleY, rot.x * m_fScaleY,
//                                                 x,	y));
//}
//
//#elif CC_ENABLE_BOX2D_INTEGRATION
//
//b2Body* Animal::getB2Body() const
//{
//    return m_pB2Body;
//}
//
//void Animal::setB2Body(b2Body *pBody)
//{
//    m_pB2Body = pBody;
//}
//
//float Animal::getPTMRatio() const
//{
//    return m_fPTMRatio;
//}
//
//void Animal::setPTMRatio(float fRatio)
//{
//    m_fPTMRatio = fRatio;
//}
//
//// Override the setters and getters to always reflect the body's properties.
//void Animal::updatePosFromPhysics()
//{
//    b2Vec2 pos = m_pB2Body->GetPosition();
//    float x = pos.x * m_fPTMRatio;
//    float y = pos.y * m_fPTMRatio;
//    m_obPosition = ccp(x,y);
//}
//
//void Animal::setPosition(const CCPoint &pos)
//{
//    float angle = m_pB2Body->GetAngle();
//    m_pB2Body->SetTransform(b2Vec2(pos.x / m_fPTMRatio, pos.y / m_fPTMRatio), angle);
//}
//
//float Animal::getRotation()
//{
//    return (m_bIgnoreBodyRotation ? CCSprite::getRotation() :
//            CC_RADIANS_TO_DEGREES(m_pB2Body->GetAngle()));
//}
//
//void Animal::setRotation(float fRotation)
//{
//    if (m_bIgnoreBodyRotation)
//    {
//        CCSprite::setRotation(fRotation);
//    }
//    else
//    {
//        b2Vec2 p = m_pB2Body->GetPosition();
//        float radians = CC_DEGREES_TO_RADIANS(fRotation);
//        m_pB2Body->SetTransform(p, radians);
//    }
//}
//
//// returns the transform matrix according the Box2D Body values
//CCAffineTransform Animal::nodeToParentTransform()
//{
//    b2Vec2 pos  = m_pB2Body->GetPosition();
//	
//	float x = pos.x * m_fPTMRatio;
//	float y = pos.y * m_fPTMRatio;
//	
//	if (m_bIgnoreAnchorPointForPosition)
//    {
//		x += m_obAnchorPointInPoints.x;
//		y += m_obAnchorPointInPoints.y;
//	}
//	
//	// Make matrix
//	float radians = m_pB2Body->GetAngle();
//	float c = cosf(radians);
//	float s = sinf(radians);
//	
//	// Although scale is not used by physics engines, it is calculated just in case
//	// the sprite is animated (scaled up/down) using actions.
//	// For more info see: http://www.cocos2d-iphone.org/forum/topic/68990
//	if (!m_obAnchorPointInPoints.equals(CCPointZero))
//    {
//		x += ((c * -m_obAnchorPointInPoints.x * m_fScaleX) + (-s * -m_obAnchorPointInPoints.y * m_fScaleY));
//		y += ((s * -m_obAnchorPointInPoints.x * m_fScaleX) + (c * -m_obAnchorPointInPoints.y * m_fScaleY));
//	}
//    
//	// Rot, Translate Matrix
//	m_sTransform = CCAffineTransformMake( c * m_fScaleX,	s * m_fScaleX,
//									     -s * m_fScaleY,	c * m_fScaleY,
//									     x,	y );
//	
//	return m_sTransform;
//}
//
//#endif


//AnimalNode*****************************************************************