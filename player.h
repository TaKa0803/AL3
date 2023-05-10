#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>
#include<PlayerBullet.h>

//自キャラ
class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);

	void Update();

	void Attack();

	void Draw(ViewProjection view);

	private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	//弾
	PlayerBullet*bullet_=nullptr;
};