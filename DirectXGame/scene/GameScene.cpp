#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<AxisIndicator.h>
#include<Matrix.h>
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugcamera_;
	delete enemy_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	TextureHandle_ = TextureManager::Load("mario.jpg");
	EnemyTextureHandle = TextureManager::Load("ushikun.jpg");
	model_ = Model::Create();

	//
	viewProjection_.Initialize();

	player_ = new Player();
	player_->Initialize(model_,TextureHandle_);

	enemy_ = new Enemy();
	enemy_->Initialize(model_, EnemyTextureHandle);

	// デバックカメラの生成
	debugcamera_ = new DebugCamera(1280, 720);

	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	enemy_->SetPlayer(player_);
}

void GameScene::Update() {
	player_->Update();
	if (enemy_) {
		enemy_->Update();
	}
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_1)) {
		isDebugCameraActive_ = true;
	}
#endif // _DEBUG
	if (isDebugCameraActive_) {
		debugcamera_->Update();

		viewProjection_.matView = debugcamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugcamera_->GetViewProjection().matProjection;

		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
	}


	
}

 

/*
void GameScene::CheckAllCollosions() {
	//判定対象AとBの座標
	Vector3 posA, posB;

	//次弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();

	#pragma region 自キャラと敵弾の当たり判定
	posA = player_->GetWorldPosition();

	//自キャラと敵弾すべての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
	//敵弾の座標
		posB = bullet->GetWorldPosition();

		if (Distance(posA, posB) <= 1) {
		
		}
	}
	#pragma endregion
	#pragma region 次弾と敵キャラの当たり判定

	#pragma endregion
	#pragma region 次弾と敵弾の当たり判定

	#pragma endregion


}
*/
void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	player_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
