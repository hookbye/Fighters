#include "Player.h"


Player::Player(void):ani_attack(NULL),ani_stand(NULL),ani_run(NULL),
	ani_skill(NULL),skill_effect(NULL),attack_effect(NULL),
	attEffNode(NULL),skillEffNode(NULL)
{
	attacks = CCArray::create();
	attacks->retain();
}


Player::~Player(void)
{
	CC_SAFE_RELEASE(attacks);
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
	Animal::initAnimalData();
	
	ani_attack = getAnimationByName("attack",7);
	ani_attack->retain();

	ani_stand = getAnimationByName("stand");
	ani_stand->retain();

	ani_run = getAnimationByName("run");
	ani_run->retain();

	ani_skill = getAnimationByName("skill");
	ani_skill->retain();

	skill_effect = getAnimationByName("skill_effect");
	skill_effect->retain();
	attack_effect = getAnimationByName("attack_effect");
	attack_effect->retain();
	

	attEffNode = CCNode::create();
	attEffNode->retain();
	addChild(attEffNode);

	skillEffNode = CCNode::create();
	skillEffNode->retain();
	addChild(skillEffNode);

	CCString *frameName = CCString::createWithFormat("%d_stand_%04d.png",m_roleId,1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	this->setDisplayFrame(frame);
	width = frame->getRect().size.width;
	height = frame->getRect().size.height;
	
	playAnimation(ani_stand);
	return true;
}

 void Player::attack(Animal* target)
 {
	 Animal::attack(target);
	 playAnimation(ani_attack);
 }