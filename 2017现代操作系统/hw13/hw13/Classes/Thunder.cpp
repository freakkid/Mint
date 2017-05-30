#include "Thunder.h"
#include <algorithm>

USING_NS_CC;

using namespace CocosDenshion;

Scene* Thunder::createScene() {
  // 'scene' is an autorelease object
  auto scene = Scene::create();

  // 'layer' is an autorelease object
  auto layer = Thunder::create();

  // add layer as a child to scene
  scene->addChild(layer);

  // return the scene
  return scene;
}

bool Thunder::init() {
  if (!Layer::init()) {
    return false;
  }

  origin = Director::getInstance()->getVisibleOrigin();
  visibleSize = Director::getInstance()->getVisibleSize();


  isMove = false;  // �Ƿ����ɴ�
  visibleSize = Director::getInstance()->getVisibleSize();

  // ��������
  auto bgsprite = Sprite::create("bg.jpg");
  bgsprite->setPosition(visibleSize / 2);
  bgsprite->setScale(visibleSize.width / bgsprite->getContentSize().width,
                     visibleSize.height / bgsprite->getContentSize().height);
  this->addChild(bgsprite, 0);

  // �����ɴ�
  player = Sprite::create("player.png");
  player->setAnchorPoint(Vec2(0.5, 0.5));
  player->setPosition(visibleSize.width / 2, player->getContentSize().height);
  player->setName("player");
  this->addChild(player, 1);

  // ��ʾ��ʯ���ӵ�����
  enemysNum = Label::createWithTTF("enemys: 0", "fonts/arial.TTF", 20);
  enemysNum->setColor(Color3B(255, 255, 255));
  enemysNum->setPosition(50, 60);
  this->addChild(enemysNum, 3);
  bulletsNum = Label::createWithTTF("bullets: 0", "fonts/arial.TTF", 20);
  bulletsNum->setColor(Color3B(255, 255, 255));
  bulletsNum->setPosition(50, 30);
  this->addChild(bulletsNum, 3);

  addEnemy(5);        // ��ʼ����ʯ
  preloadMusic();     // Ԥ��������
  playBgm();          // ���ű�������
  explosion();        // ������ը֡����

  // ��Ӽ�����
  addTouchListener();
  addKeyboardListener();
  addCustomListener();

  enemy_type = 0;

  // ������
  schedule(schedule_selector(Thunder::update), 0.04f, kRepeatForever, 0);

  return true;
}

//Ԥ���������ļ�
void Thunder::preloadMusic() {
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/bgm.mp3");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/explore.wav");
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/fire.wav");
}

//���ű�������
void Thunder::playBgm() {
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("music/bgm.mp3", true);
}

//��ʼ����ʯ
void Thunder::addEnemy(int n) {
  enemys.clear();
  for (unsigned i = 0; i < 3; ++i) {
    char enemyPath[20];
    sprintf(enemyPath, "stone%d.png", 3 - i);
    double width = visibleSize.width / (n + 1.0),
           height = visibleSize.height - (50 * (i + 1));
    for (int j = 0; j < n; ++j) {
      auto enemy = Sprite::create(enemyPath);
      enemy->setAnchorPoint(Vec2(0.5, 0.5));
      enemy->setScale(0.5, 0.5);
      enemy->setPosition(width * (j + 1), height);
      enemys.push_back(enemy);
      addChild(enemy, 1);
    }
  }
}

// ��ʯ�����ƶ��������µ�һ��(�ӷ���)
void Thunder::newEnemy() {
	// �������е���ʯ���������ƶ�
	for (Sprite* s : enemys) {
		if (s != NULL) {
			s->setPosition(s->getPosition() + Vec2(0, -50));
		}
	}
	// ��������ʯ
	char enemyPath[20];
	sprintf(enemyPath, "stone%d.png", enemy_type + 1);
	double width = visibleSize.width / (5 + 1.0), height = visibleSize.height - 50;
	for (int j = 0; j < 5; ++j) {
		auto enemy = Sprite::create(enemyPath);
		enemy->setAnchorPoint(Vec2(0.5, 0.5));
		enemy->setScale(0.5, 0.5);
		enemy->setPosition(width * (j + 1) - 84, height);
		enemys.push_back(enemy);
		addChild(enemy, 1);
	}
	enemy_type = (enemy_type + 1) % 3;
}

