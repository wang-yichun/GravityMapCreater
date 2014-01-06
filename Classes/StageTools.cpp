#include "StageTools.h"

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