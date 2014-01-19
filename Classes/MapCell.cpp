#include "MapCell.h"
#include "CreaterConfig.h"

MapCell::MapCell(): primaryNode(NULL), primarySprite(NULL), secondaryNode(NULL), secondarySprite(NULL),
	pollNode(NULL), pollSprite(NULL), parent(NULL), infoTTF(NULL) {}
MapCell::~MapCell() {}

void MapCell::setMapCell(CCPoint loc, enumMapCellCode code) {
	this -> loc = loc;

	if (DEBUG_CELL_INFO_SHOW) {
		stringstream ss;
		ss << loc.x << "," << loc.y << endl;
		ss << code;
		if ( this -> infoTTF != NULL) {
			this -> infoTTF -> setString(ss.str().c_str());
		} else {
			this -> infoTTF = CCLabelTTF::create(ss.str().c_str(),"Arial",10);
			this -> infoTTF -> setColor(ccc3(255,0,0));
		}
		ss.str("");
	}

	if ( this -> primaryNode == NULL) {
		this -> primaryNode = CCNode::create();
	}
	if ( this -> secondaryNode == NULL) {
		this -> secondaryNode = CCNode::create();
	}
	if ( this -> pollNode == NULL) {
		this -> pollNode = CCNode::create();
	}

	this -> setCode(code);
}

void MapCell::setCode(enumMapCellCode _code) {
	this -> code = _code;
	this -> poll_code = emcpcNull;
	if (DEBUG_CELL_INFO_SHOW) {
		stringstream ss;
		ss << loc.x << "," << loc.y << endl;
		ss << code;
		if ( this -> infoTTF != NULL) {
			this -> infoTTF -> setString(ss.str().c_str());
		} else {
			this -> infoTTF = CCLabelTTF::create(ss.str().c_str(),"Arial",10);
			this -> infoTTF -> setColor(ccc3(255,0,0));
		}
		ss.str("");
	}

	refleshSprite();
}

void MapCell::setPollCode(enumMapCellPollCode poll_code) {
	if (this -> poll_code == emcpcNull) {
		this -> poll_code = poll_code;
		pollSprite = CCSprite::createWithSpriteFrameName("mapcell/poll_red.png");
		pollSprite -> setOpacity(0);
		pollSprite -> runAction(CCFadeIn::create(1.0f));
		pollNode -> removeAllChildren();
		pollNode -> addChild(pollSprite);
	}
}

void MapCell::setParent(CCNode *pNode) {
	CCAssert(pNode != NULL, "pNode is NULL.");
	parent = pNode;
}

