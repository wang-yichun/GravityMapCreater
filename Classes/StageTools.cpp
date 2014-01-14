#include "StageTools.h"

CCSize StageTools::getMapSize() {
	CCSize map_grid_size = getMapGridSize();
	CCSize cell_size = getCellSize();
	CCSize map_size = CCSizeMake(map_grid_size.width * cell_size.width, map_grid_size.height * cell_size.height);
	return map_size;
}

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

CCPoint StageTools::idx2pos(int idx, enumAnchorType at) {
	CCAssert(isInScope(idx), "idx out of bound. ");
	return loc2pos(idx2loc(idx), at);
}

CCPoint StageTools::loc2pos(CCPoint loc, enumAnchorType at) {
	CCAssert(isInScope(loc), "idx out of bound.");
	CCPoint pos = CCPoint(getCellSize().width * loc.x, getCellSize().height * loc.y) + AncharDiff(at) + AncharDiff(kRT);
	return pos;
}

CCPoint StageTools::pos2loc(CCPoint pos) {
	CCSize cell_size = this->getCellSize();
	CCPoint loc = ccp(floorf(pos.x / cell_size.width), floorf(pos.y / cell_size.height));
	CCAssert(isInScope(loc), "pos out of bound.");
	return loc;
}

int StageTools::pos2idx(CCPoint pos) {
	CCSize cell_size = this->getCellSize();
	CCPoint loc = ccp(floorf(pos.x / cell_size.width), floorf(pos.y / cell_size.height));
	CCAssert(isInScope(loc), "pos out of bound.");
	return loc2idx(loc);
}

CCPoint StageTools::AncharDiff(enumAnchorType at) {
	CCPoint p;
	CCSize cs = getCellSize();
	switch (at) {
	case kC:
		p.setPoint(0,0);
		break;
	case kR:
		p.setPoint(cs.width/2,0);
		break;
	case kRT:
		p.setPoint(cs.width/2,cs.height/2);
		break;
	case kT:
		p.setPoint(0,cs.height/2);
		break;
	case kLT:
		p.setPoint(-cs.width/2,cs.height/2);
		break;
	case kL:
		p.setPoint(-cs.width/2,0);
		break;
	case kLB:
		p.setPoint(-cs.width/2,-cs.height/2);
		break;
	case kB:
		p.setPoint(0,-cs.height/2);
		break;
	case kRB:
		p.setPoint(cs.width/2,-cs.height/2);
		break;
	default:
		CCAssert(false, "enumAnchorType err.");
		break;
	}
	return p;
}