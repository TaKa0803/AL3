#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<AxisIndicator.h>
#include<Matrix.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
	delete player_;
	delete debugcamera_;
	delete enemy_;
	delete skydome;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	TextureHandle_ = TextureManager::Load("mario.jpg");
	EnemyTextureHandle = TextureManager::Load("ushikun.jpg");
	
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	
	//天球
	skydome = new Skydome();
	skydome->Initialize(modelSkydome_);

#pragma region カメラ
	// view
	viewProjection_.farZ = 2 * skydome->GetScalar();
	viewProjection_.translation_ = {0, 0, 0};
	viewProjection_.Initialize();

	// デバックカメラの生成
	debugcamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	// レールカメラ
	railCamera = new RailCamera();
	railCamera->Initialize(viewProjection_);

#pragma endregion

	//プレイヤー
	player_ = new Player();
	Vector3 playerPosition(0, 0, 30);
	player_->Initialize(model_,TextureHandle_,playerPosition);
	//自キャラとカメラで親子関係
	player_->SetParent(railCamera->GetWorldTransform());
	
	//敵
	enemy_ = new Enemy();
	enemy_->Initialize(model_, EnemyTextureHandle);
	enemy_->SetPlayer(player_);

	
	

	
}

void GameScene::Update() {
	

	skydome->Update();

	player_->Update();
	if (enemy_) {
		enemy_->Update();
	}

	railCamera->Update();
	viewProjection_.matView = railCamera->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera->GetViewProjection().matProjection;
	
	
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_1)) {
		isDebugCameraActive_ = true;
	}
#endif // _DEBUG
	if (isDebugCameraActive_) {
		debugcamera_->Update();
		viewProjection_.matView = debugcamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugcamera_->GetViewProjection().matProjection;	
	} else {
		//viewProjection_.UpdateMatrix();
	}
	viewProjection_.TransferMatrix();

	
}

 


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

		if (Length(Subtract(posA,posB)) <= player_->Getsize()+bullet->Getsize()) {
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
	#pragma endregion
	#pragma region 次弾と敵キャラの当たり判定
	// 敵の座標
	posB = enemy_->GetWorldPosition();
	for (PlayerBullet* bulletA : playerBullets) {
		posA = bulletA->GetWorldPosition();
			
			if (Length(Subtract(posA,posB))<=enemy_->Getsize()+bulletA->Getsize()) {
				bulletA->OnCollision();
				enemy_->OnCollision();
			}
		
	}
	#pragma endregion
	#pragma region 次弾と敵弾の当たり判定
	for (PlayerBullet* bulletA : playerBullets) {
		posA = bulletA->GetWorldPosition();
		for (EnemyBullet* bullet : enemyBullets) {
			// 敵弾の座標
			posB = bullet->GetWorldPosition();

			if (Length(Subtract(posA, posB)) <= bulletA->Getsize() + bullet->Getsize()) {
				bulletA->OnCollision();
				bullet->OnCollision();
			}
		}
	}
	#pragma endregion


}

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
	skydome->Draw(viewProjection_); 

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
