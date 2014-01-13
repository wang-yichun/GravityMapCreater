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

	// default implements are used to call script callback if exist
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
private:

};

bool GameLayer::init() {
	CCLayerColor::init();
	setContentSize(CCSizeMake(1280,800));
	setColor(ccc3(61,62,113));
	setOpacity(255);

	setTouchEnabled(true);
	return true;
}

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesBegan");
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesMoved");
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesEnded");
}

void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesCancelled");
}