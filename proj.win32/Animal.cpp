#include "Animal.h"


Animal::Animal(void):walk(NULL),die(NULL),hurt(NULL)
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
	//walk = 
	walk = getAnimationByName("walk");
	walk->retain();
	CCAnimate * animate = CCAnimate::create(walk);
	this->runAction(CCRepeatForever::create(animate));
	return true;
}
CCAnimation* Animal::getAnimationByName(const char* pzName,int num)
{
	/*std::string name;
	name.append(m_roleId+"_");
	name.append(pzName);
	std::string plist(name);
	plist.append(".plist");
	std::string png(name);
	png.append(".png");*/

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
void Animal::walkTo(CCPoint pos)
{
}
void Animal::idle()
{
}
void Animal::attack(Animal* target,int hurt)
{
}