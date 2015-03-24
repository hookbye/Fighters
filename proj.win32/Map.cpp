#include "Map.h"


Map::Map(int mapId):id(mapId),bg(NULL),mapWidth(0),mapHeight(0)
{
}


Map::~Map(void)
{
}

Map* Map::create(int mapId)
{
	Map* map = new Map(mapId);
	if(map && map->init())
	{
		map->autorelease();
		return map;
	}
	CC_SAFE_DELETE(map);
	return NULL;
}
bool Map::init()
{
	do{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCString* bgName = CCString::createWithFormat("%d.png",id);
		bg = CCSprite::create(bgName->getCString());
		bg->setAnchorPoint(ccp(0,0));
		addChild(bg,0);

		mapWidth = bg->getContentSize().width;
		mapHeight = bg->getContentSize().height;
		if(mapWidth < winSize.width)
			mapWidth = winSize.width;
		if(mapHeight < winSize.height)
			mapHeight = winSize.height;

		return true;
	}while(0);
	return false;
}
void Map::correctPos(float &x,float &y)
{
	if(x > 0)
		x=0;
	if(y>0)
		y=0;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int w = winSize.width,h = winSize.height;
	if(x<-(mapWidth-w))
		x = -(mapWidth-w);
	if(y<-(mapHeight-h))
		x = -(mapHeight-w);
}
void Map::move(Direction dir,float step)
{
	float x = getPositionX(),y = getPositionY();
	switch (dir)
	{
	case UP:
		y+=step;
		break;
	case DOWN:
		y-=step;
		break;
	case LEFT:
		x-=step;
		break;
	case RIGHT:
		x+=step;
		break;
	default:
		break;
	}
	correctPos(x,y);
	setPosition(ccp(x,y));
}