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

	ViewProjection viewProjection_;

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	DebugCamera* debugcamera_ = nullptr;

	//プレイヤー
	Player* player_ = nullptr;
	uint32_t TextureHandle_ = 0;
	
	//敵
	Enemy* enemy_ = nullptr;
	uint32_t EnemyTextureHandle = 0;
};
