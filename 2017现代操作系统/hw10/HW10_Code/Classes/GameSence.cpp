#include "GameSence.h"

USING_NS_CC;

Scene* GameSence::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameSence::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameSence::init()
{

	if (!Layer::init())
	{
		return false;
	}

	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameSence::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 设置背景
	auto bg = Sprite::create("level-background-0.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(bg, 0);

	// 设置石头层
	stoneLayer = Layer::create();
	stoneLayer->ignoreAnchorPointForPosition(true);
	stoneLayer->setPosition(Vec2(origin.x, origin.y));
	this->addChild(stoneLayer, 2);
	// 放一个石头
	stone = Sprite::create("stone.png");
	stone->setPosition(Vec2(origin.x + 560, origin.y + 480));
	stoneLayer->addChild(stone, 0);

	// 设置老鼠层
	mouseLayer = Layer::create();
	mouseLayer->ignoreAnchorPointForPosition(true);
	mouseLayer->setPosition(Vec2(origin.x, origin.y + visibleSize.height / 2));
	this->addChild(mouseLayer, 1);
	// 老鼠动图
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("level-sheet.plist");
	char frameName[20];
	Animation* mouseAnimation = Animation::create();
	// 加载序列帧动画
	for (int i = 0; i < 8; i++)
	{
		sprintf(frameName, "gem-mouse-%d.png", i);
		mouseAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	mouseAnimation->setDelayPerUnit(0.1);
	AnimationCache::getInstance()->addAnimation(mouseAnimation, "mouseAnimation");
	// 放一只老鼠
	mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
	Animate* mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
	mouse->runAction(RepeatForever::create(mouseAnimate));
	mouse->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y));
	mouseLayer->addChild(mouse, 1);
	
	// 设置发射的"shoot"
	auto shoot = MenuItemFont::create("Shoot", CC_CALLBACK_1(GameSence::shootStone, this));
	shoot->setFontSizeObj(80);
	shoot->setPosition(Vec2(visibleSize.width / 2 + origin.x + 270, visibleSize.height / 2 + origin.y + 150));
	auto menu = Menu::create(shoot, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// 添加一个会自己原地旋转的钻石图片
	auto diamond = Sprite::create("diamond.png");
	diamond->setPosition(Vec2(visibleSize.width / 2 + origin.x + 250, visibleSize.height / 2 + origin.y + 130));
	auto rotateTo = RotateBy::create(1.0f, 30.0f);
	RepeatForever *repeatForever = RepeatForever::create(rotateTo);
	diamond->runAction(repeatForever);
	this->addChild(diamond, 1);

	return true;
}

bool GameSence::onTouchBegan(Touch *touch, Event *unused_event) {

	auto location = touch->getLocation();
	// 获得触摸点的本地坐标
	CCPoint point = mouseLayer->convertToNodeSpace(location);
	// 放一个奶酪
	auto cheese = Sprite::create("cheese.png");
	cheese->setPosition(point);
	mouseLayer->addChild(cheese, 0);
	// 奶酪逐渐消失
	auto fadeOut = FadeOut::create(4.0f);
	cheese->runAction(fadeOut);
	// 老鼠跑向奶酪
	auto moveTo = MoveTo::create(1, point);
	mouse->runAction(moveTo);
	return true;
}

void GameSence::shootStone(cocos2d::Ref* pSender) {
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto shootingStone = Sprite::create("stone.png");
	// 石头初始位置
	shootingStone->setPosition(Vec2(origin.x + 560, origin.y + 480));
	stoneLayer->addChild(shootingStone, 0);
	// 石头发射到老鼠所在的位置
	// 先转换成世界坐标，再转换成本地坐标
	CCPoint mouseWorldPosition = mouseLayer->convertToWorldSpace(mouse->getPosition());
	CCPoint mouseNodePosition = stoneLayer->convertToNodeSpace(mouseWorldPosition);
	auto moveTo = MoveTo::create(0.8, mouseNodePosition);
	shootingStone->runAction(moveTo);
	// 石头逐渐消失
	auto fadeOut = FadeOut::create(4.0f);
	shootingStone->runAction(fadeOut);

	// 老鼠留下钻石
	auto diamond = Sprite::create("diamond.png");
	diamond->setPosition(mouse->getPosition());
	mouseLayer->addChild(diamond, 1);
	// 老鼠跑开到随机的位置
	// 由于老鼠层的原点坐标是(0, 屏幕高度一半)
	// 让老鼠在屏幕可见范围内移动到随机位置
	CCPoint moveToPoint = Vec2(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height - visibleSize.height / 2);
	auto mouseMoveTo = MoveTo::create(0.8, moveToPoint);
	mouse->runAction(mouseMoveTo);
}