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

	//����һ����ͼ
	auto texture = Director::getInstance()->getTextureCache()->addImage("$lucia_2.png");
	//����ͼ�������ص�λ�и�����ؼ�֡
	auto frame0 = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(0, 0, 113, 113)));
	//ʹ�õ�һ֡��������
	player = Sprite::createWithSpriteFrame(frame0);
	player->setPosition(Vec2(origin.x + visibleSize.width / 2,
							origin.y + visibleSize.height / 2));
	addChild(player, 3);

	//hp��
	Sprite* sp0 = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(0, 320, 420, 47)));
	Sprite* sp = Sprite::create("hp.png", CC_RECT_PIXELS_TO_POINTS(Rect(610, 362, 4, 16)));
	//ʹ��hp������progressBar
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

	// ��̬����
	idle.reserve(1);
	idle.pushBack(frame0);

	// ��������
	attack.reserve(17);
	for (int i = 0; i < 17; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(113 * i,0,113,113)));
		attack.pushBack(frame);
	}

	// ��������(֡����22֡���ߣ�90����79��
	auto texture2 = Director::getInstance()->getTextureCache()->addImage("$lucia_dead.png");
	dead.reserve(22);
	for (int i = 0; i < 22; i++) {
		auto frame = SpriteFrame::createWithTexture(texture2, CC_RECT_PIXELS_TO_POINTS(Rect(79 * i, 0, 79, 90)));
		dead.pushBack(frame);
	}

	// �˶�����(֡����8֡���ߣ�101����68��
	auto texture3 = Director::getInstance()->getTextureCache()->addImage("$lucia_forward.png");
	run.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture3, CC_RECT_PIXELS_TO_POINTS(Rect(68 * ((i + 3) % 8), 0, 68, 101)));
		run.pushBack(frame);
	}

	// �������½ǵ����ⷽ��wasd
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

	// �������½ǵ�xy��Ϊ��
	// ��ʼ��triggeringΪfalse
	// ��Ϊfalse��û�������򹥻��������У����԰���X��Y��������
	// ����˵���Ѿ��ж������У�����X��Y���ܷ�����Ӧ
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

	// �������Ϸ���һ����ʱ��
	// ��ʼ������ʱʱ��Ϊ180
	dtime = 180;
	char *init_time = new char[5];
	sprintf(init_time, "%d", dtime);
	// ����һ������label
	time = Label::createWithTTF(init_time, "fonts/arial.ttf", 36);
	time->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - time->getContentSize().height));
	this->addChild(time, 2);
	// ����һ�����ʱ��Ϊ1s�ĵ�����������ʱ
	schedule(schedule_selector(HelloWorld::update), 1.0f);

	return true;
}

void HelloWorld::update(float dt) {
	--dtime;
	char *dtime_str = new char[5];
	sprintf(dtime_str, "%d", dtime);
	// ���¼�ʱ��label������
	time->setString(dtime_str);	
	// ���dtimeΪ0��ȡ��������
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
	// ��·�Ķ���
	auto animation = Animation::createWithSpriteFrames(run, 0.03f);
	auto animate = Animate::create(animation);
	// ���ݷ����ж�
	switch (direction) {
		case up:
			// �ж��ƶ����λ���Ƿ����
			// ��������
			if (player->getPosition().y + 30 < origin.y + visibleSize.height) {
				// ����MoveTo�ƶ�����
				auto move_to = MoveTo::create(0.3f, Vec2(player->getPosition().x, player->getPosition().y + 30));
				// �ƶ��Ͷ���ͬʱ����
				auto my_spawn = Spawn::createWithTwoActions(animate, move_to);
				// ִ��Spawn����
				player->runAction(my_spawn);
			}
			else {	// �����磬��ִֻ�ж���
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
	// �Ƚ����ж�triggering�Ƿ�Ϊfalse
	// �����false����Բ��Ŷ���
	if (!triggering) {
		// ����triggeringΪ�棬�ٴΰ���X��Yʱ����ͬʱ���Ŷ���
		triggering = true;
		// Ѫ�����ȼ���
		float progressTo = pT->getPercentage() - 20;
		float progressFrom = pT->getPercentage();
		CCProgressFromTo *from_to = CCProgressFromTo::create(1.5, progressFrom, progressTo);
		pT->runAction(from_to);
		// ��������
		auto dead_animation = Animation::createWithSpriteFrames(dead, 0.07f);
		auto dead_animate = Animate::create(dead_animation);
		// ��ֹ����
		auto idle_animation = Animation::createWithSpriteFrames(idle, 0.01f);
		auto idle_animate = Animate::create(idle_animation);

		// ʹ�ûص������ڶ���ִ����Ϻ�
		// �ڶ���������Ϻ󣬽�triggering����Ϊfalse��������X��Y���Բ��Ŷ�Ӧ����
		auto func = CallFuncN::create(CC_CALLBACK_0(HelloWorld::enable_trigger, this));
		// ���ж�������������-->��ֹ����-->�ص�����
		auto seq = Sequence::create(dead_animate, idle_animate, func, nullptr);

		player->runAction(seq);
	}
}


void HelloWorld::attacking(cocos2d::Ref* pSender) {
	// �Ƚ����ж�triggering�Ƿ�Ϊfalse
	// �����false����Բ��Ŷ���
	if (!triggering) {
		// ����triggeringΪ�棬�ٴΰ���X��Yʱ����ͬʱ���Ŷ���
		triggering = true;
		// Ѫ����������
		float progressTo = pT->getPercentage() + 20;
		float progressFrom = pT->getPercentage();
		CCProgressFromTo *from_to = CCProgressFromTo::create(1.5, progressFrom, progressTo);
		pT->runAction(from_to);
		// ��������
		auto attatck_animation = Animation::createWithSpriteFrames(attack, 0.07f);
		auto attatck_animate = Animate::create(attatck_animation);
		// ��ֹ����
		auto idle_animation = Animation::createWithSpriteFrames(idle, 0.01f);
		auto idle_animate = Animate::create(idle_animation);

		// ʹ�ûص������ڶ���ִ����Ϻ�
		// �ڶ���������Ϻ󣬽�triggering����Ϊfalse��������X��Y���Բ��Ŷ�Ӧ����
		auto func = CallFuncN::create(CC_CALLBACK_0(HelloWorld::enable_trigger, this));
		// ���ж�������������-->��ֹ����-->�ص�����
		auto seq = Sequence::create(attatck_animate, idle_animate, func, nullptr);

		player->runAction(seq);
	}
}
// ���ô���Ϊfalse��������������
void HelloWorld::enable_trigger()
{
	triggering = false;
}



