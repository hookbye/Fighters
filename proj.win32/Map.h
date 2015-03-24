#pragma once
#include "cocos2d.h"
#include "config.h"
USING_NS_CC;
class Map :
	public CCLayer
{
public:
	Map(int mapId);
	~Map(void);
	static Map* create(int mapId);
	virtual bool init();
	/*enum MapDirection{
		MAPUP,
		MAPDOWN,
		MAPLEFT,
		MAPRIGHT,
	};*/
	void correctPos(float &x,float &y);
	void move(Direction dir,float step = 1.0f);
	CC_SYNTHESIZE(int ,id,ID);
private:
	CCSprite* bg;
	float mapWidth;
	float mapHeight;
};

