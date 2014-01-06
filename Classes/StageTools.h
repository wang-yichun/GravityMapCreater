#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "MapCell.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class StageTools {
public:
	virtual CCSize getMapGridSize() = 0;
	virtual vector<MapCell>& getMap() = 0;
public:
	bool isInScope(int idx) { return idx >= 0 || idx < getMap().size(); };
	bool isInScope(CCPoint loc) {
		int idx = int(getMapGridSize().width) * int(loc.y) + int(loc.x);
		return (idx >= 0 && idx < getMap().size());
	}
	CCPoint idx2loc(int idx);
	int loc2idx(CCPoint loc);
	MapCell& cell(int idx);
	MapCell& cell(CCPoint loc);
};

CCPoint StageTools::idx2loc(int idx) {
	CCAssert(isInScope(idx), "idx out of bound.");
	CCPoint point;
	point.x = idx % int(getMapGridSize().width);
	point.y = idx / int(getMapGridSize().width);
	return point;
}

int StageTools::loc2idx(CCPoint loc) {
	CCAssert(isInScope(loc), "loc out of bound.");
	int idx = int(getMapGridSize().width) * int(loc.y) + int(loc.x);
	return idx;
}

MapCell& StageTools::cell(int idx) {
	CCAssert(isInScope(idx), "out of bound.");
	return getMap().at(idx);
}

MapCell& StageTools::cell(CCPoint loc) {
	int idx = loc2idx(loc);
	return getMap().at(idx);
}