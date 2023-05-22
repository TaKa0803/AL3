#pragma once
#include "WorldTransform.h"
#include "Model.h"



class EnemyBullet {
public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	// ゲッター
	bool IsDead() const { return isDead_; }

	void OnCollision();

	Vector3 GetWorldPosition() { return worldTransform_.translation_; }
	
	float Getsize() { return size; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;

	// デスタイマー
	int32_t deathTimer_ = 60 * 5;
	// デスフラグ
	bool isDead_ = false;

	float size;
};