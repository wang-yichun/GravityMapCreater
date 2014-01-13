#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "Stage.h"
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
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
		CCTouch * pTouch = dynamic_cast<CCTouch *>(*it);
		CCPoint pos = this -> convertTouchToNodeSpace(pTouch);
		CCPoint loc = Stage::GetInstance()->pos2loc(pos);
		int idx = Stage::GetInstance()->pos2idx(pos);
		CCLOGINFO("ccTouchesBegan pos:(%f,%f) loc:(%f,%f) idx:(%d) tID:(%d)", pos.x, pos.y, loc.x, loc.y, idx, pTouch->getID());
	}
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesMoved");
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
		CCTouch * pTouch = dynamic_cast<CCTouch *>(*it);
		CCPoint pos = this -> convertTouchToNodeSpace(pTouch);
		CCPoint loc = Stage::GetInstance()->pos2loc(pos);
		int idx = Stage::GetInstance()->pos2idx(pos);
		CCLOGINFO("ccTouchesMoved pos:(%f,%f) loc:(%f,%f) idx:(%d) tID:(%d)", pos.x, pos.y, loc.x, loc.y, idx, pTouch->getID());
	}
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesEnded");
	for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++) {
		CCTouch * pTouch = dynamic_cast<CCTouch *>(*it);
		CCPoint pos = this -> convertTouchToNodeSpace(pTouch);
		CCPoint loc = Stage::GetInstance()->pos2loc(pos);
		int idx = Stage::GetInstance()->pos2idx(pos);
		CCLOGINFO("ccTouchesEnded pos:(%f,%f) loc:(%f,%f) idx:(%d) tID:(%d)", pos.x, pos.y, loc.x, loc.y, idx, pTouch->getID());
	}
}

void GameLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent) {
	CCLOG("GameLayer::ccTouchesCancelled");
}