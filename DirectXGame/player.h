#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>
#include<PlayerBullet.h>
#include<list>

//自キャラ
class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);

	~Player();

	void Update();

	void Attack();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition();

	void OnCollision();

	const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	float Getsize() { return size; }
	private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	float size;

	//弾
	std::list<PlayerBullet*>bullets_;
	
};