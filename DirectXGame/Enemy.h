#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include <Input.h>
class Player;

class GameScene;

class Enemy {
public:
	//syoki
	void Initialize(Model* model, uint32_t textureHandle, Vector3 translation);

	void Update();

	void Draw(ViewProjection view);

	void Fire();
	//
	void ApproachFazeInitialize();

	bool Approach();
	bool Leave();

	void SetPlayer(Player* player) { player_ = player; }
	
	Vector3 GetWorldPosition();


	void OnCollision();

	//const std::list<EnemyBullet*>& GetBullets() { return bullets_; }

	float Getsize() { return size; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDraw() { return isdraw; }

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

	bool isdraw = true;


	//発射感覚
	static const int kFireIntervaal = 60;
	//発射タイマー
	int32_t timer = 0;
	//
	Input* input_ = nullptr;

	//自キャラ
	Player* player_=nullptr;

	float size;

	//ゲームシーン
	GameScene* gameScene_ = nullptr;
};