// �ƶ��ɴ�
void Thunder::movePlane(char c) {
	if (isMove == true) {
		switch (movekey) {
		case 'A':
			if (player->getPosition().x - 10 > origin.x) {
				auto move_by = MoveBy::create(0.04f, Vec2(-10, 0));
				player->runAction(move_by);
			}
			break;
		case 'D':
			if (player->getPosition().x + 10 < origin.x + visibleSize.width) {
				auto move_by = MoveBy::create(0.04f, Vec2(10, 0));
				player->runAction(move_by);
			}
			break;
		}
	}
}

//�����ӵ�
void Thunder::fire() {
  auto bullet = Sprite::create("bullet.png");
  bullet->setAnchorPoint(Vec2(0.5, 0.5));
  bullets.push_back(bullet);
  bullet->setPosition(player->getPosition());
  addChild(bullet, 1);
  SimpleAudioEngine::getInstance()->playEffect("music/fire.wav", false);

  // �Ƴ��ɳ���Ļ����ӵ�
  // ����ص��������ӵ��ɳ��߽���Զ��Ƴ�
  bullet->runAction(
	  Sequence::create(
		MoveBy::create(1.0f, Vec2(0, visibleSize.height)),
		CallFuncN::create(this, callfuncN_selector(Thunder::remove_bullet)),	
		nullptr
	 )
  );
}

// �Ƴ��ӵ�
void Thunder::remove_bullet(Node* bullet) {
	bullets.remove((Sprite*)bullet);
	bullet->removeFromParentAndCleanup(true);
}

// �иը����֡
void Thunder::explosion() {
	auto texture = Director::getInstance()->getTextureCache()->addImage("explosion.png");
	explore.reserve(8);
	for (int i = 0; i < 8; i++) {
		auto frame = SpriteFrame::createWithTexture(texture, CC_RECT_PIXELS_TO_POINTS(Rect(187 * (i % 5), i <= 4 ? 0 : 182, 187, 182)));
		explore.pushBack(frame);
	}
}

void Thunder::update(float f) {
  // ʵʱ����ҳ������ʯ���ӵ�����(����ɾ��)
  // Ҫ��������ʾ��ȷ(�ӷ���)
  char str[15];
  sprintf(str, "enemys: %d", enemys.size());
  enemysNum->setString(str);
  sprintf(str, "bullets: %d", bullets.size());
  bulletsNum->setString(str);

  // �ɴ��ƶ�
  if (isMove)
    this->movePlane(movekey);

  static int ct = 0;
  static int dir = 4;
  ++ct;
  if (ct == 120)
    ct = 40, dir = -dir;
  else if (ct == 80) {
    dir = -dir;
    newEnemy();  // ��ʯ�����ƶ��������µ�һ��(�ӷ���)
  }
  else if (ct == 20)
    ct = 40, dir = -dir;

  //��ʯ�����ƶ�
  for (Sprite* s : enemys) {
    if (s != NULL) {
      s->setPosition(s->getPosition() + Vec2(dir, 0));
    }
  }

  // �ַ��Զ����¼�
  EventCustom e("meet");
  _eventDispatcher->dispatchEvent(&e);
}

