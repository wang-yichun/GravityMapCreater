#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "MapCell.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;


//////////////////////////////////////////////////////////////////////////
// tag int
// 4 3 2 | LT T RT
// 5 0 1 |  L C R
// 6 7 8 | LB B RB
enum enumAnchorType {
	kC = 0, kR = 1, kRT = 2, kT = 3,
	kLT = 4, kL = 5, kLB = 6, kB = 7,
	kRB = 8
};

class StageTools {
public:
	virtual CCSize getMapGridSize() = 0;
	virtual CCSize getCellSize() = 0;
	virtual vector<MapCell>& getMap() = 0;
	CCSize getMapSize();
public:
	bool isInScope(int idx) { return idx >= 0 || (size_t)idx < getMap().size(); };
	bool isInScope(CCPoint loc_or_pos, bool isPos = false) {
		if (isPos){
			CCSize map_size = getMapSize();
			CCRect map_rect = CCRectMake(0,0,map_size.width,map_size.height);
			return map_rect.containsPoint(loc_or_pos);
		} else {
			int idx = int(getMapGridSize().width) * int(loc_or_pos.y) + int(loc_or_pos.x);
			return (idx >= 0 && (size_t)idx < getMap().size());
		}
		
	}

	CCPoint idx2loc(int idx);
	int loc2idx(CCPoint loc);
	MapCell& cell(int idx);
	MapCell& cell(CCPoint loc);

	CCPoint idx2pos(int idx, enumAnchorType at = kC); // 格子坐标转换屏幕坐标，第二参数为相对锚点位位置;
	CCPoint loc2pos(CCPoint loc, enumAnchorType at = kC);

	CCPoint pos2loc(CCPoint pos); // 屏幕坐标 -> 格子坐标;
	int pos2idx(CCPoint pos);

	CCPoint AncharDiff(enumAnchorType at);
};
