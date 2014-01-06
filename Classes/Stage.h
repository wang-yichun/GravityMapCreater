#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "StageTools.h"
#include "MapCell.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

/************************************************************************/
/* 小关;
/* 描述一局游戏场景;
/************************************************************************/
class Stage :
	public StageTools {
	//////////////////////////////////////////////////////////////////////////
	// StageTools
public:
	CCSize getMapGridSize() { return m_MapGridSize; }
	vector<MapCell>& getMap() { return m_Map; }
	//////////////////////////////////////////////////////////////////////////
public:
	Stage();
	~Stage();
	CCSize m_MapGridSize; // 障碍地图的格子大小;
	vector<MapCell> m_Map; // 地图;

	void resetMap();
private:

};


Stage::Stage():
m_MapGridSize() 
{}

Stage::~Stage() {
}

void Stage::resetMap() {

	//////////////////////////////////////////////////////////////////////////
	// width = 40 * 32 = 1280
	// height = 40 * 20 = 800

	m_MapGridSize = CCPointMake(32, 20);
	for (int y = 0; y < int(m_MapGridSize.height); y++) {
		for (int x = 0; x < int(m_MapGridSize.width); x++) {
			MapCell mc;
			mc.code = kNull;
			mc.loc = CCPointMake(x, y);
			mc.primarySprite = NULL;
		}
	}
}