// �Զ�����ײ�¼�
void Thunder::meet(EventCustom * event) {
	// �ж��ӵ��Ƿ������ʯ��ִ�ж�Ӧ����
	for (list<Sprite*>::iterator itor = bullets.begin(); itor != bullets.end(); ) {
		bool is_explore = false; // �ж��Ƿ���ײ
 		for (list<Sprite*>::iterator e_itor = enemys.begin(); e_itor != enemys.end(); e_itor++) {
			if ((*itor)->getPosition().getDistance((*e_itor)->getPosition()) < 25) {
				// ��ʯ��ը
				Sprite *enemy = (*e_itor);
				enemy->runAction(
					Sequence::create(
						Animate::create(
							Animation::createWithSpriteFrames(explore, 0.05, 1)
						),
						CallFunc::create([enemy] {
							enemy->removeFromParentAndCleanup(true);
						}),
						nullptr
					)
				);
				// �Ƴ���ʯ
				enemys.erase(e_itor);
				// ���ű�ը��Ч
				SimpleAudioEngine::getInstance()->playEffect("music/explore.wav", false);
				is_explore = true;
				break;
			}
		}
		// ����ʯ��ը���Ƴ����ӵ�
		if (is_explore == true) {
			(*itor)->removeFromParentAndCleanup(true);
			itor = bullets.erase(itor);
		}
		else {
			itor++;
		}
		
	}

	// �ж���Ϸ�Ƿ������ִ�ж�Ӧ����
	for (list<Sprite*>::iterator itor = enemys.begin(); itor != enemys.end(); itor++) {
		// ��ʯλ�ñ仯
		if ((*itor)->getPosition().y < 50) {
			// ����game over
			auto game_over = Sprite::create("gameOver.png");
			game_over->setPosition(Vec2(origin.x + visibleSize.width / 2,
												origin.y + visibleSize.height / 2));
			this->addChild(game_over, 2);
			// �ɴ���ը
			Sprite *temp = player;
			player->runAction(
				Sequence::create(
					Animate::create(
						Animation::createWithSpriteFrames(explore, 0.05, 1)
					),
					CallFunc::create([temp] {
						temp->removeFromParentAndCleanup(true);
					}),
					nullptr
				)
			);
			unschedule(schedule_selector(Thunder::update));  // ȡ��������
			_eventDispatcher->removeAllEventListeners();	// �Ƴ�������
		}
	}
}

// ����Զ��������
void Thunder::addCustomListener() {
	auto meetListener = EventListenerCustom::create("meet", CC_CALLBACK_1(Thunder::meet, this));
	_eventDispatcher->addEventListenerWithFixedPriority(meetListener, 1);
}

// ��Ӽ����¼�������
void Thunder::addKeyboardListener() {
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Thunder::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Thunder::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);	// ע��ַ���
}

void Thunder::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
  switch (code) {
  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_CAPITAL_A:
  case EventKeyboard::KeyCode::KEY_A:
    movekey = 'A';
    isMove = true;
    break;
  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_CAPITAL_D:
  case EventKeyboard::KeyCode::KEY_D:
    movekey = 'D';
    isMove = true;
    break;
  case EventKeyboard::KeyCode::KEY_SPACE:
    fire();
    break;
  }
}

void Thunder::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
  switch (code) {
  case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
  case EventKeyboard::KeyCode::KEY_A:
  case EventKeyboard::KeyCode::KEY_CAPITAL_A:
  case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
  case EventKeyboard::KeyCode::KEY_D:
  case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    isMove = false;
    break;
  }
}

// ��Ӵ����¼�������
void Thunder::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Thunder::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Thunder::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Thunder::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, player);
}

 bool Thunder::onTouchBegan(Touch *touch, Event *event) {
	fire();
	// �ж��Ƿ��ƶ��ɴ�
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	if (rect.containsPoint(locationInNode)) {
		isClick = true;
		return true;
	}
	return false;
}

void Thunder::onTouchEnded(Touch *touch, Event *event) {
  isClick = false;
}

// ����갴ס�ɴ���ɿ��Ʒɴ��ƶ� (�ӷ���)
void Thunder::onTouchMoved(Touch *touch, Event *event) {
	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Vec2 delta = touch->getDelta();
	Vec2 currentPosition = target->getPosition();
	Vec2 newPosition = Vec2(delta.x + currentPosition.x, currentPosition.y);
	if (newPosition.x > origin.x && newPosition.x < origin.x + visibleSize.width) {
		target->setPosition(newPosition);
	}
}
