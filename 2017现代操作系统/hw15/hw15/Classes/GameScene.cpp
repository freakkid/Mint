#include "GameScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include <regex>
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;

USING_NS_CC;

cocos2d::Scene* GameScene::createScene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GameScene::init() {
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;

	score_field = TextField::create("Score", "Arial", 30);
	score_field->setPosition(Size(visibleWidth / 4, visibleHeight / 4 * 3));
	this->addChild(score_field, 2);

	submit_button = Button::create();
	submit_button->setTitleText("Submit");
	submit_button->setTitleFontSize(30);
	submit_button->setPosition(Size(visibleWidth / 4, visibleHeight / 4));
	submit_button->addTouchEventListener(CC_CALLBACK_2(GameScene::submit, this));
	this->addChild(submit_button, 2);

	rank_field = TextField::create("", "Arial", 30);
	rank_field->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4 * 3));
	this->addChild(rank_field, 2);

	rank_button = Button::create();
	rank_button->setTitleText("Rank");
	rank_button->setTitleFontSize(30);
	rank_button->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4));
	rank_button->addTouchEventListener(CC_CALLBACK_2(GameScene::rank, this));
	this->addChild(rank_button, 2);

	return true;
}

void GameScene::submit(Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	// �ж�score��������Ƿ�ȫ�������Ҳ�Ϊ��
	if (GameScene::isDigit(score_field->getString())) {
		HttpRequest *request = new HttpRequest();
		request->setUrl("http://localhost:8080/submit");
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback(CC_CALLBACK_2(GameScene::onHttpSummitRequestCompleted, this));

		string data = "score=" + score_field->getString();
		const char *post_data = data.data();
		request->setRequestData(post_data, strlen(post_data));
		// �����header
		vector<string> headers;
		string cookie = "Cookie:GAMESESSIONID=" + Global::gameSessionId;
		headers.push_back(cookie);
		request->setHeaders(headers);

		// ����
		cocos2d::network::HttpClient::getInstance()->send(request);
		request->release();
	}


}
// �ж�score�Ƿ�ȫ�������Ҳ�Ϊ��
bool GameScene::isDigit(string score) {
	if (score.length() > 0) {
		for (int i = 0; i < score.length(); i++) {
			if (!isdigit(score[i]))
				return false;
		}
		return true;
	}
	return false;
}

void GameScene::onHttpSummitRequestCompleted(HttpClient *sender, HttpResponse *response) {
	if (!response) {
		return;
	}
	if (!response->isSucceed()) {
		log("response failes");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	string res = Global::toString(response->getResponseData());
	
	// ����json��ʽ���ַ���
	rapidjson::Document res_d;
	res_d.Parse<0>(res.c_str());
	if (res_d.HasParseError()) {	// ��������
		CCLOG("GetParseError %s\n", res_d.GetParseError());
	}
	if (res_d.IsObject() && res_d.HasMember("result")) {
		// �ύ�ɹ�
		if (res_d["result"].GetBool() == true) {
			// ��ȡ��߷���
			if (res_d.HasMember("info")) {
				// ��ȡ��߷���,�������������
				score_field->setText(res_d["info"].GetString());
			}
		}
	}
}

void GameScene::rank(Ref *pSender, cocos2d::ui::Widget::TouchEventType type) {
	HttpRequest *request = new HttpRequest();
	request->setUrl("http://localhost:8080/rank?top=10");
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(GameScene::onHttpRankRequestCompleted, this));

	vector<string> headers;
	string cookie = "Cookie:GAMESESSIONID=" + Global::gameSessionId;
	headers.push_back(cookie);
	request->setHeaders(headers);

	// ����
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void GameScene::onHttpRankRequestCompleted(HttpClient *sender, HttpResponse *response) {
	if (!response) {
		return;
	}
	if (!response->isSucceed()) {
		log("response failes");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	string res = Global::toString(response->getResponseData());
	// ����json��ʽ���ַ���
	rapidjson::Document res_d;
	res_d.Parse<0>(res.c_str());
	if (res_d.HasParseError()) {	// ��������
		CCLOG("GetParseError %s\n", res_d.GetParseError());
	}
	if (res_d.IsObject() && res_d.HasMember("result")) {
		// rank�ɹ�
		if (res_d["result"].GetBool() == true) {
			if (res_d.HasMember("info")) {
				string rank_result = res_d["info"].GetString();
				// "|"��"\n"����
				int len = rank_result.length();
				size_t pos = -1;
				for (int i = 0; i < len; i++) {
					pos = rank_result.find("|");
					if (pos == -1)
						break;
					else
						rank_result[pos] = '\n';
				}
				// rank�����
				rank_field->setText("\n" + rank_result);
			}
		}
	}
}