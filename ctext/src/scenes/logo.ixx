module;

#include "build_config.hpp"

//#include "mod_api/sound_manager_impl.hpp"
//#include "ct/virtual_controller.hpp"
//#include "ct/statics.hpp"
//#include "ct/subs.hpp"
//#include "ct/sound_task.hpp"
//
//#include <cocos/2d/CCLayer.h>

export module ctext.scenes:logo;


#ifdef FEATURE_LOGO_HOOK


export namespace ctext::scenes {
	class LogoScene : public cocos2d::Layer {
	public:
		virtual ~LogoScene();

		virtual bool init() override;
		virtual void update(float delta) override;
	};


	LogoScene::~LogoScene() {

	}

	bool LogoScene::init() {
		cocos2d::Layer::init();

		auto* director = cocos2d::Director::getInstance();
		auto visibleSize = director->getVisibleSize();
		auto visibleOrigin = director->getVisibleOrigin();

		auto bg = cocos2d::LayerColor::create(cocos2d::Color4B::BLACK, visibleSize.width, visibleSize.height);
		bg->setPosition(visibleOrigin.x, visibleOrigin.y);
		this->addChild(bg);

		cocos2d::Texture2D* logoTexture;

		{
			cocos2d::Image logoImage;
			logoTexture = ct::sub_19AC50("sqlogo.png", logoImage);
		}

		auto* logo = cocos2d::Sprite::createWithTexture(logoTexture);
		logo->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
		logo->setPosition(visibleSize.width * 0.5f + visibleOrigin.x, visibleSize.height * 0.5f + visibleOrigin.y);
		logo->setColor(cocos2d::Color3B::BLACK);
		this->addChild(logo);

		/*auto tintWhite = cocos2d::TintTo::create(2.0f, cocos2d::Color3B::WHITE);
		auto tintBlack = cocos2d::TintTo::create(2.0f, cocos2d::Color3B::BLACK);
		auto delay = cocos2d::DelayTime::create(5.0f);*/
		auto tintWhite = cocos2d::TintTo::create(0.8f, cocos2d::Color3B::WHITE);
		auto tintBlack = cocos2d::TintTo::create(0.8f, cocos2d::Color3B::BLACK);
		auto delay = cocos2d::DelayTime::create(2.0f);

		auto* tsuna = cocos2d::Sprite::create("voice/tsunamods.png");
		tsuna->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
		tsuna->setPosition(visibleSize.width * 0.5f + visibleOrigin.x, visibleSize.height * 0.5f + visibleOrigin.y);
		auto scale = visibleSize.height / tsuna->getContentSize().height;
		tsuna->setScale(scale);
		tsuna->setColor(cocos2d::Color3B::BLACK);
		tsuna->setVisible(false);
		this->addChild(tsuna);

		auto bgTransition = cocos2d::Sequence::create(tintWhite, delay, tintBlack, nullptr);

		//auto bgFade = cocos2d::TargetedAction::create(bg, bgTransition);
		//auto logoFade = cocos2d::TargetedAction::create(logo, logoTransition);
		auto logoFade = cocos2d::TargetedAction::create(logo, bgTransition->clone());
		auto fade = cocos2d::Spawn::create(/*bgFade,*/ logoFade, nullptr);

		auto tsunaVisible = cocos2d::CallFunc::create([tsuna]() {
			tsuna->setVisible(true);
			});

		auto tsunaTransition = cocos2d::Sequence::create(tsunaVisible, tintWhite->clone(), delay->clone(), tintBlack->clone(), nullptr);
		auto tsunaFade = cocos2d::TargetedAction::create(tsuna, tsunaTransition);

		auto introEnded = cocos2d::CallFunc::create([] {
			ct::sub_297B60(0);
			});

		auto logosSequence = cocos2d::Sequence::create(fade, tsunaFade, introEnded, nullptr);

		this->runAction(logosSequence);
		this->scheduleUpdate();

		return true;
	}

	void LogoScene::update(float delta) {
		auto* controller = &ct::statics::DefaultController();

		if (ct::statics::VirtualController() != nullptr)
			controller = ct::statics::VirtualController();
	}
}


#endif