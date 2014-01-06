#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer :
	public CCLayerColor
{
public:
	GameLayer();
	virtual ~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();
private:

};

bool GameLayer::init() {
	CCLayerColor::init();
	setContentSize(CCSizeMake(1280,800));
	setColor(ccc3(61,62,113));
	setOpacity(255);
	return true;
}

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}