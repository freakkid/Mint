#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
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
	cocos2d::Label* grade;		// ��ּ�����
	int grade_counts;
	cocos2d::ProgressTimer* pT;
	

	// ���ĸ�����
	enum directions { up, down, left, right } key_directions;
	void up_run(cocos2d::Ref* pSender);
	void down_run(cocos2d::Ref* pSender);
	void left_run(cocos2d::Ref* pSender);
	void right_run(cocos2d::Ref* pSender);
	
	// ��������
	void running(int direction);
	void attacking(cocos2d::Ref* pSender);
	void dying();
	
	// ����X��Y��������ͬʱ����
	bool triggering;		// x��y����ͬʱ���š�����������Ӧwasd�е�һ��������flag
	void enable_trigger();	// ʹtriggeringΪ��

	void create_and_move_monster(float dt);	// �������ƶ�����
	void hitByMonster(float dt);
	int lastCid;			// playerƫת����
};

#endif // __HELLOWORLD_SCENE_H__
