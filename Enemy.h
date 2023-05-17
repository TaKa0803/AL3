#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <Input.h>
class Enemy {
public:
	//syoki
	void Initialize(Model* model, uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection view);

	void Fire();
	//
	void ApproachFazeInitialize();

	bool Approach();
	bool Leave();
	private:
	//位置
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 行動フェーズ
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};
	//攻撃モード
	Phase phase_=Phase::Approach;

	//弾
	std::list<EnemyBullet *>bullets_;

	//発射感覚
	static const int kFireIntervaal = 60;
	//発射タイマー
	int32_t timer = 0;
	//
	Input* input_ = nullptr;
};