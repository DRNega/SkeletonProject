#pragma once
#include "Scene.h"
#include <memory>	//�u�X�}�[�g�|�C���^�v���g�����߂�include
#include <array>	//�z��p

//�v���g�^�C�v�錾
class Player;		//�v���C���[�N���X
class Shot;			//���@�̒e
class ChargeShot;	//�g���C(�`���[�W�e)

/// <summary>
/// �Q�[�����V�[��
/// </summary>
class GameplayingScene : public Scene
{
public:
	GameplayingScene(SceneManager& manager);
	~GameplayingScene() {}

	void Update(const InputState& input);
	void Draw();
private:
	//�v���C���[
	std::shared_ptr<Player> player_;
	
	//�e
	std::array<std::shared_ptr<Shot>, 32> shots_;
	int rapidFireCount_ = 0;

	//�t�F�[�h�̐F(�f�t�H��)
	unsigned int  fadeColor_ = 0x000000; 

	static constexpr int fade_interval = 60;
	int fadeTimer_ = fade_interval;
	int fadeValue_ = 255;

	void FadeInUpdate(const InputState& input);
	void NormalUpdate(const InputState& input);
	void FadeOutUpdate(const InputState& input);

	using UpdateFunc_t = void (GameplayingScene::*) (const InputState& input);
	UpdateFunc_t updateFunc_ = nullptr;

	//�g���C(�`���[�W�e)
	std::shared_ptr<ChargeShot> chargeShot_;
	int chargePower_ = 0;
	int gaugeImg_;
	int chargedGaugeImg_;

	struct BagImg
	{
		//�摜�̃n���h��
		int handle;

		//�X�N���[���̃X�s�[�h(���d�X�N���[���p)
		float scrollSpeed;

		//������]���肩?
		bool isTurnV = false;

		//���݂̉摜�͏㉺���]���邩?
		bool currentTurnV = false;
	};

	//�w�i
	std::array<BagImg, 3> bgImgs_;

	//���݂̃X�N���[��
	int scroll_ = 0;

	//���݂̕�
	int bgW_ = 0;

	//���݂̍���
	int bgH_ = 0;
};

