#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>
#include<PlayerBullet.h>
#include<list>
#include<Sprite.h>
class GameScene;

//自キャラ
class Player {
public:
	void
	    Initialize(Model* model, uint32_t textureHandle, Vector3 position, uint32_t reticleTexture);

	~Player();

	void Update(ViewProjection view);

	void Attack();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition();

	void OnCollision();

	//const std::list<PlayerBullet*>& GetBullets() { return bullets_; }

	float Getsize() { return size; }

	void SetParent(const WorldTransform* parent);

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }


	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	private:

	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;

	float size;
	
	//
	GameScene *gameScene_;

	//3Dレティクル用ワールドトランスフォーム
	WorldTransform worldtransform3DReticle_;
	Model* reticleModel_ = nullptr;
	uint32_t reticleTextureHandle_=0u;

	//2Dレティクル用スプライト
	Sprite* sprite2DReticle_ = nullptr;

	
};