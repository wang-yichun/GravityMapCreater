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
/* С��;
/* ����һ����Ϸ����;
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
	CCSize m_MapGridSize; // �ϰ���ͼ�ĸ��Ӕ�Ŀ;
	CCSize m_CellSize;
	vector<MapCell> m_Map; // ��ͼ;

	CCNode * m_mother;
	void setMother(CCNode * mother);
	
	void resetMap(); // ��Ŀ�о�Ӧ���ڴ��滻Ϊ�����ݿ���ȡ��ͼ����;
	void refleshCellShow_adv(); // ����������ͼ��ʾ;
	void refleshCellShow_adv_nine(CCPoint loc); // �Ź���Χ���µ�ͼ��ʾ, locΪ���ĵ�;
	void refleshCellShow_adv(CCPoint loc); // ����locλ�õĵ�ͼ��ʾ ����Բ��;
private:

};
