#ifndef __MAPCREATE_SCENE_H__
#define __MAPCREATE_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MapCreate : public cocos2d::CCLayer
{
private:
	MapCreate();
	~MapCreate();

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(MapCreate);

public:
	CCLayer * getGameLayer();

	UIWidget * uiWidget;

	void touchBeganEvent(CCObject *pSender);
	void touchEndEvent(CCObject *pSender);

	void setAllCellCodeBtnEnabled(bool enabled);
	void setCurrentCellCodeBtnEnabled();
};

#endif // __MAPCREATE_SCENE_H__
