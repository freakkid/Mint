#pragma execution_character_set("utf-8")
#include "FriendShip.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#define database UserDefault::getInstance()

USING_NS_CC;
using namespace CocosDenshion;

void FriendShip::setPhysicsWorld(PhysicsWorld* world) { m_world = world; }

Scene* FriendShip::createScene() {
	srand((unsigned)time(NULL));
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setAutoStep(true);

	// Debug 模式
	// 开启debug模式需要setAutoStep() 并注释掉update函数第一行
	 scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, -300.0f));
	auto layer = FriendShip::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool FriendShip::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	preloadMusic(); // 预加载音效

	addSprite();    // 添加背景和各种精灵
	addListener();  // 添加监听器
	addPlayer();    // 添加玩家

					// 添加调度器
	schedule(schedule_selector(FriendShip::update), 0.01f, kRepeatForever, 0.1f);
	schedule(schedule_selector(FriendShip::boxFall), 4.0f, kRepeatForever, 0);
	schedule(schedule_selector(FriendShip::updateShip), 0.01f, kRepeatForever, 0);

	deltaH = 0;    // 每次更新的高度变化量
	height = 0;    // 左右高度差

	return true;
}

// 预加载音效
void FriendShip::preloadMusic() {
	auto sae = SimpleAudioEngine::getInstance();
	sae->preloadEffect("boxfall.mp3");
	sae->preloadEffect("gameover.mp3");
	sae->preloadEffect("jump.mp3");
	sae->preloadBackgroundMusic("bgm.mp3");

	sae->playBackgroundMusic("bgm.mp3", true);
}

// 添加背景和各种精灵
void FriendShip::addSprite() {
	// add background
	auto bgSprite = Sprite::create("bg.png");
	bgSprite->setPosition(visibleSize / 2);
	bgSprite->setScale(visibleSize.width / bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite, 0);

	// add ship
	ship = Sprite::create("ship.png");
	ship->setScale(visibleSize.width / ship->getContentSize().width * 0.97, 1.2f);
	ship->setPosition(visibleSize.width / 2, 110);
	auto shipbody = PhysicsBody::createBox(ship->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 1.0f));
	shipbody->setCategoryBitmask(0xFFFFFFFF);
	shipbody->setCollisionBitmask(0xFFFFFFFF);
	shipbody->setContactTestBitmask(0xFFFFFFFF);
	shipbody->setDynamic(false);  // 静态刚体不受重力影响, 同时也无法发生倾斜了
	ship->setPhysicsBody(shipbody);
	this->addChild(ship, 1);

	// add sea
	auto seaSprite = Sprite::create("sea.png");
	seaSprite->setPosition(visibleSize.width / 2, 60);
	seaSprite->setScale(visibleSize.width / seaSprite->getContentSize().width, 120 / seaSprite->getContentSize().height);
	seaSprite->setOpacity(230);
	this->addChild(seaSprite, 3);

	// add sun and cloud
	auto sunSprite = Sprite::create("sun.png");
	sunSprite->setPosition(rand() % (int)(visibleSize.width - 200) + 100, 550);
	this->addChild(sunSprite);
	auto cloudSprite1 = Sprite::create("cloud.png");
	cloudSprite1->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
	this->addChild(cloudSprite1);
	auto cloudSprite2 = Sprite::create("cloud.png");
	cloudSprite2->setPosition(rand() % (int)(visibleSize.width - 200) + 100, rand() % 100 + 450);
	this->addChild(cloudSprite2);
}

