#include "HelloWorldScene.h"
#pragma execution_character_set("utf-8")
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

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	//创建一张贴图
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	//从贴图中以像素单位切割，创建关键帧
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	//使用第一帧创建精灵
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height / 2));
	addChild(player, 3);

	//hp条
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));
	//使用hp条设置progressBar
	pT = ProgressTimer::create(sp);
	pT->setScaleX(90);
	pT->setAnchorPoint(Vec2(0, 0));
	pT->setType(ProgressTimerType::BAR);
	pT->setBarChangeRate(Point(1, 0));
	pT->setMidpoint(Point(0, 1));
	pT->setPercentage(100);
	pT->setPosition(Vec2(origin.x+14*pT->getContentSize().width,origin.y + visibleSize.height - 2*pT->getContentSize().height));
	addChild(pT,1);
	sp0->setAnchorPoint(Vec2(0, 0));
	sp0->setPosition(Vec2(origin.x + pT->getContentSize().width, origin.y + visibleSize.height - sp0->getContentSize().height));
	addChild(sp0,0);

	// 静态动画
	idle.reserve(1);
	idle.pushBack(frame0);

	// 攻击动画
	attack.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i,0,113,113)));
		attack.pushBack(frame);
	}

	// 死亡动画(帧数：22帧，高：90，宽：79）
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	dead.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		dead.pushBack(frame);
	}

	// 运动动画(帧数：8帧，高：101，宽：68）
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	run.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * ((i + 3) % 8), 0, 68, 101)));
		run.pushBack(frame);
	}

	// 设置左下角的虚拟方向wasd
	auto w_diction = MenuItemLabel::create(Label::createWithTTF("W", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::up_run, this));
	w_diction->setPosition(Vec2(origin.x + 1.5 * w_diction->getContentSize().width, origin.y + 2 * w_diction->getContentSize().height));
	auto w_menu = Menu::create(w_diction, NULL);
	w_menu->setPosition(Vec2::ZERO);
	this->addChild(w_menu, 2);

	auto a_diction = MenuItemLabel::create(Label::createWithTTF("A", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::left_run, this));
	a_diction->setPosition(Vec2(origin.x + a_diction->getContentSize().width, origin.y + a_diction->getContentSize().height));
	auto a_menu = Menu::create(a_diction, NULL);
	a_menu->setPosition(Vec2::ZERO);
	this->addChild(a_menu, 2);
	
	auto s_diction = MenuItemLabel::create(Label::createWithTTF("S", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::down_run, this));
	s_diction->setPosition(Vec2(origin.x + 1.5 * w_diction->getContentSize().width, origin.y + s_diction->getContentSize().height));
	auto s_menu = Menu::create(s_diction, NULL);
	s_menu->setPosition(Vec2::ZERO);
	this->addChild(s_menu, 2);

	auto d_diction = MenuItemLabel::create(Label::createWithTTF("D", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::right_run, this));
	d_diction->setPosition(Vec2(origin.x + 2.5 * w_diction->getContentSize().width, origin.y + d_diction->getContentSize().height));
	auto d_menu = Menu::create(d_diction, NULL);
	d_menu->setPosition(Vec2::ZERO);
	this->addChild(d_menu, 2);

	// 设置右下角的xy行为键
	// 初始化triggering为false
	// 若为false则没有死亡或攻击动画进行，可以按下X或Y发生动作
	// 否则说明已经有动画进行，按下X或Y不能发生响应
	triggering = false;
	auto dead_button = MenuItemLabel::create(Label::createWithTTF("X", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::dying, this));
	dead_button->setPosition(Vec2(origin.x + visibleSize.width - dead_button->getContentSize().width, origin.y + 2 * dead_button->getContentSize().height));
	auto dead_menu = Menu::create(dead_button, NULL);
	dead_menu->setPosition(Vec2::ZERO);
	this->addChild(dead_menu, 2);

	auto attack_button = MenuItemLabel::create(Label::createWithTTF("Y", "fonts/arial.ttf", 36), CC_CALLBACK_1(HelloWorld::attacking, this));
	attack_button->setPosition(Vec2(origin.x + visibleSize.width - 2 * attack_button->getContentSize().width, origin.y + attack_button->getContentSize().height));
	auto attack_menu = Menu::create(attack_button, NULL);
	attack_menu->setPosition(Vec2::ZERO);
	this->addChild(attack_menu, 2);

	// 设置正上方的一个计时器
	// 初始化倒计时时间为180
	dtime = 180;
	char *init_time = new char[5];
	sprintf(init_time, "%d", dtime);
	// 建立一个数字label
	time = Label::createWithTTF(init_time, "fonts/arial.ttf", 36);
	time->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - time->getContentSize().height));
	this->addChild(time, 2);
	// 设置一个间隔时间为1s的调度器用来计时
	schedule(schedule_selector(HelloWorld::update), 1.0f);

	return true;
}

void HelloWorld::update(float dt) {
	--dtime;
	char *dtime_str = new char[5];
	sprintf(dtime_str, "%d", dtime);
	// 更新计时器label的文字
	time->setString(dtime_str);	
	// 如果dtime为0，取消调度器
	if (dtime == 0) {
		unschedule(schedule_selector(HelloWorld::update));
	}
}

