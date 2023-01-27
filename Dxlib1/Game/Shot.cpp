#include "Shot.h"
#include <DxLib.h>
#include "../DrawFunctions.h"

constexpr int img_width = 19;
constexpr int img_height = 6;
constexpr float img_scale = 2.0f;

Shot::Shot(int handle) :
	handle_(handle),
	vel_(6.0f, 0.0f)
{
}

void Shot::Fire(const Position2& pos)
{
	pos_ = pos;
	isEnabled_ = true;
}

bool Shot::IsEnabled() const
{
	return isEnabled_;
}

void Shot::Update()
{
	//�e�����ݑ��x�ňړ�������
	pos_ += vel_;

	//�摜�̃C���f�b�N�X�̐؂�ւ�
	imgIdx_ = (imgIdx_ + 1) % 2;

	//�e����ʊO�ɏo����A���񂾂��Ƃɂ���
	if (pos_.x < -img_width || 640 + img_width < pos_.x )
	{
		isEnabled_ = false;
	}
}

void Shot::Draw()
{
	my::MyDrawRectRotaGraph(
		pos_.x, pos_.y,
		imgIdx_ * img_width, 0,
		img_width, img_height,
		img_scale, 0.0f,
		handle_, true);
}