void MapCell::refleshSprite_adv(char * param) {
	string s1 = "mapcell/obst_";
	string s2 = param[0] == '0' ? "n" : "p";
	stringstream ss3;
	ss3 << param[1] << param[2] << param[3] << param[4];
	string s3 = ss3.str();
	ss3.str("");

	if (s2 == "n") {
		if (s3 == "1000" || s3 == "0100" || s3 == "0010" || s3 == "0001" || s3 == "1010" || s3 == "0101") {
			s3 = "0000";
		}
	} else if (s2 == "p") {
		if (s3 == "1110" || s3 == "0111" || s3 == "1011" || s3 == "1101" || s3 == "1010" || s3 == "0101") {
			s3 = "1111";
		}
		if (s3 == "0000") {
			if (param[5] == '1' && param[6] == '1' && param[7] == '1' && param[8] == '1') {
				s3 = "1111";
			} else if (param[5] == '0' && param[6] == '1' && param[7] == '1' && param[8] == '1') {
				s3 = "0011";
			} else if (param[5] == '1' && param[6] == '0' && param[7] == '1' && param[8] == '1') {
				s3 = "1001";
			} else if (param[5] == '1' && param[6] == '1' && param[7] == '0' && param[8] == '1') {
				s3 = "1100";
			} else if (param[5] == '1' && param[6] == '1' && param[7] == '1' && param[8] == '0') {
				s3 = "0110";
			} 
			else if (param[5] == '1' && param[6] == '1' && param[7] == '0' && param[8] == '0') {
				s3 = "0100";
			} else if (param[5] == '1' && param[6] == '0' && param[7] == '1' && param[8] == '0') {
				s3 = "00001010";
			} else if (param[5] == '1' && param[6] == '0' && param[7] == '0' && param[8] == '1') {
				s3 = "1000";
			} else if (param[5] == '0' && param[6] == '1' && param[7] == '1' && param[8] == '0') {
				s3 = "0010";
			} else if (param[5] == '0' && param[6] == '1' && param[7] == '0' && param[8] == '1') {
				s3 = "00000101";
			} else if (param[5] == '0' && param[6] == '0' && param[7] == '1' && param[8] == '1') {
				s3 = "0001";
			} 
			else if (param[5] == '1' && param[6] == '0' && param[7] == '0' && param[8] == '0') {
				s3 = "00001000";
			} else if (param[5] == '0' && param[6] == '1' && param[7] == '0' && param[8] == '0') {
				s3 = "00000100";
			} else if (param[5] == '0' && param[6] == '0' && param[7] == '1' && param[8] == '0') {
				s3 = "00000010";
			} else if (param[5] == '0' && param[6] == '0' && param[7] == '0' && param[8] == '1') {
				s3 = "00000001";
			} else {

			}
		} else if (s3 == "1000") {
			if (param[6] == '1' && param[7] == '0') {
				s3 = "1100";
			}
			if (param[6] == '0' && param[7] == '1') {
				s3 = "1001";
			}
			if (param[6] == '1' && param[7] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "0100") {
			if (param[7] == '1' && param[8] == '0') {
				s3 = "0110";
			}
			if (param[7] == '0' && param[8] == '1') {
				s3 = "1100";
			}
			if (param[7] == '1' && param[8] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "0010") {
			if (param[5] == '1' && param[8] == '0') {
				s3 = "0110";
			}
			if (param[5] == '0' && param[8] == '1') {
				s3 = "0011";
			}
			if (param[5] == '1' && param[8] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "0001") {
			if (param[5] == '1' && param[6] == '0') {
				s3 = "1001";
			}
			if (param[5] == '0' && param[6] == '1') {
				s3 = "0011";
			}
			if (param[5] == '1' && param[6] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "1100") {
			if (param[7] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "0110") {
			if (param[8] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "0011") {
			if (param[5] == '1') {
				s3 = "1111";
			}
		} else if (s3 == "1001") {
			if (param[6] == '1') {
				s3 = "1111";
			}
		}
	}

	string s4 = ".png";

	string frame_name = s1 + s2 + s3 + s4;

	if (primarySprite == NULL) {
		primarySprite = CCSprite::createWithSpriteFrameName(frame_name.c_str());
		primarySprite -> setAnchorPoint(GetCellCodeAP(code));
		primaryNode -> removeAllChildren();
		primaryNode -> addChild(primarySprite, 10, 1);
	} else {
		primarySprite -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame_name.c_str()));
	}
}

CCPoint MapCell::GetCellCodeAP(enumMapCellCode cell_code) {
	CCPoint ap;
	switch (cell_code) {
	case kNull:
		ap = CCPointMake(.5, .5);
		break;
	case kNormal:
		ap = CCPointMake(.5, .5);
		break;
	case kStart:
		ap = CCPointMake(.25, .5);
		break;
	case kEnd:
		ap = CCPointMake(.25, .5);
		break;
	default:
		ap = CCPointZero;
		break;
	}
	return ap;
}

bool MapCell::GetCellCodeIsNullShow(enumMapCellCode cell_code) {
	bool isNullShow = false;
	switch (cell_code) {
	case kNull:
		isNullShow = true;
		break;
	case kNormal:
		isNullShow = false;
		break;
	case kStart:
		isNullShow = true;
		break;
	case kEnd:
		isNullShow = true;
		break;
	default:
		isNullShow = true;
		break;
	}
	return isNullShow;
}

void MapCell::refleshSprite() {
	string frame_name = "";

	if (secondarySprite != NULL) {
		secondarySprite -> removeFromParent();
		secondarySprite = NULL;
	}

	switch (code) {
	case kNull:{
		frame_name = "";
		break;
			   }
	case kNormal:{
		frame_name = "mapcell/obst_p1111.png"; // no use.
		break;
				 }
	case kStart:{
		frame_name = "mapobj/landing_point.png";
		secondarySprite = CCSprite::createWithSpriteFrameName(frame_name.c_str());
		secondarySprite -> setAnchorPoint(GetCellCodeAP(code));
		secondaryNode -> addChild(secondarySprite, 10, 1);
		break;
				}
	case kEnd:{
		frame_name = "mapobj/landing_point.png";
		secondarySprite = CCSprite::createWithSpriteFrameName(frame_name.c_str());
		secondarySprite -> setAnchorPoint(GetCellCodeAP(code));
		secondaryNode -> addChild(secondarySprite, 10, 1);
		break;
			  }
	default:{
		CCAssert(false, "MapCell::refleshSprite failed: code is unexcepted");
		break;
			}
	}

	if (GetCellCodeIsNullShow(code)) { // 显示非墙,清空primary node;
		if (primarySprite != NULL) {
			primarySprite -> removeFromParent();
			primarySprite = NULL;
		}
	} else { // 显示墙; (这里的墙无法填充包含周边关系的圆角,它在Stage里面调用)
		if (primarySprite == NULL) {
			primarySprite = CCSprite::createWithSpriteFrameName("mapcell/obst_p1111.png");
			primarySprite -> setAnchorPoint(GetCellCodeAP(code));
			primaryNode -> removeAllChildren();
			primaryNode -> addChild(primarySprite, 10, 1);
		} else {
			primarySprite -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frame_name.c_str()));
		}
	}
}