// 添加监听器
void FriendShip::addListener() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(FriendShip::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(FriendShip::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(FriendShip::onConcactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// 创建角色
void FriendShip::addPlayer() {
	IsPlayer1Jump = false;
	IsPlayer1Left = false;
	IsPlayer1Right = false;
	IsPlayer1Hold = false;
	IsWantToHold = false;
	LastPlayer1Press = 'D';

	//create player1
	auto texture1 = Director::getInstance()->getTextureCache()->addImage("player1.png");
	frame1 = SpriteFrame::createWithTexture(texture1, CC_RECT_PIXELS_TO_POINTS(Rect(0, 4, 32, 36)));
	player1 = Sprite::createWithSpriteFrame(frame1);
	int xpos = visibleSize.width / 2;
	player1->setPosition(Vec2(xpos, 185));
	player1->setTag(10);

	// 设置角色刚体属性
	auto physicsBody = PhysicsBody::createBox(Size(player1->getContentSize().width - 2, player1->getContentSize().height), PhysicsMaterial(20.0f, 0.0f, 1.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(0x0005); // 0101
	physicsBody->setCollisionBitmask(0x0005);
	physicsBody->setContactTestBitmask(0x0005);
	physicsBody->setRotationEnable(false);	// 禁止旋转
	player1->setPhysicsBody(physicsBody);

	player1->setName("player1");
	this->addChild(player1, 2);

	loadAnimation("player1"); // 加载人物动画

	// 人物出场特效 ---> 粒子系统 太阳粒子
	CCParticleSun *particle = CCParticleSun::create();
	particle->setPosition(Vec2(xpos, 180));
	particle->setDuration(1);
	this->addChild(particle, 2);
}

//加载玩家动画帧, 共8种 :)
void FriendShip::loadAnimation(string filepath) {
	Vector<SpriteFrame*> PlayerIdleWithBox;
	Vector<SpriteFrame*> PlayerIdleWithoutBox;
	Vector<SpriteFrame*> PlayerPutUp;
	Vector<SpriteFrame*> PlayerPutDown;
	Vector<SpriteFrame*> PlayerRunWithBox;
	Vector<SpriteFrame*> PlayerRunWithoutBox;
	Vector<SpriteFrame*> PlayerJumpWithBox;
	Vector<SpriteFrame*> PlayerJumpWithoutBox;

	auto PlayerImage = Director::getInstance()->getTextureCache()->addImage(filepath + ".png");

	PlayerIdleWithoutBox.reserve(3);
	for (int i = 0; i < 3; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 5, 32, 36)));
		PlayerIdleWithoutBox.pushBack(frame);
	}
	Animation* PlayerIdelWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerIdleWithoutBox, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerIdelWithoutBoxAnimation, filepath + "IdleWithoutBoxAnimation");

	PlayerIdleWithBox.reserve(3);
	auto IdleWithBox = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96, 7, 32, 36)));
	PlayerIdleWithBox.pushBack(IdleWithBox);
	if (filepath == "player1")
		IdleWithBox1 = IdleWithBox;
	else IdleWithBox2 = IdleWithBox;
	for (int i = 1; i < 3; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96 + 32 * i, 7, 32, 33)));
		PlayerIdleWithBox.pushBack(frame);
	}
	Animation* PlayerIdleWithBoxAnimation = Animation::createWithSpriteFrames(PlayerIdleWithBox, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerIdleWithBoxAnimation, filepath + "IdleWithBoxAnimation");

	for (int i = 0; i < 3; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(96 + 32 * i, 4, 32, 36)));
		PlayerPutUp.pushBack(frame);
	}
	Animation* PlayerPutUpAnimation = Animation::createWithSpriteFrames(PlayerPutUp, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerPutUpAnimation, filepath + "PutUpAnimation");

	for (int i = 0; i < 2; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(193 + 32 * i, 4, 32, 36)));
		PlayerPutDown.pushBack(frame);
	}
	if (filepath == "player1")
		PlayerPutDown.pushBack(frame1);
	else
		PlayerPutDown.pushBack(frame2);
	Animation* PlayerPutDownAnimation = Animation::createWithSpriteFrames(PlayerPutDown, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerPutDownAnimation, filepath + "PutDownAnimation");

	PlayerRunWithoutBox.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 41, 32, 36)));
		PlayerRunWithoutBox.pushBack(frame);
	}

	Animation* PlayerRunWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerRunWithoutBox, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerRunWithoutBoxAnimation, filepath + "RunWithoutBoxAnimation");

	PlayerRunWithBox.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(32 * i, 81, 32, 36)));
		PlayerRunWithBox.pushBack(frame);
	}
	Animation* PlayerRunWithBoxAnimation = Animation::createWithSpriteFrames(PlayerRunWithBox, 0.1f);
	AnimationCache::getInstance()->addAnimation(PlayerRunWithBoxAnimation, filepath + "RunWithBoxAnimation");

	PlayerJumpWithoutBox.pushBack(SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(64, 41, 32, 36))));
	if (filepath == "player1")
		PlayerJumpWithoutBox.pushBack(frame1);
	else
		PlayerJumpWithoutBox.pushBack(frame2);
	Animation* PlayerJumpWithoutBoxAnimation = Animation::createWithSpriteFrames(PlayerJumpWithoutBox, 1.0f);
	AnimationCache::getInstance()->addAnimation(PlayerJumpWithoutBoxAnimation, filepath + "JumpWithoutBoxAnimation");

	PlayerJumpWithBox.pushBack(SpriteFrame::createWithTexture(PlayerImage, CC_RECT_PIXELS_TO_POINTS(Rect(64, 81, 32, 36))));
	PlayerJumpWithBox.pushBack(IdleWithBox);
	Animation* PlayerJumpWithBoxAnimation = Animation::createWithSpriteFrames(PlayerJumpWithBox, 1.0);
	AnimationCache::getInstance()->addAnimation(PlayerJumpWithBoxAnimation, filepath + "JumpWithBoxAnimation");
}