void HelloWorld::up_run(cocos2d::Ref* pSender) {
		running(up);
}

void HelloWorld::down_run(cocos2d::Ref* pSender) {
	running(down);
}

void HelloWorld::left_run(cocos2d::Ref* pSender) {
	running(left);
}

void HelloWorld::right_run(cocos2d::Ref* pSender) {
	running(right);
}

void HelloWorld::running(int direction) {
	// 走路的动画
	auto animation = Animation::createWithSpriteFrames(run, 0.03f);
	auto animate = Animate::create(animation);
	// 根据方向判断
	switch (direction) {
		case up:
			// 判断移动后的位置是否出界
			// 若不出界
			if (player->getPosition().y + 30 < origin.y + visibleSize.height) {
				// 建立MoveTo移动动作
				auto move_to = MoveTo::create(0.3f, Vec2(player->getPosition().x, player->getPosition().y + 30));
				// 移动和动画同时发生
				auto my_spawn = Spawn::createWithTwoActions(animate, move_to);
				// 执行Spawn动作
				player->runAction(my_spawn);
			}
			else {	// 若出界，则只执行动画
				player->runAction(animate);
			}
			break;
		case down:
			if (player->getPosition().y - 30 > origin.y) {
				auto move_to = MoveTo::create(0.3f, Vec2(player->getPosition().x, player->getPosition().y - 30));
				auto my_spawn = Spawn::createWithTwoActions(animate, move_to);
				player->runAction(my_spawn);
			}
			else {
				player->runAction(animate);
			}
			break;
		case left:
			if (player->getPosition().x - 30 > origin.x) {
				auto move_to = MoveTo::create(0.3f, Vec2(player->getPosition().x - 30, player->getPosition().y));
				auto my_spawn = Spawn::createWithTwoActions(animate, move_to);
				player->runAction(my_spawn);
			}
			else {
				player->runAction(animate);
			}
			break;
		case right:
			if (player->getPosition().x + 30 < origin.x + visibleSize.width) {
				auto move_to = MoveTo::create(0.3f, Vec2(player->getPosition().x + 30, player->getPosition().y));
				auto my_spawn = Spawn::createWithTwoActions(animate, move_to);
				player->runAction(my_spawn);
			}
			else {
				player->runAction(animate);
			}
			break;
	}
}

void HelloWorld::dying(cocos2d::Ref* pSender) {
	// 先进行判断triggering是否为false
	// 如果是false则可以播放动画
	if (!triggering) {
		// 设置triggering为真，再次按下X或Y时不能同时播放动画
		triggering = true;
		// 血条均匀减少
		float progressTo = pT->getPercentage() - 20;
		float progressFrom = pT->getPercentage();
		CCProgressFromTo *from_to = CCProgressFromTo::create(1.5, progressFrom, progressTo);
		pT->runAction(from_to);
		// 死亡动画
		auto dead_animation = Animation::createWithSpriteFrames(dead, 0.07f);
		auto dead_animate = Animate::create(dead_animation);
		// 静止动画
		auto idle_animation = Animation::createWithSpriteFrames(idle, 0.01f);
		auto idle_animate = Animate::create(idle_animation);

		// 使用回调函数在动画执行完毕后
		// 在动画播放完毕后，将triggering设置为false，允许按下X或Y可以播放对应动画
		auto func = CallFuncN::create(CC_CALLBACK_0(HelloWorld::enable_trigger, this));
		// 序列动画：死亡动画-->静止动画-->回调函数
		auto seq = Sequence::create(dead_animate, idle_animate, func, nullptr);

		player->runAction(seq);
	}
}


void HelloWorld::attacking(cocos2d::Ref* pSender) {
	// 先进行判断triggering是否为false
	// 如果是false则可以播放动画
	if (!triggering) {
		// 设置triggering为真，再次按下X或Y时不能同时播放动画
		triggering = true;
		// 血条均匀增加
		float progressTo = pT->getPercentage() + 20;
		float progressFrom = pT->getPercentage();
		CCProgressFromTo *from_to = CCProgressFromTo::create(1.5, progressFrom, progressTo);
		pT->runAction(from_to);
		// 攻击动画
		auto attatck_animation = Animation::createWithSpriteFrames(attack, 0.07f);
		auto attatck_animate = Animate::create(attatck_animation);
		// 静止动画
		auto idle_animation = Animation::createWithSpriteFrames(idle, 0.01f);
		auto idle_animate = Animate::create(idle_animation);

		// 使用回调函数在动画执行完毕后
		// 在动画播放完毕后，将triggering设置为false，允许按下X或Y可以播放对应动画
		auto func = CallFuncN::create(CC_CALLBACK_0(HelloWorld::enable_trigger, this));
		// 序列动画：攻击动画-->静止动画-->回调函数
		auto seq = Sequence::create(attatck_animate, idle_animate, func, nullptr);

		player->runAction(seq);
	}
}
// 设置触发为false，允许其他动画
void HelloWorld::enable_trigger()
{
	triggering = false;
}



