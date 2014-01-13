#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

enum enumMapCellCode {
	kNull = 0,
	kNormal
};

/************************************************************************/
/* 地图单元格子;
/************************************************************************/
class MapCell {
public:
	MapCell();
	MapCell(CCPoint loc, enumMapCellCode code);
	~MapCell();

	CCPoint loc; // 方格坐标;
	enumMapCellCode code; // 编号;
	CCNode * primaryNode; // 主节点;
	CCSprite * primarySprite; // 主显示精灵;
	CCLabelTTF * infoTTF; // 測試;
	CCNode * parent; // 宿主;

	void setMapCell(CCPoint loc, enumMapCellCode code);
	void setCode(enumMapCellCode _code);
	void setParent(CCNode *pNode);
	void refleshSprite_adv(char * param);

private:
	void refleshSprite(); // 此处的sprite显示与周围无关;
};
