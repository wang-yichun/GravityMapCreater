#include "Stage.h"
#include "CreaterConfig.h"

Stage * Stage::s_Stage = NULL;

Stage * Stage::GetInstance() {
	if (s_Stage == NULL) {
		s_Stage = new Stage();
		CCAssert(s_Stage -> init(), "Stage::init failed");
	}
	return s_Stage;
}

Stage::Stage():
	m_mother(NULL)
{}

Stage::~Stage() {
}

bool Stage::init() {
	m_stage_id = 100;
	m_stage_name = "New Stage";
	return true;
}

void Stage::setMother(CCNode * mother) {
	m_mother = mother;
}

void Stage::resetMap() {
	CCAssert(m_mother != NULL, "Stage.m_mother can't be null");
	m_Map.clear();

	//////////////////////////////////////////////////////////////////////////
	// width = 40 * 32 = 1280
	// height = 40 * 20 = 800
	m_CellSize = CCSizeMake(40,40);
	m_MapGridSize = CCPointMake(32, 20);
	for (int y = 0; y < int(m_MapGridSize.height); y++) {
		for (int x = 0; x < int(m_MapGridSize.width); x++) {
			
			MapCell mc;
			//if ( (x + y) % 2 == 0) {
			//if (CCRANDOM_MINUS1_1() > 0) {
			//	mc.setMapCell(CCPointMake(x,y), kNormal);
			//} else {
				mc.setMapCell(CCPointMake(x,y), kNull);
			//}

			m_Map.push_back(mc);

			CCPoint pos = loc2pos(CCPointMake(x,y));

			if (mc.primaryNode != NULL) {
				mc.primaryNode -> setPosition(pos);
				m_mother -> addChild(mc.primaryNode, 100, 1);
			}
			if (mc.secondaryNode != NULL) {
				mc.secondaryNode -> setPosition(pos);
				m_mother -> addChild(mc.secondaryNode, 110, 2);
			}
			if (DEBUG_CELL_INFO_SHOW) {
				mc.infoTTF -> setPosition(pos);
				m_mother -> addChild(mc.infoTTF, 200, 3);
			}
		}
	}
}

void Stage::clearMap() {
	CCAssert(m_mother != NULL, "Stage.m_mother can't be null");

	m_mother -> removeAllChildren();

	m_Map.clear();
}

void Stage::refleshMapShow() {
	CCAssert(m_mother != NULL, "Stage.m_mother can't be null");
	for (int idx = 0; idx < m_Map.size(); idx++) {
		CCPoint loc = idx2loc(idx);
		CCPoint pos = loc2pos(loc);
		MapCell& mc = m_Map[idx];
		if (mc.primaryNode != NULL) {
			mc.primaryNode -> setPosition(pos);
			m_mother -> addChild(mc.primaryNode, 100, 1);
		}
		if (mc.secondaryNode != NULL) {
			mc.secondaryNode -> setPosition(pos);
			m_mother -> addChild(mc.secondaryNode, 110, 2);
		}
		if (DEBUG_CELL_INFO_SHOW) {
			mc.infoTTF -> setPosition(pos);
			m_mother -> addChild(mc.infoTTF, 200, 3);
		}
	}
}

void Stage::refleshCellShow_adv() {
	for (vector<MapCell>::iterator it = m_Map.begin(); it != m_Map.end(); it++) {
		refleshCellShow_adv(it->loc);
	}
}

void Stage::refleshCellShow_adv_nine(CCPoint loc) {
	CCAssert(isInScope(loc), "Stage::refleshCellShow_adv loc out of bound");

	CCPoint p[9];
	p[0] = loc;
	p[1] = CCPointMake(loc.x + 1, loc.y);
	p[2] = CCPointMake(loc.x, loc.y + 1);
	p[3] = CCPointMake(loc.x - 1, loc.y);
	p[4] = CCPointMake(loc.x, loc.y - 1);
	p[5] = CCPointMake(loc.x + 1, loc.y + 1);
	p[6] = CCPointMake(loc.x - 1, loc.y + 1);
	p[7] = CCPointMake(loc.x - 1, loc.y - 1);
	p[8] = CCPointMake(loc.x + 1, loc.y - 1);

	MapCell null_cell;
	null_cell.code = kNull;

//	MapCell mapCell[9];

	for (int i = 0; i < 9; i++) {
		if (isInScope(p[i])) {
			refleshCellShow_adv(p[i]);
		}
	}
}

void Stage::refleshCellShow_adv(CCPoint loc) {
	CCAssert(isInScope(loc), "Stage::refleshCellShow_adv loc out of bound");

	CCPoint p[9];
	p[0] = loc;
	p[1] = CCPointMake(loc.x + 1, loc.y);
	p[2] = CCPointMake(loc.x, loc.y + 1);
	p[3] = CCPointMake(loc.x - 1, loc.y);
	p[4] = CCPointMake(loc.x, loc.y - 1);
	p[5] = CCPointMake(loc.x + 1, loc.y + 1);
	p[6] = CCPointMake(loc.x - 1, loc.y + 1);
	p[7] = CCPointMake(loc.x - 1, loc.y - 1);
	p[8] = CCPointMake(loc.x + 1, loc.y - 1);
	
	MapCell null_cell;
	null_cell.code = kNull;

	MapCell mapCell[9];

	for (int i = 0; i < 9; i++) {
		mapCell[i] = isInScope(p[i]) ? cell(p[i]) : null_cell;
	}

	char param[9];
	memset(param, 0, sizeof(param));
	for (int i = 0; i < 9; i++) {
		if (MapCell::GetCellCodeIsNullShow(mapCell[i].code)) { // 障碍显示码;
			param[i] = '0';
		} else {
			param[i] = '1';
		}
	}

	mapCell[0].refleshSprite_adv(param);
}