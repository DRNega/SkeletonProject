#include "GameplayingScene.h"
#include "../InputState.h"
#include "GameoverScene.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "../DrawFunctions.h"
#include "PauseScene.h"
#include"../Game/Player.h"
#include "../Game/Shot.h"
#include "../Game/ChargeShot.h"
#include <DxLib.h>

constexpr int rapid_fire_interval = 10;
constexpr int max_charge_frame = 80;
constexpr int gauge_x = 10;
constexpr int gauge_y = 480 - 36;
constexpr float gauge_width_scale = 3.6f;

void GameplayingScene::FadeInUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (--fadeTimer_ == 0)
	{
		updateFunc_ = &GameplayingScene::NormalUpdate;
		rapidFireCount_ = 0;
	}
}
void GameplayingScene::NormalUpdate(const InputState& input)
{
	scroll_ = scroll_ + 1;
	player_->Update(input);

	if (input.IsPressed(InputType::shot))
	{
		if (input.IsTriggered(InputType::shot))
		{
			for (auto& shot : shots_)
			{
				if (!shot->IsEnabled())
				{
					shot->Fire(player_->GetPosition() + Vector2(26.0f, 0.0f));
					break;
				}
			}
		}
		else
		{
			chargePower_++;
		}
	}
	else
	{
		if (chargePower_ >= max_charge_frame)
		{
			chargeShot_->Fire(player_->GetPosition());
		}
		chargePower_ = 0;
	}
	// �A��
	if (input.IsPressed(InputType::rapid))
	{
		if (rapidFireCount_ == 0)
		{
			for (auto& shot : shots_)
			{
				if (!shot->IsEnabled())
				{
					shot->Fire(player_->GetPosition());
					break;
				}
			}
		}
		rapidFireCount_ = (rapidFireCount_ + 1) % rapid_fire_interval;
	}
	for (auto& shot : shots_)
	{
		if (shot->IsEnabled())
		{
			shot->Update();
		}
	}
	if (chargeShot_->IsEnabled())
	{
		chargeShot_->Update();
	}

	if (input.IsTriggered(InputType::next))
	{
		updateFunc_ = &GameplayingScene::FadeOutUpdate;
		fadeColor_ = 0xff0000;
	}
	if (input.IsTriggered(InputType::prev))
	{
		manager_.ChangeScene(new TitleScene(manager_));
		return;
	}
	if (input.IsTriggered(InputType::pause))
	{
		manager_.PushScene(new PauseScene(manager_));
	}
}

void GameplayingScene::FadeOutUpdate(const InputState& input)
{
	fadeValue_ = 255 * static_cast<float>(fadeTimer_) / static_cast<float>(fade_interval);
	if (++fadeTimer_ == fade_interval)
	{
		manager_.ChangeScene(new GameoverScene(manager_));
		return;
	}
}

GameplayingScene::GameplayingScene(SceneManager& manager) :
	Scene(manager),
	updateFunc_(&GameplayingScene::FadeInUpdate)
{
	player_ = std::make_shared<Player>();
	chargeShot_ = std::make_shared<ChargeShot>();

	//gaugeImg_ = my::MyLoadGraph(L"Data/img/game/gauge.png");
	//chargedGaugeImg_ = my::MyLoadGraph(L"Data/img/game/chargedGauge.png");

	//�n���h����ݒ�
	bgImgs_[0].handle = my::MyLoadGraph(L"Data/img/game/bg-back.png");
	bgImgs_[1].handle = my::MyLoadGraph(L"Data/img/game/bg-stars.png");
	bgImgs_[2].handle = my::MyLoadGraph(L"Data/img/game/bg-planet.png");
	//�X�N���[���X�s�[�h��ݒ�
	bgImgs_[0].scrollSpeed = 0.5f;
	bgImgs_[1].scrollSpeed = 0.75f;
	bgImgs_[2].scrollSpeed = 1.0f;
	//���]����ǂ���
	bgImgs_[2].isTurnV = true;

	//�w�i�̕��ƍ������L�^���Ă���
	GetGraphSize(bgImgs_[0].handle, &bgW_, &bgH_);

	// �e�̐���
	int shotH = my::MyLoadGraph(L"Data/img/game/shot.png");
	for (auto& shot : shots_)
	{
		shot = std::make_shared<Shot>(shotH);
	}
}


void GameplayingScene::Update(const InputState& input)
{
	(this->*updateFunc_)(input);
}

void GameplayingScene::Draw()
{
	constexpr float bg_scale = 3.0f;
	
	//��̃X�N���[��
	
	for(auto& bg : bgImgs_)
	{
		int scroll = static_cast<int>(scroll_ * bg.scrollSpeed) % static_cast<int>(bgW_ * bg_scale * (bg.isTurnV?2.0f : 1.0f));
		//�w�i�̕`��@
		DrawRotaGraph(bgW_ * 0.5 * bg_scale - scroll,	//�\�����Sx���W
					bgH_ * 0.5 * bg_scale,			//�\�����Sy���W
					3.0f, 0.0f, bg.handle, true, false, false);
		//�w�i�̕`��A
		DrawRotaGraph(bgW_ * (1 + 0.5) * bg_scale - scroll,	//�\�����Sx���W
					bgH_ * 0.5 * bg_scale,					//�\�����Sy���W
					3.0f, 0.0f, bg.handle, true, false,false);
	}
	
	DrawString(0, 0, L"GamePlayingScene", 0xffffff, true);

	player_->Draw();

	for (auto& shot : shots_)
	{
		if (shot->IsEnabled())
		{
			shot->Draw();
		}
	}
	if (chargeShot_->IsEnabled())
	{
		chargeShot_->Draw();
	}

	//�`���[�W�Q�[�W
	DrawExtendGraph(gauge_x, gauge_y,//���� 
		gauge_x + std::min(chargePower_, max_charge_frame) * gauge_width_scale, gauge_y + 10,//�E��
		(chargePower_ >= max_charge_frame) ? chargedGaugeImg_ : gaugeImg_, false);

	//�`���[�W�Q�[�W
	DrawBox(gauge_x, gauge_y,//���� 
		gauge_x + std::min(chargePower_ ,max_charge_frame ) * gauge_width_scale, gauge_y + 10,//�E��
		(chargePower_ >= max_charge_frame) ? 0xff8888 : 0x8888ff, true);

	//�Q�[�W�g
	DrawBox(gauge_x, gauge_y,//���� 
		gauge_x + max_charge_frame * gauge_width_scale, gauge_y + 10,//�E��
		0xffffff, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue_);
	DrawBox(0, 0, 640, 480, fadeColor_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}