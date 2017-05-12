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
	cocos2d::Label* grade;		// 打怪计数器
	int grade_counts;
	cocos2d::ProgressTimer* pT;
	

	// 跑四个方向
	enum directions { up, down, left, right } key_directions;
	void up_run(cocos2d::Ref* pSender);
	void down_run(cocos2d::Ref* pSender);
	void left_run(cocos2d::Ref* pSender);
	void right_run(cocos2d::Ref* pSender);
	
	// 三个动画
	void running(int direction);
	void attacking(cocos2d::Ref* pSender);
	void dying();
	
	// 关于X和Y动画不能同时播放
	bool triggering;		// x和y不能同时播放、精灵智能响应wasd中的一个动作的flag
	void enable_trigger();	// 使triggering为真

	void create_and_move_monster(float dt);	// 产生和移动怪物
	void hitByMonster(float dt);
	int lastCid;			// player偏转方向
};

#endif // __HELLOWORLD_SCENE_H__
