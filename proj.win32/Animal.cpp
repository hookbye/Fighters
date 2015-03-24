#include "Animal.h"


Animal::Animal(void):speed(1),
	ani_walk(NULL),ani_die(NULL),ani_hurt(NULL),
	width(0),height(0)
{
}


Animal::~Animal(void)
{
}


Animal* Animal::create(int roleId)
{
	Animal* ani = new Animal();
	if (ani && ani->initWithFile("CloseNormal.png"))
	{
		ani->autorelease();
		ani->m_roleId = roleId;
		ani->initAnimalData();
		return ani;
	}
	CC_SAFE_DELETE(ani);
	return NULL;
}
bool Animal::initAnimalData()
{
	ani_walk = getAnimationByName("walk");
	ani_walk->retain();

	CCString *frameName = CCString::createWithFormat("%d_walk_%04d.png",m_roleId,1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	this->setDisplayFrame(frame);
	width = frame->getRect().size.width;
	height = frame->getRect().size.height;
	CCLog("%f,%f",getContentSize().width,height);
	
	ani_die = getAnimationByName("die");
	ani_die->retain();

	ani_hurt =  getAnimationByName("hurt",2);
	ani_hurt->retain();

	playAnimation(ani_walk);
	return true;
}
void Animal::playAnimation(CCAnimation* animation)
{
	CCAnimate * animate = CCAnimate::create(animation);
	this->runAction(CCRepeatForever::create(animate));
}
CCAnimation* Animal::getAnimationByName(const char* pzName,int num)
{
	CCString * strPlist = CCString::createWithFormat("%d_%s.plist",m_roleId,pzName);
	CCString * strPng = CCString::createWithFormat("%d_%s.png",m_roleId,pzName);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(strPlist->getCString(),strPng->getCString());
	CCAnimation* animation = CCAnimation::create();
	
	CCSpriteFrame* frame;
	for (int i=0;i<num;i++)
	{
		CCString *frameName = CCString::createWithFormat("%d_%s_%04d.png",m_roleId,pzName,i);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(frame);
	}
	animation->setDelayPerUnit(0.2f);
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
	

void Animal::walkTo(CCPoint pos)
{
	CCPoint tpos = ccpAdd(getPosition(),ccp(pos.x*speed,pos.y*speed));
	correctPos(tpos.x,tpos.y);
	if(tpos.x < getPositionX())
		setFlipX(true);
	else
		setFlipX(false);
	setPosition(tpos);
}
void Animal::idle()
{
}
void Animal::attack(Animal* target,int hurt)
{
}