#include "Enemy.h"


Enemy::Enemy(void):ani_die(NULL)
{
}


Enemy::~Enemy(void)
{
}
void Enemy::initFSM()
{
	Animal::initFSM();
	fsm->addState("dieing",[&](){playAnimation(ani_die);})
		->addState("hurting",[&](){playAnimation(ani_hurt);})
		;
	fsm->addEvent("die","walking","dieing")
		->addEvent("die","hurting","dieing")
		->addEvent("hurt","walking","hurting")
		->addEvent("hurt","idleing","hurting")
		;
}
Enemy* Enemy::create(int roleId)
{
	Enemy* ani = new Enemy();
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

bool Enemy::initAnimalData()
{
	Animal::initAnimalData();
	
	ani_die = getAnimationByName("die");
	ani_die->retain();

	CCString *frameName = CCString::createWithFormat("%d_walk_%04d.png",m_roleId,1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	this->setDisplayFrame(frame);
	width = frame->getRect().size.width;
	height = frame->getRect().size.height;
	playAnimation(ani_walk,-1);
	return true;
}

void Enemy::attack(Animal* target)
{
	Animal::attack(target);
	
}
void Enemy::beAttacked(Animal* attacker,int hurt)
{
	Animal::beAttacked(attacker,hurt);
	if(blood <= 0)
	{
		m_status = DIE;
		playAnimation(ani_die);
		CCSequence* seq = CCSequence::createWithTwoActions(CCDelayTime::create(1.6),
			CCCallFunc::create(this,callfunc_selector(Enemy::die)));
		runAction(seq);
	}
	else
	{
	}
}
void Enemy::die()
{
	Animal::die();
}