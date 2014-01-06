#include "MapCell.h"


MapCell::MapCell(): primarySprite(NULL), parent(NULL), infoTTF(NULL) {}
MapCell::~MapCell() {}

void MapCell::setMapCell(CCPoint loc, enumMapCellCode code) {
	this -> loc = loc;
	stringstream ss;
	ss << loc.x << "," << loc.y;
	this -> infoTTF = CCLabelTTF::create(ss.str().c_str(),"Arial",10);
	this -> infoTTF -> setColor(ccc3(255,0,0));
	this -> setCode(code);
}

void MapCell::setCode(enumMapCellCode _code) {
	this->code = _code;
	refleshSprite();
}

void MapCell::setParent(CCNode *pNode) {
	CCAssert(pNode != NULL, "pNode is NULL.");
	parent = pNode;
}

void MapCell::refleshSprite() {
	string frame_name = "";
	switch (code) {
	case kNull:
		frame_name = "";
		break;
	case kNormal:
		frame_name = "images/art_design_11.png";
		break;
	default:
		frame_name = "";
		break;
	}

	if (frame_name == "") {
		if (primarySprite != NULL) {
			primarySprite -> removeFromParent();
			primarySprite = NULL;
		}
	} else {
		if (primarySprite == NULL) {
			primarySprite = CCSprite::createWithSpriteFrameName(frame_name.c_str());
			primarySprite -> setAnchorPoint(CCPointMake(.5f,.5f));
		} else {
			primarySprite -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame_name.c_str()));
		}
	}
}