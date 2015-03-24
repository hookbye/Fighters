#include "Player.h"


Player::Player(void)
{
}


Player::~Player(void)
{
}
Player* Player::create(int roleId)
{
	Player* ani = new Player();
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
bool Player::initAnimalData()
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