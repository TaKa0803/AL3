#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>

static const int32_t kLifeTime = 60 * 5;

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3&position,const Vector3&velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	//ゲッター
	bool IsDead() const { return isDead_; }

	void OnCollision();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	//速度
	Vector3 velocity_;

	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
};