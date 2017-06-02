#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Global.h"
#include "GameScene.h"
#include <regex>
using std::to_string;
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;
USING_NS_CC;

using namespace cocostudio::timeline;

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
using namespace  rapidjson;

#define database UserDefault::getInstance()

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool LoginScene::init()
{
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	

    Size size = Director::getInstance()->getVisibleSize();
    visibleHeight = size.height;
    visibleWidth = size.width;

    textField = TextField::create("Player Name", "Arial", 30);
    textField->setPosition(Size(visibleWidth / 2, visibleHeight / 4 * 3));
    this->addChild(textField, 2);

    auto button = Button::create();
    button->setTitleText("Login");
    button->setTitleFontSize(30);
    button->setPosition(Size(visibleWidth / 2, visibleHeight / 2));
	button->addTouchEventListener(CC_CALLBACK_2(LoginScene::login, this));
    this->addChild(button, 2);

    return true;
}

void LoginScene::login(Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	// POST请求
	HttpRequest *request = new HttpRequest();
	request->setUrl("http://localhost:8080/login");
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(LoginScene::onHttpRequestCompleted, this));

	// 数据
	string player_name = textField->getString();
	string data = "username=" + player_name;
	const char *post_data = data.data();
	request->setRequestData(post_data, strlen(post_data));

	// 发送
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void LoginScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response) {
	if (!response) {	// 如果没有response
		return;
	}
	if (!response->isSucceed()) {	// 要求返回是否成功
		log("response failes");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	// 获得响应的字符串
	string res = Global::toString(response->getResponseData());
	// 解析json格式的字符串
	rapidjson::Document res_d;
	res_d.Parse<0>(res.c_str());
	if (res_d.HasParseError()) {	// 解析错误
		CCLOG("GetParseError %s\n", res_d.GetParseError());
	}
	// 获得result的值
	if (res_d.IsObject() && res_d.HasMember("result")) {
		// 登陆成功
		if (res_d["result"].GetBool() == true) {
			// 保存sessionid
			 Global::gameSessionId = Global::getSessionIdFromHeader(Global::toString(response->getResponseHeader()));
			 database->setStringForKey("sessionid", Global::gameSessionId);
			 // 切换场景
			 auto gameSence = GameScene::createScene();
			 Director::getInstance()->replaceScene(gameSence);
		}
	}
	
}