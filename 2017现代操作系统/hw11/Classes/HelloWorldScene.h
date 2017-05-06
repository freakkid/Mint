#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//void update(float dt) override;
private:
	cocos2d::Sprite* player;
	cocos2d::Vector<SpriteFrame*> attack;
	cocos2d::Vector<SpriteFrame*> dead;
	cocos2d::Vector<SpriteFrame*> run;
	cocos2d::Vector<SpriteFrame*> idle;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Label* time;
	int dtime;
	cocos2d::ProgressTimer* pT;

	
	void update(float dt);	// ��������update���������ڵ���ʱ

	// ���ĸ�����
	enum directions { up, down, left, right } key_directions;
	void up_run(cocos2d::Ref* pSender);
	void down_run(cocos2d::Ref* pSender);
	void left_run(cocos2d::Ref* pSender);
	void right_run(cocos2d::Ref* pSender);
	
	// ��������
	void running(int direction);
	void attacking(cocos2d::Ref* pSender);
	void dying(cocos2d::Ref* pSender);
	
	// ����X��Y��������ͬʱ����
	bool triggering;		// X��Y��������ͬʱ���ŵ�flag
	void enable_trigger();	// ʹtriggeringΪ��
};

#endif // __HELLOWORLD_SCENE_H__
