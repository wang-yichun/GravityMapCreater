#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

enum enumMapCellCode {
	kNull = 0,
	kNormal = 1,
	kStart = 2,		// 出发点;
	kEnd = 3		// 目的地;
};

//
//地图单元格子;
//

class MapCell {
public:
	MapCell();
	MapCell(CCPoint loc, enumMapCellCode code);
	~MapCell();

	CCPoint loc; // 方格坐标;
	enumMapCellCode code; // 编号;
	CCNode * primaryNode; // 主节点;
	CCSprite * primarySprite; // 主显示精灵; 被用来显示连接图了。
	CCNode * secondaryNode; // 第二节点;
	CCSprite * secondarySprite; // 第二显示精灵;
	CCLabelTTF * infoTTF; // 測試;
	CCNode * parent; // 宿主;

	void setMapCell(CCPoint loc, enumMapCellCode code);
	void setCode(enumMapCellCode _code);
	void setParent(CCNode *pNode);
	void refleshSprite_adv(char * param);

	static CCPoint GetCellCodeAP(enumMapCellCode cell_code); 
	static bool GetCellCodeIsNullShow(enumMapCellCode cell_code); // 在连通显示法中，格子是否处于连通点的‘空’;
private:
	void refleshSprite(); // 此处的sprite显示与周围无关;
};