PhysicsBody *FriendShip::getNearBox() {
	Rect boundingBox = player1->getBoundingBox();
	for (PhysicsBody* b : boxes) {
		if ((Sprite*)(b->getOwner())) {
			joint1 = PhysicsJointDistance::construct(
				((Sprite*)holdbox1)->getPhysicsBody(), player1->getPhysicsBody(),
				((Sprite*)holdbox1)->getAnchorPoint(), player1->getAnchorPoint()
			);
			m_world->addJoint(joint1);
			return NULL;
		}
			
	}
	return NULL;
}

void FriendShip::update(float dt) {
	// this->getScene()->getPhysicsWorld()->setAutoStep(false);
//	scheduleUpdate();

	//for (int i = 0; i < 3; i++)
		//this->getScene()->getPhysicsWorld()->step(1 / 100.0f);

	// 玩家1是否在举着箱子的情况下 左右移动
	if (IsPlayer1Left || IsPlayer1Right) {
		if (player1->getSpriteFrame() == frame1) {
			auto animation = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("player1RunWithoutBoxAnimation")));
			animation->setTag(11);
			player1->runAction(animation);
		}
		else if (player1->getSpriteFrame() == IdleWithBox1) {
			auto animation = RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("player1RunWithBoxAnimation")));
			animation->setTag(11);
			player1->runAction(animation);
		}
		// 移动动作
		if (IsPlayer1Left && player1->getPosition().x - 3 > origin.x) {
			auto moveBy = MoveBy::create(0.01f, Vec2(-1, 0));
			moveBy->setTag(12);
			player1->runAction(moveBy);
		}
		else if (IsPlayer1Right && player1->getPosition().x + 3 < origin.x + visibleSize.width) {
			auto moveBy = MoveBy::create(0.01f, Vec2(1, 0));
			moveBy->setTag(12);
			player1->runAction(moveBy);
		}
	}

	if (IsPlayer1Jump) {
		player1->getPhysicsBody()->setVelocity(Vec2(0, player1->getPosition().y + 50));
		IsPlayer1Jump = false;
	}
}

// 更新船的平衡和倾斜(加分项)
// Todo
void FriendShip::updateShip(float dt) {
	return;
}


// 掉落箱子
// 设置掩码使箱子掉落过程不会砸到玩家
// 为了增加难度，箱子将掉落在船重的一端
// Todo
void FriendShip::boxFall(float dt) {
	auto box = Sprite::create("box.png");
	// 为箱子设置刚体属性
	auto physicsBody = PhysicsBody::createBox(box->getContentSize(), PhysicsMaterial(100.0f, 0.0f, 100000.0f));
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(0x0002);	// 0010
	physicsBody->setCollisionBitmask(0x0002);
	physicsBody->setContactTestBitmask(0x0002);
	physicsBody->setRotationEnable(false);
	physicsBody->setMass(100000000);
	box->setPhysicsBody(physicsBody);
	box->setTag(20);


	// 掉落在重的一侧
	if (height > 0)       // 左右高度差大于0(左边重)
		box->setPosition(rand() % (int)(visibleSize.width / 2 - 50) + 50, visibleSize.height);
	else if (height < 0)  // 左右高度差小于0(右边重)
		box->setPosition(rand() % (int)(visibleSize.width / 2 - 50) + visibleSize.width / 2, visibleSize.height);
	else
		box->setPosition(rand() % (int)(visibleSize.width - 100) + 50, visibleSize.height);
	// boxes.push_back(boxbody);
	this->addChild(box);
}


