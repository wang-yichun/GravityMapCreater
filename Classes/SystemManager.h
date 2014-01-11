#pragma once
#include "cocos2d.h"
#include "MapCell.h"
USING_NS_CC;

class SystemManager {
private:
	SystemManager();
	virtual ~SystemManager();
	static SystemManager * s_SystemManager;
	bool init();
public:
	static SystemManager * GetInstance();

	// MapCreate active vars.
	enumMapCellCode m_chosedCellCode;
};
