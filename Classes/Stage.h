#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include "StageTools.h"
#include "MapCell.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

/************************************************************************/
/* 小关;
/* 描述一局游戏场景;
/************************************************************************/
class Stage :
	public StageTools {
private:
	Stage();
	virtual ~Stage();
	static Stage * s_Stage;
	bool init();
public:
	static Stage * GetInstance();
	//////////////////////////////////////////////////////////////////////////
	// StageTools
public:
	CCSize getMapGridSize() { return m_MapGridSize; }
	CCSize getCellSize() { return m_CellSize; }
	vector<MapCell>& getMap() { return m_Map; }
	//////////////////////////////////////////////////////////////////////////
public:
	CCSize m_MapGridSize; // 障碍地图的格子數目;
	CCSize m_CellSize;
	vector<MapCell> m_Map; // 地图;

	CCNode * m_mother;
	void setMother(CCNode * mother);
	
	void resetMap(); // 项目中就应该在此替换为从数据库提取地图数据;
	void refleshCellShow_adv(); // 更新整个地图显示;
	void refleshCellShow_adv_nine(CCPoint loc); // 九宫格范围更新地图显示, loc为中心点;
	void refleshCellShow_adv(CCPoint loc); // 更新loc位置的地图显示 处理圆角;
private:

};
