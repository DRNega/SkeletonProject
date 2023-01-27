#include "ChargeShot.h"
#include <DxLib.h>
#include "../DrawFunctions.h"

constexpr int img_width = 63;
constexpr int img_height = 32;
constexpr float img_scale = 1.0f;

// 1枚当たりフレーム数
constexpr int animation_flame = 16;

ChargeShot::ChargeShot() : 
	vel_(3.0f, 0.0f)
{
	handle_ = my::MyLoadGraph(L"Data/img/game/charge_shot.png");
}

void ChargeShot::Fire(const Position2& pos)
{
	pos_ = pos;
	isEnabled_ = true;
}

bool ChargeShot::IsEnabled() const
{
	return isEnabled_;
}

void ChargeShot::Update()
{
	//弾を現在速度で移動させる
	pos_ += vel_;

	//画像のインデックスの切り替え
	imgIdx_ = (imgIdx_ + 1) % (4 * animation_flame);

	//弾が画面外に出たら、死んだことにする
	if (pos_.x < -img_width || 640 + img_width < pos_.x)
	{
		isEnabled_ = false;
	}
}

void ChargeShot::Draw()
{
	my::MyDrawRectRotaGraph(
		pos_.x, pos_.y,
		(imgIdx_ / animation_flame) * img_width, 0,
		img_width, img_height,
		img_scale, 0.0f,
		handle_, true);
}
