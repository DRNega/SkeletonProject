#pragma once
#include "Scene.h"
#include <memory>	//「スマートポインタ」を使うためのinclude
#include <array>	//配列用

//プロトタイプ宣言
class Player;		//プレイヤークラス
class Shot;			//自機の弾
class ChargeShot;	//波動砲(チャージ弾)

/// <summary>
/// ゲーム中シーン
/// </summary>
class GameplayingScene : public Scene
{
public:
	GameplayingScene(SceneManager& manager);
	~GameplayingScene() {}

	void Update(const InputState& input);
	void Draw();
private:
	//プレイヤー
	std::shared_ptr<Player> player_;
	
	//弾
	std::array<std::shared_ptr<Shot>, 32> shots_;
	int rapidFireCount_ = 0;

	//フェードの色(デフォ黒)
	unsigned int  fadeColor_ = 0x000000; 

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameplayingScene::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

	//波動砲(チャージ弾)
	std::shared_ptr<ChargeShot> chargeShot_;
	int chargePower_ = 0;
	int gaugeImg_;
	int chargedGaugeImg_;

	struct BagImg
	{
		//画像のハンドル
		int handle;

		//スクロールのスピード(多重スクロール用)
		float scrollSpeed;

		//上限反転ありか?
		bool isTurnV = false;

		//現在の画像は上下反転するか?
		bool currentTurnV = false;
	};

	//背景
	std::array<BagImg, 3> bgImgs_;

	//現在のスクロール
	int scroll_ = 0;

	//現在の幅
	int bgW_ = 0;

	//現在の高さ
	int bgH_ = 0;
};

