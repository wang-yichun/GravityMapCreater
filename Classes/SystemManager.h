#pragma once
#include "cocos2d.h"
#include "MapCell.h"
USING_NS_CC;

struct TStage {
	int cell_height;
	int cell_width;
	int map_grid_height;
	int map_grid_width;
	int stage_id;
	string stage_name;
};

class SystemManager {
private:
	SystemManager();
	virtual ~SystemManager();
	static SystemManager * s_SystemManager;
	bool init();
public:
	static SystemManager * GetInstance();

	// db full path.
	string m_db_full_path;
	// db action.
	void insert_stage(const TStage& t_stage);
	void select_stage();

	// MapCreate active vars.
	enumMapCellCode m_chosedCellCode;
};
