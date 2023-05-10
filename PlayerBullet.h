#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>

class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3&position);

	void Update();

	void Draw(const ViewProjection& viewProjection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

};