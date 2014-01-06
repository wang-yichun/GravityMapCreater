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
			if ( (x + y) % 2 == 0) {
				mc.setMapCell(CCPointMake(x,y), kNormal);
			} else {
				mc.setMapCell(CCPointMake(x,y), kNull);
			}

			m_Map.push_back(mc);
			
			if (mc.primarySprite != NULL) {
				CCPoint pos = loc2pos(CCPointMake(x,y));
				CCLOG( "(%d,%d) - (%f,%f)", x ,y , pos.x, pos.y );
				mc.primarySprite -> setPosition(pos);
				m_mother -> addChild(mc.primarySprite, 100);
				mc.infoTTF -> setPosition(pos);
				m_mother -> addChild(mc.infoTTF, 110);
			}
		}
	}
}

