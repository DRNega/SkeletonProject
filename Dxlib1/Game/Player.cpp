#include "Player.h"
#include "../DrawFunctions.h"
#include "../InputState.h"
#include <DxLib.h>

// ���@�摜1������̕��ƍ���
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

	// ���x�x�N�g��
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
	// ������������ĂȂ�
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

	// ��������0�ɂȂ��Ă��܂�����
	// 0 / 0���s���ƕs���ĂȒl�ɂȂ邩��
	if (vel.Length() > 0.0f)
	{
		// �e�����ɂ�����炸�傫�����P�ɂ���
		vel.Normalize();

		// 1�̕����ɃX�s�[�h����Z����
		vel *= speed;
	}

	// ���̌��ʁA�����ɂ�����炸�X�s�[�h��2.0f�ɂȂ�
	// �����pos_�ɉ��Z����
	pos_ += vel;
}

void Player::Draw()
{
	// �v���C���[�摜�̕\��
	my::MyDrawRectRotaGraph(
		pos_.x, pos_.y,			// �\�����W
		imgIdx_ * img_width, 0,	// �؂��荶��
		img_width, img_height,	// ���A����
		draw_scale, 0.0f,		// �g�嗦�A��]�p�x
		handle_, true);
}
