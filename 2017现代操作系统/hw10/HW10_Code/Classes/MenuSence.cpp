#include "MenuSence.h"
#include "GameSence.h"
USING_NS_CC;

Scene* MenuSence::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuSence::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuSence::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg_sky = Sprite::create("menu-background-sky.jpg");
	bg_sky->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
	this->addChild(bg_sky, 0);

	auto bg = Sprite::create("menu-background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(bg, 0);

	auto title = Sprite::create("gold-miner-text.png");
	title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 120));
	this->addChild(title, 1);

	auto miner = Sprite::create("menu-miner.png");
	miner->setPosition(Vec2(150 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(miner, 1);

	auto leg = Sprite::createWithSpriteFrameName("miner-leg-0.png");
	Animate* legAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("legAnimation"));
	leg->runAction(RepeatForever::create(legAnimate));
	leg->setPosition(110 + origin.x, origin.y + 102);
	this->addChild(leg, 1);

	auto gold = Sprite::create("menu-start-gold.png");
	gold->setPosition(Vec2(visibleSize.width / 2 + origin.x + 270, visibleSize.height / 2 + origin.y -180));
	this->addChild(gold, 1);

	auto startClickItem = MenuItemImage::create(
											"start-0.png",
											"start-1.png",
											CC_CALLBACK_1(MenuSence::gameStart, this));
	
	startClickItem->setPosition(Vec2(visibleSize.width / 2 + origin.x + 280, visibleSize.height / 2 + origin.y - 130));
	auto menu = Menu::create(startClickItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    return true;
}

void MenuSence::gameStart(cocos2d::Ref* pSender)
{
	auto gameSence = GameSence::createScene();
	// 创建一个随机方格消失的过渡动画
	CCTransitionScene *reScene = CCTransitionTurnOffTiles::create(2.0f, gameSence);
	Director::getInstance()->replaceScene(reScene);
}


