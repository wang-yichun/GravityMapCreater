#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum enumMapCellCode {
	kNull = 0,
	kNormal
};

/************************************************************************/
/* ��ͼ��Ԫ����;
/************************************************************************/
struct MapCell {
public:
	CCPoint loc; // ��������;
	enumMapCellCode code; // ���;
	CCSprite * primarySprite; // ����ʾ����;

	void setCode(enumMapCellCode _code);

private:
	void refleshSprite();
};

void MapCell::setCode(enumMapCellCode _code) {
	this->code = _code;
	refleshSprite();
}

void MapCell::refleshSprite() {
	switch (code) {
	case kNull:
		primarySprite = NULL;
		break;
	case kNormal:
		primarySprite = NULL; // TODO: 
		break;
	default:
		primarySprite = NULL;
		break;
	}
}