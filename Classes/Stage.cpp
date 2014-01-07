#include "Stage.h"

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
			if (CCRANDOM_MINUS1_1() > 0) {
				mc.setMapCell(CCPointMake(x,y), kNormal);
			} else {
				mc.setMapCell(CCPointMake(x,y), kNull);
			}

			m_Map.push_back(mc);
			
			if (mc.primaryNode != NULL) {
				CCPoint pos = loc2pos(CCPointMake(x,y));
				CCLOG( "(%d,%d) - (%f,%f)", x ,y , pos.x, pos.y );
				mc.primaryNode -> setPosition(pos);
				m_mother -> addChild(mc.primaryNode, 100);
				mc.infoTTF -> setPosition(pos);
				m_mother -> addChild(mc.infoTTF, 110);
			}
		}
	}
}

void Stage::refleshCellShow_adv() {
	for (vector<MapCell>::iterator it = m_Map.begin(); it != m_Map.end(); it++) {
		refleshCellShow_adv(it->loc);
	}
}

void Stage::refleshCellShow_adv(CCPoint loc) {
	CCAssert(isInScope(loc), "Stage::refleshCellShow_adv loc out of bound");

	CCPoint p[5];
	p[0] = loc;
	p[1] = CCPointMake(loc.x + 1, loc.y);
	p[2] = CCPointMake(loc.x, loc.y + 1);
	p[3] = CCPointMake(loc.x - 1, loc.y);
	p[4] = CCPointMake(loc.x, loc.y - 1);

	MapCell null_cell;
	null_cell.code = kNull;

	MapCell mapCell[5];
	mapCell[0] = isInScope(p[0]) ? cell(p[0]) : null_cell;
	mapCell[1] = isInScope(p[1]) ? cell(p[1]) : null_cell;
	mapCell[2] = isInScope(p[2]) ? cell(p[2]) : null_cell;
	mapCell[3] = isInScope(p[3]) ? cell(p[3]) : null_cell;
	mapCell[4] = isInScope(p[4]) ? cell(p[4]) : null_cell;

	char param[5];
	memset(param, 0, sizeof(param));
	for (int i = 0; i < 5; i++) {
		if (mapCell[i].code == kNull) {
			param[i] = '0';
		} else {
			param[i] = '1';
		}
	}

	mapCell[0].refleshSprite_adv(param);
}