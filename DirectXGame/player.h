#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>
#include<PlayerBullet.h>
#include<list>

class GameScene;

//自キャラ
class Player {
public:
	void Initialize(Model* model, uint32_t textureHandle, Vector3 position);

	~Player();

	void Update();

	void Attack();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition();

	void OnCollision();

	//const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	float Getsize() { return size; }

	void SetParent(const WorldTransform* parent);

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	float size;

	
	//
	GameScene *gameScene_;
};