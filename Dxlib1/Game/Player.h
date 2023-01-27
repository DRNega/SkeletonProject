#pragma once
#include "../Geometry.h"

class Enemy;
class InputState;

class Player
{
public:
	Player();

	const Position2& GetPosition()const;
	void Dameged();

	/// <summary>
	/// �v���C���[�̏�Ԃ̍X�V
	/// </summary>
	/// <param name="input">����</param>
	void Update(const InputState& input);

	/// <summary>
	/// �v���C���[�̕`��
	/// </summary>
	void Draw();
private:
	Enemy* enemy_ = nullptr;

	//���@�̌��݂̍��W
	Position2 pos_;	

	//�v���C���[�̉摜
	int handle_;

	//�\������摜�̃C���f�b�N�X
	int imgIdx_ = 0;	
};