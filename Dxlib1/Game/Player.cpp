#include "Player.h"
#include "../DrawFunctions.h"
#include "../InputState.h"
#include <DxLib.h>

// 自機画像1個あたりの幅と高さ
constexpr int img_width = 26;
constexpr int img_height = 21;
constexpr float draw_scale = 2.0f;

Player::Player() : 
	pos_(320, 240)
{
	handle_ = my::MyLoadGraph(L"Data/img/game/player.png");
}

const Position2& Player::GetPosition() const
{
	return pos_;
}

void Player::Dameged()
{

}

void Player::Update(const InputState& input)
{
	constexpr float speed = 2.0f;

	// 速度ベクトル
	Vector2 vel = {0.0f, 0.0f};

	if (input.IsPressed(InputType::up))
	{
		imgIdx_ = 2;
		vel.y = -2.0f;
	}
	else if (input.IsPressed(InputType::down))
	{
		imgIdx_ = 1;
		vel.y = 2.0f;
	}
	// 上も下も押してない
	else
	{
		imgIdx_ = 0;
	}

	if (input.IsPressed(InputType::left))
	{
		vel.x = -2.0f;
	}
	if (input.IsPressed(InputType::right))
	{
		vel.x = 2.0f;
	}

	// 初期化で0になってしまうため
	// 0 / 0を行うと不明瞭な値になるから
	if (vel.Length() > 0.0f)
	{
		// 各方向にかかわらず大きさを１にする
		vel.Normalize();

		// 1の方向にスピードを乗算する
		vel *= speed;
	}

	// この結果、方向にかかわらずスピードは2.0fになる
	// それをpos_に加算する
	pos_ += vel;
}

void Player::Draw()
{
	// プレイヤー画像の表示
	my::MyDrawRectRotaGraph(
		pos_.x, pos_.y,			// 表示座標
		imgIdx_ * img_width, 0,	// 切り取り左上
		img_width, img_height,	// 幅、高さ
		draw_scale, 0.0f,		// 拡大率、回転角度
		handle_, true);
}
