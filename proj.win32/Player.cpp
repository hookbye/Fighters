#include "Player.h"


Player::Player(void):ani_attack(NULL),ani_stand(NULL),ani_run(NULL),
	ani_skill(NULL),skill_effect(NULL),attack_effect(NULL),
	attEffNode(NULL),skillEffNode(NULL),
	attackInterval(0.5),attackIndex(0)
{
	attacks = CCArray::create();
	attacks->retain();
}


Player::~Player(void)
{
	CC_SAFE_RELEASE(attacks);
}
void Player::initFSM()
{
	Animal::initFSM();
	fsm->setOnEnter("idleing",[&](){onStand();});
	fsm->addState("attacking",[&](){onAttack();})
		
		->addState("running",[&](){onRun();})
		->addState("skilling",[&](){onSkill();})
		//->addState("standing",[&](){})
		/*->addState("attacking_1",[&](){onAttack();})
		->addState("attacking_2",[&](){onAttack();})
		->addState("attacking_3",[&](){onAttack();})
		->addState("attacking_4",[&](){onAttack();})
		->addState("attacking_5",[&](){onAttack();})*/
		;
	fsm->addEvent("walk","walking","running")
		->addEvent("walk","running","walking")
		->addEvent("attack","idleing","attacking")
		->addEvent("attack","walking","attacking")
		->addEvent("attack","running","attacking")

		->addEvent("skill","idleing","skilling")
		->addEvent("skill","walking","skilling")
		->addEvent("skill","running","skilling")

		->addEvent("hurt","idleing","hurting")
		->addEvent("hurt","walking","hurting")
		->addEvent("hurt","running","hurting")
		//->addEvent("hurt","skilling","hurting")

		->addEvent("idle","walking","idleing")
		->addEvent("idle","running","idleing")
		->addEvent("idle","hurting","idleing")
		->addEvent("idle","skilling","idleing")
		->addEvent("idle","attacking","idleing")
		/*->addEvent("idle","attacking_1","idleing")
		->addEvent("idle","attacking_2","idleing")
		->addEvent("idle","attacking_3","idleing")
		->addEvent("idle","attacking_4","idleing")
		->addEvent("idle","attacking_5","idleing")
		->addEvent("attack","attacking","attacking_1")
		->addEvent("attack","attacking_1","attacking_2")
		->addEvent("attack","attacking_2","attacking_3")
		->addEvent("attack","attacking_3","attacking_4")
		->addEvent("attack","attacking_4","attacking_5")
		->addEvent("attack","attacking_5","attacking")*/
		;

}
Player* Player::create(int roleId)
{
	Player* ani = new Player();
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
bool Player::initAnimalData()
{
	Animal::initAnimalData();
	
	ani_attack = getAnimationByName("attack",0.08);
	ani_attack->retain();
	attacks->addObject(ani_attack);

	for(int i=1;i<6;i++)
	{
		CCString* attName = CCString::createWithFormat("attack_%d",i);
		CCAnimation* ani = getAnimationByName(attName->getCString(),0.08);
		ani->retain();
		attacks->addObject(ani);
	}

	ani_stand = getAnimationByName("stand");
	ani_stand->retain();

	ani_run = getAnimationByName("run");
	ani_run->retain();

	ani_skill = getAnimationByName("skill",0.08);
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
void Player::run()
{
	speed = 2;
	fsm->doEvent("run");
}
 void Player::attack(Animal* target,int skillid)
 {
	 if(fsm->getState() != "attack")
	 {
		Animal::attack(target);
		if(skillid == 1)
		{
			fsm->doEvent("attack");
		}else if(skillid == 2)
		{
			fsm->doEvent("skill");
		}
	 }
 }

void Player::onAttack()
{
	playAnimation((CCAnimation*)attacks->objectAtIndex(attackIndex++%6));
}
void Player::onRun()
{
	speed = 2;
	playAnimation(ani_run,-1);
}
void Player::onSkill()
{
	playAnimation(ani_skill);
}
void Player::onHurt()
{
	playAnimation(ani_hurt);
}
void Player::onStand()
{
	playAnimation(ani_stand,-1);
}

void Player::update(float dt)
{
	if(fsm->getState() == "attacking")
	{
		//CCLog("attacking in update");
		attackInterval = 0.5;
	}else if(attackInterval >-0.02)
	{
		//CCLog("attacking###### in update");
		attackInterval -= dt;
		if(attackInterval == 0)
		{
			//CCLog(" reset attacking index###### in update");
			attackIndex = 0;
		}
	}
}