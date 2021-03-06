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
	fsm->setOnEnter("idleing",[&](){onWalk();});
	fsm->addState("dieing",[&](){playAnimation(ani_die);})
		->addState("hurting",[&](){playAnimation(ani_hurt);})
		;
	fsm->addEvent("die","walking","dieing")
		->addEvent("die","hurting","dieing")
		->addEvent("hurt","walking","hurting")
		->addEvent("hurt","idleing","hurting")
		->addEvent("idle","hurting","idleing")
		;
}
Enemy* Enemy::create(int roleId)
{
	Enemy* ani = new Enemy();
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

bool Enemy::initAnimalData()
{
	Animal::initAnimalData();
	
	ani_die = getAnimationByName("die");
	ani_die->retain();

	CCString *frameName = CCString::createWithFormat("%d_walk_%04d.png",m_roleId,1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
	/*this->setDisplayFrame(frame);*/
	width = frame->getRect().size.width;
	height = frame->getRect().size.height;
	playAnimation(ani_walk,-1);
	return true;
}
void Enemy::initBasicData()
{
	Animal::initBasicData();
}
void Enemy::attack(Animal* target)
{
	Animal::attack(target);
	
}
void Enemy::beAttacked(Animal* attacker,int hurt)
{
	Animal::beAttacked(attacker,hurt);
	if(hp <= 0)
	{
		fsm->doEvent("die");
		CCSequence* seq = CCSequence::createWithTwoActions(CCDelayTime::create(0.5),
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