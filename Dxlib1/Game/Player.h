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
	/// プレイヤーの状態の更新
	/// </summary>
	/// <param name="input">入力</param>
	void Update(const InputState& input);

	/// <summary>
	/// プレイヤーの描画
	/// </summary>
	void Draw();
private:
	Enemy* enemy_ = nullptr;

	//自機の現在の座標
	Position2 pos_;	

	//プレイヤーの画像
	int handle_;

	//表示する画像のインデックス
	int imgIdx_ = 0;	
};