// 上左右 举起箱子 扔掉箱子
void FriendShip::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	Action* animation;
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		// 左右移动
		if (code == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
			IsPlayer1Left = true;
			if (LastPlayer1Press == 'D') {
				LastPlayer1Press = 'A';
				player1->setFlippedX(true);
			}
		}
		else {
			IsPlayer1Right = true;
			if (LastPlayer1Press == 'A') {
				LastPlayer1Press = 'D';
				player1->setFlippedX(false);
			}
		}
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		// 跳
		if (player1->getPhysicsBody()->getVelocity().getDistance(Vec2(0, 0)) - 0 < 0.0001) {
			IsPlayer1Jump = true;
		}
		break;

		// 使用固定距离关节
	case cocos2d::EventKeyboard::KeyCode::KEY_ENTER:
		// 举起或扔掉箱子
		// IsHold == true --->要求扔掉箱子
		// IsHold == false && holdbox != nullptr
		if (IsPlayer1Hold == false && holdbox1 != nullptr) {
			auto moveTo = MoveTo::create(0.2f, Vec2(player1->getPosition().x,
				player1->getPosition().y + ((Sprite*)holdbox1)->getContentSize().height + 100));
			auto createJoint = CallFunc::create([=] {
				/*joint1 = PhysicsJointDistance::construct(
					((Sprite*)holdbox1)->getPhysicsBody(), player1->getPhysicsBody(),
					((Sprite*)holdbox1)->getAnchorPoint(), player1->getAnchorPoint()
				);
				m_world->addJoint(joint1);*/

			});

			((Sprite*)holdbox1)->runAction(Sequence::create(moveTo, createJoint, nullptr));

		}
		//else if (IsPlayer1Hold)
		
		break;
	default:
		break;
	}
}

// 释放按键
void FriendShip::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
	switch (code) {
	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		if (code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			IsPlayer1Left = false;
		else
			IsPlayer1Right = false;

		// 停止动画和运动
		player1->stopAllActions();
		if (IsPlayer1Hold == true) {

		}
		else {
			player1->setSpriteFrame(frame1);
			if (LastPlayer1Press == 'A')
				player1->setFlippedX(true);
		}
		break;

	default:
		break;
	}
}

// 箱子碰到船或者碰到其他箱子之后改变掩码，可以与玩家发生碰撞
// Todo
bool FriendShip::onConcactBegin(PhysicsContact & contact) {
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	// holdbox1 = nullptr;
	//	player1->getBoundingBox().intersectsRect(player1->getBoundingBox());
	if (nodeA && nodeB) {
		if (nodeA->getPhysicsBody()->getCategoryBitmask() == 0x0002) {
			nodeA->getPhysicsBody()->setCategoryBitmask(0x0003);	// 0011
			nodeA->getPhysicsBody()->setCollisionBitmask(0x0003);
			nodeA->getPhysicsBody()->setContactTestBitmask(0x0003);
		}
		else if (nodeB->getPhysicsBody()->getCategoryBitmask() == 0x0002) {
			nodeB->getPhysicsBody()->setCategoryBitmask(0x0003);	// 0011
			nodeB->getPhysicsBody()->setCollisionBitmask(0x0003);
			nodeB->getPhysicsBody()->setContactTestBitmask(0x0003);
		}
		
		if (nodeA->getTag() == 10 && nodeB->getTag() == 20) {
			nodeA->getPhysicsBody()->setVelocity(Vec2(0, 0));
			holdbox1 = nodeB;
		}
		else if (nodeB->getTag() == 10 && nodeA->getTag() == 20) {
			nodeB->getPhysicsBody()->setVelocity(Vec2(0, 0));
			holdbox1 = nodeA;
			// log("%f", ((Sprite*)nodeA)->getPosition().getDistance(((Sprite*)nodeA)->getPosition())
		}
		else {
			holdbox1 = nullptr;
		}

	}

	return true;
}

// 游戏结束, 小船说翻就翻
void FriendShip::GameOver() {
	unschedule(schedule_selector(FriendShip::updateShip));
	unschedule(schedule_selector(FriendShip::boxFall));
	//  unschedule(schedule_selector(FriendShip::update));
	SimpleAudioEngine::getInstance()->stopBackgroundMusic("bgm.mp3");
	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3", false);

	auto label1 = Label::createWithTTF("单身狗独木舟说沉就沉", "fonts/STXINWEI.TTF", 60);
	label1->setColor(Color3B(0, 0, 0));
	label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label1);

	auto label2 = Label::createWithTTF("重玩", "fonts/STXINWEI.TTF", 40);
	label2->setColor(Color3B(0, 0, 0));
	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(FriendShip::replayCallback, this));
	Menu* replay = Menu::create(replayBtn, NULL);
	replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
	this->addChild(replay);

	auto label3 = Label::createWithTTF("退出 ", "fonts/STXINWEI.TTF", 40);
	label3->setColor(Color3B(0, 0, 0));
	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(FriendShip::exitCallback, this));
	Menu* exit = Menu::create(exitBtn, NULL);
	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
	this->addChild(exit);
}

// 继续或重玩按钮响应函数
void FriendShip::replayCallback(Ref * pSender) {
	Director::getInstance()->replaceScene(FriendShip::createScene());
}

// 退出
void FriendShip::exitCallback(Ref * pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
