#pragma once
#include<DebugCamera.h>
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include<player.h>
#include<Enemy.h>
#include<Skydome.h>
#include<RailCamera.h>
#include<EnemyBullet.h>

#include<sstream>
/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollosions();

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 自機弾を追加
	/// </summary>
	void AddPlayerBullet(PlayerBullet* playerBullet);


	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();


/// <summary>
/// 敵発生コマンドの更新
/// </summary>
	void UpdateEnemyPopCommand();


	/// <summary>
	/// 敵発生関数
	/// </summary>
	void AddEnemy(Vector3 pos);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	/// 
	Model* model_ = nullptr;
	Model* modelSkydome_ = nullptr;
	
	ViewProjection viewProjection_;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugcamera_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;
	uint32_t TextureHandle_ = 0;
	// 弾
	std::list<PlayerBullet*> playerBullets_;
	
	//敵
	std::list<Enemy*> enemy_;
	uint32_t EnemyTextureHandle = 0;
	// 敵弾
	std::list<EnemyBullet*> enemyBullets_;

	//天球
	Skydome* skydome = nullptr;

	//レールカメラ
	RailCamera* railCamera = nullptr;

	//敵発生コマンド
	std::stringstream enemyPopCommands;


	//レベルデザイン
	bool isWait_;
	int32_t waitCount_;
};
