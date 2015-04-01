#pragma once
#include "cocos2d.h"
USING_NS_CC;
class ProgressBar :
	public CCProgressTimer
{
public:
	ProgressBar(void);
	ProgressBar(CCSprite* bg,CCSprite* barName);
	~ProgressBar(void);
	static ProgressBar* create(const char* bgName,const char* barName);
	static ProgressBar* create(CCSprite* bg,CCSprite* barName);
private:
	CCSprite* barBg;
	CCSprite* blinkSpr; 
};

