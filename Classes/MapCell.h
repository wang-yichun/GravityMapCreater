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

enum enumMapCellPollCode {
	emcpcNull = 0,
	emcpcPoll
};

//////////////////////////////////////////////////////////////////////////
//地图单元格子;
//////////////////////////////////////////////////////////////////////////
class MapCell {
public:
	MapCell();
	MapCell(CCPoint loc, enumMapCellCode code);
	~MapCell();

	CCPoint loc; // 方格坐标;
	enumMapCellCode code; // 编号;
	enumMapCellPollCode poll_code; // 污染状态编号;

	CCNode * primaryNode; // 主节点;
	CCSprite * primarySprite; // 主显示精灵; 被用来显示连接图了。
	CCNode * secondaryNode; // 第二节点;
	CCSprite * secondarySprite; // 第二显示精灵;
	CCNode * pollNode; // 用来承载污染土地的精灵;
	CCSprite * pollSprite;
	CCLabelTTF * infoTTF; // 测试;
	CCNode * parent; // 宿主;

	void setMapCell(CCPoint loc, enumMapCellCode code); // create一些空的CCNode用于将来填充CCSprite,内部调用setCode,即只有在第一次初始化时调用,以后的改变使用setCode;
	void setCode(enumMapCellCode _code); // 设置code后调用refleshSprite;
	void setPollCode(enumMapCellPollCode _poll_code);
	void setParent(CCNode *pNode);
	void refleshSprite_adv(char * param); // 这个显示功能完成了周边相关显示,传入的是九宫格的模式 xxxxxxxxx;

	static CCPoint GetCellCodeAP(enumMapCellCode cell_code); // 得到该图片对应基准格子中心时,自身的锚点应该设置的值,与自身的大小有关,自身为1x1个格子时是(0.5,0.5);
	static bool GetCellCodeIsNullShow(enumMapCellCode cell_code); // 在连通显示法中，格子是否处于连通点的‘空’;
private:
	void refleshSprite(); // 此处的sprite显示与周围无关;
};
