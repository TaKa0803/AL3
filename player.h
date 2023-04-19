#pragma once
#include "WorldTransform.h"
#include "Model.h"

//自キャラ
class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);

	void Update();

	void Draw(ViewProjection view);

	private:
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};