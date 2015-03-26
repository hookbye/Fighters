#include "Animal.h"


Animal::Animal(void):speed(1),blood(100),attackNum(5),
	ani_walk(NULL),ani_hurt(NULL),
	width(0),height(0),m_status(IDLE)
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
	if (ani && ani->initWithFile("CloseNormal.png"))
	{
		ani->autorelease();
		ani->m_roleId = roleId;
		ani->initAnimalData();
		ani->initFSM();
		return ani;
	}
	CC_SAFE_DELETE(ani);
	return NULL;
}
bool Animal::initAnimalData()
{
	CCString * findPath = CCString::createWithFormat("model/%d",m_roleId);
	CCFileUtils::sharedFileUtils()->addSearchPath(findPath->getCString());
	ani_walk = getAnimationByName("walk");
	ani_walk->retain();

	CCString *frameName = CCString::createWithFormat("%d_walk_%04d.png",m_roleId,1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	this->setDisplayFrame(frame);
	width = frame->getRect().size.width;
	height = frame->getRect().size.height;
	CCLog("%f,%f",getContentSize().width,height);
	

	ani_hurt =  getAnimationByName("hurt");
	ani_hurt->retain();

	return true;
}
void Animal::playAnimation(CCAnimation* animation,int repeat)
{
	stopAllActions();
	if(animation)
	{
		CCAnimate * animate = CCAnimate::create(animation);
		if(repeat > 0)
			this->runAction(CCSequence::createWithTwoActions( CCRepeat::create(animate,repeat),
			CCCallFunc::create(this,callfunc_selector(Animal::animationCallBack))));
		else
			this->runAction(CCRepeatForever::create(animate));
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
		setFlipX(true);
	else
		setFlipX(false);
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
void Animal::idle()
{
}
void Animal::run()
{
}
void Animal::attack(Animal* target,int skillid)
{
	if(target && target->getStatus() != "die")
		target->beAttacked(this,attackNum);
}
void Animal::beAttacked(Animal* attacker,int hurt)
{
	blood -= hurt;

	if(blood <= 0)
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
	speed = 1;
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
