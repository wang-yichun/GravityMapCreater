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
/* ��ͼ��Ԫ����;
/************************************************************************/
class MapCell {
public:
	MapCell();
	MapCell(CCPoint loc, enumMapCellCode code);
	~MapCell();

	CCPoint loc; // ��������;
	enumMapCellCode code; // ���;
	CCSprite * primarySprite; // ����ʾ����;
	CCLabelTTF * infoTTF; // �yԇ;
	CCNode * parent; // ����;

	void setMapCell(CCPoint loc, enumMapCellCode code);
	void setCode(enumMapCellCode _code);
	void setParent(CCNode *pNode);

private:
	void refleshSprite();
};
