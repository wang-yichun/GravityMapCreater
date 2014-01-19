#include "MapCreateScene.h"
#include "GameLayer.h"
#include "Stage.h"
#include "SystemManager.h"

MapCreate::MapCreate():
	uiWidget(NULL) { }

MapCreate::~MapCreate() {}

CCScene* MapCreate::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MapCreate *layer = MapCreate::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MapCreate::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(MapCreate::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Map Creater for Gravity", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    //// add "MapCreate" splash screen"
    //CCSprite* pSprite = CCSprite::createWithSpriteFrameName("images/art_design_11.png");

    //// position the sprite on the center of the screen
    //pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    //// add the sprite as a child to this layer
    //this->addChild(pSprite, 200, 2);

	// 
	UILayer * uiLayer = UILayer::create();
    
	uiWidget = GUIReader::shareReader()->widgetFromJsonFile("CSProj/map_create_widget.ExportJson");
	UIButton * btn_save = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_save"));
	btn_save -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_save -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_load = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_load"));
	btn_load -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_load -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));

	UIButton * btn_cell_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_null"));
	btn_cell_null -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_null -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_cell_normal = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_normal"));
	btn_cell_normal -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_normal -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_cell_start = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_start"));
	btn_cell_start -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_start -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_cell_end = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_end"));
	btn_cell_end -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_end -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_cell_poll_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_null"));
	btn_cell_poll_null -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_poll_null -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));
	UIButton * btn_cell_poll_red = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_red"));
	btn_cell_poll_red -> addPushDownEvent(this, coco_pushselector(MapCreate::touchBeganEvent));
	btn_cell_poll_red -> addReleaseEvent(this, coco_releaseselector(MapCreate::touchEndEvent));

	uiWidget -> setTag(1);
	uiLayer -> addWidget(uiWidget);
	this -> addChild(uiLayer, 200, 2);

	//ActionObject * ao = ActionManager::shareManager() -> getActionByName("splash_screen.ExportJson", "Animation0");
	//ao -> play();

	GameLayer * gameLayer = GameLayer::create();
	gameLayer -> setPositionY(50);
	this -> addChild(gameLayer, 100, 1);

	Stage::GetInstance() -> setMother(gameLayer);
	Stage::GetInstance() -> resetMap();
	Stage::GetInstance() -> refleshCellShow_adv();

	SystemManager::GetInstance(); // init
	this -> setCurrentCellCodeBtnEnabled();

    return true;
}


void MapCreate::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}


CCLayer * MapCreate::getGameLayer() {
	return dynamic_cast<CCLayer *>(getChildByTag(1));
}

void MapCreate::touchBeganEvent(CCObject *pSender) {
	UIButton * btn = dynamic_cast<UIButton *>(pSender);
	if (btn -> isBright()) {
		CCLOG("touchBeganEvent arg:%s", btn->getName());
		if (string(btn->getName()) == "btn_load") {
			// TODO: LOAD DB
			SystemManager::GetInstance() -> do_load_map();
		} else if (string(btn->getName()) == "btn_save") {
			// TODO: SAVE DB
			SystemManager::GetInstance() -> do_save_map();
		} else if (string(btn->getName()) == "btn_cell_null") {
			SystemManager::GetInstance() -> m_chosedCellCode = kNull; // record btn status.
		} else if (string(btn->getName()) == "btn_cell_normal") {
			SystemManager::GetInstance() -> m_chosedCellCode = kNormal; // record ..
		} else if (string(btn->getName()) == "btn_cell_start") {
			SystemManager::GetInstance() -> m_chosedCellCode = kStart; // record ..
		} else if (string(btn->getName()) == "btn_cell_end") {
			SystemManager::GetInstance() -> m_chosedCellCode = kEnd; // record ..
		} else if (string(btn->getName()) == "btn_cell_poll_null") {
			SystemManager::GetInstance() -> m_chosedCellPollCode = emcpcNull; // record ..
		} else if (string(btn->getName()) == "btn_cell_poll_red") {
			SystemManager::GetInstance() -> m_chosedCellPollCode = emcpcPoll; // record ..
		} 
	} else {
		CCLOG("touchBeganEvent arg:%s (not Bright)", btn->getName());
	}

}

void MapCreate::touchEndEvent(CCObject *pSender) {
	UIButton * btn = dynamic_cast<UIButton *>(pSender);
	if (btn -> isBright()) {
		CCLOG("touchEndEvent arg:%s", btn->getName());
	} else {
		CCLOG("touchEndEvent arg:%s (not Bright)", btn->getName());
	}
	setCurrentCellCodeBtnEnabled();
	setCurrentCellPollCodeBtnEnabled();
}

void MapCreate::setAllCellCodeBtnEnabled(bool enabled) {
	UIButton * btn_cell_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_null"));
	UIButton * btn_cell_normal = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_normal"));
	UIButton * btn_cell_start = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_start"));
	UIButton * btn_cell_end = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_end"));

	btn_cell_null -> setBright(enabled);
	btn_cell_normal -> setBright(enabled);
	btn_cell_start -> setBright(enabled);
	btn_cell_end -> setBright(enabled);
}

void MapCreate::setCurrentCellCodeBtnEnabled() {
	UIButton * btn_cell_start = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_start"));
	UIButton * btn_cell_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_null"));
	UIButton * btn_cell_normal = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_normal"));
	UIButton * btn_cell_end = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_end"));

	setAllCellCodeBtnEnabled(true);
	enumMapCellCode current_chosed_cell_code = SystemManager::GetInstance() -> m_chosedCellCode;
	switch (current_chosed_cell_code) {
	case kNull:
		btn_cell_null -> setBright(false);
		break;
	case kNormal:
		btn_cell_normal -> setBright(false);
		break;
	case  kStart:
		btn_cell_start -> setBright(false);
		break;
	case kEnd:
		btn_cell_end -> setBright(false);
		break;
	default:
		break;
	}
}

void MapCreate::setAllCellPollCodeBtnEnabled(bool enabled) {
	UIButton * btn_cell_poll_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_null"));
	UIButton * btn_cell_poll_red = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_red"));

	btn_cell_poll_null -> setBright(enabled);
	btn_cell_poll_red -> setBright(enabled);
}

void MapCreate::setCurrentCellPollCodeBtnEnabled() {
	UIButton * btn_cell_poll_null = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_null"));
	UIButton * btn_cell_poll_red = dynamic_cast<UIButton *>(uiWidget -> getChildByName("root") -> getChildByName("btn_cell_poll_red"));

	setAllCellPollCodeBtnEnabled(true);
	enumMapCellPollCode current_chosed_cell_poll_code = SystemManager::GetInstance() -> m_chosedCellPollCode;
	switch (current_chosed_cell_poll_code) {
	case emcpcNull:
		btn_cell_poll_null -> setBright(false);
		break;
	case emcpcPoll:
		btn_cell_poll_red -> setBright(false);
		break;
	default:
		break;
	}
}