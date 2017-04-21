#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	isClicked = false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto clickItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::clickbutton_event, this));
    
	clickItem->setPosition(Vec2(origin.x + visibleSize.width - clickItem->getContentSize().width/2,
						origin.y + clickItem->getContentSize().height/2));
	auto menu = Menu::create(clickItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    
	auto *nameString = Dictionary::createWithContentsOfFile("NAME.xml");
	const char *name = ((String*)nameString->objectForKey("name"))->getCString();
	auto *nameLabel = Label::create(name, "Arial", 36);
	nameLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - 2 * nameLabel->getContentSize().height));

	const char *num = ((String*)nameString->objectForKey("num"))->getCString();
	auto *numLabel = Label::create(num, "Arial", 36);
	numLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - numLabel->getContentSize().height));

	this->addChild(nameLabel, 1);
	this->addChild(numLabel, 1);


    auto sprite = Sprite::create("01.jpg");

    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::clickbutton_event(Ref* pSender)
{
	if (!isClicked) {
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto *clickLabel = Label::create("You click me!!!", "Arial", 36);
		clickLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - 4 * clickLabel->getContentSize().height));
		this->addChild(clickLabel, 1);
		isClicked = true;
	}
	
}
