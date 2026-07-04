module;

#include <cocos/2d/CCActionInterval.h>
#include <cocos/2d/CCActionInstant.h>
#include <cocos/2d/CCLayer.h>
#include <cocos/2d/CCSprite.h>
#include <cocos/base/CCDirector.h>
#include <cocos/platform/CCImage.h>

export module ctext.scenes:logo_scene;

import ct.ctr;
import ct.input;
import ct.scene;


export namespace ctext::scenes {
	class LogoScene : public cocos2d::Layer {
	public:
		virtual ~LogoScene() {

		}

		virtual bool init() override {
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
				std::string filename = "sqlogo.png";
				logoTexture = ct::ctr::ResourceManager::createTexture(&filename, &logoImage);
			}

			auto* logo = cocos2d::Sprite::createWithTexture(logoTexture);
			logo->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
			logo->setPosition(visibleSize.width * 0.5f + visibleOrigin.x, visibleSize.height * 0.5f + visibleOrigin.y);
			logo->setColor(cocos2d::Color3B::BLACK);
			this->addChild(logo);

			auto tintWhite = cocos2d::TintTo::create(0.8f, cocos2d::Color3B::WHITE);
			auto tintBlack = cocos2d::TintTo::create(0.8f, cocos2d::Color3B::BLACK);
			auto delay = cocos2d::DelayTime::create(2.0f);

			/*auto* tsuna = cocos2d::Sprite::create("voice/tsunamods.png");
			tsuna->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
			tsuna->setPosition(visibleSize.width * 0.5f + visibleOrigin.x, visibleSize.height * 0.5f + visibleOrigin.y);
			auto scale = visibleSize.height / tsuna->getContentSize().height;
			tsuna->setScale(scale);
			tsuna->setColor(cocos2d::Color3B::BLACK);
			tsuna->setVisible(false);
			this->addChild(tsuna);*/

			auto bgTransition = cocos2d::Sequence::create(tintWhite, delay, tintBlack, nullptr);

			auto bgFade = cocos2d::TargetedAction::create(bg, bgTransition);
			//auto logoFade = cocos2d::TargetedAction::create(logo, logoTransition);
			auto logoFade = cocos2d::TargetedAction::create(logo, bgTransition->clone());
			auto fade = cocos2d::Spawn::create(bgFade, logoFade, nullptr);

			/*auto tsunaVisible = cocos2d::CallFunc::create([tsuna]() {
				tsuna->setVisible(true);
			});

			auto tsunaTransition = cocos2d::Sequence::create(tsunaVisible, tintWhite->clone(), delay->clone(), tintBlack->clone(), nullptr);
			auto tsunaFade = cocos2d::TargetedAction::create(tsuna, tsunaTransition);*/

			auto introEnded = cocos2d::CallFunc::create([] {
				ct::scene::SceneManager::NextScene(0);
			});

			auto logosSequence = cocos2d::Sequence::create(fade, /*tsunaFade,*/ introEnded, nullptr);

			this->runAction(logosSequence);
			this->scheduleUpdate();

			return true;
		}

		virtual void update(float delta) override {
			auto* controller = ct::input::VirtualController::getInstance();
		}
	};
}