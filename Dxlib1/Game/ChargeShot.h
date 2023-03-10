#pragma once
#include "../Geometry.h"

/// <summary>
/// 自機の弾を管理するクラス
/// </summary>
class ChargeShot
{
public:
	ChargeShot();

	/// <summary>
	/// //弾を発射する
	/// </summary>
	/// <param name="pos">発射場所</param>
	void Fire(const Position2& pos);

	//弾の有効無効フラグを得る
	bool IsEnabled()const;

	void Update();

	void Draw();
private:
	Position2 pos_ = {};
	Vector2 vel_ = {};
	int handle_ = 0;
	int imgIdx_ = 0;

	//弾が生きているか
	bool isEnabled_ = false;
};