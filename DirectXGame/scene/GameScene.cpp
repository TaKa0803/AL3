#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include<AxisIndicator.h>
#include<Matrix.h>
#include <fstream>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete modelSkydome_;
	delete player_;
	delete debugcamera_;
	delete skydome;

	for (Enemy* enemy : enemy_) {
		delete enemy;
	}
	for (PlayerBullet* bullet : playerBullets_) {
		delete bullet;
	}
	for (EnemyBullet* bullet : enemyBullets_) {
		delete bullet;
	}
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	TextureHandle_ = TextureManager::Load("mario.jpg");
	EnemyTextureHandle = TextureManager::Load("ushikun.jpg");
	reticleTexture_ = TextureManager::Load("reticle.png");
	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	
	//天球
	skydome = new Skydome();
	skydome->Initialize(modelSkydome_);

#pragma region カメラ
	// view
	viewProjection_.farZ = 2 * skydome->GetScalar();
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
	Vector3 playerPosition(0, 0, 50);
	player_->Initialize(model_,TextureHandle_,playerPosition,reticleTexture_);
	//自キャラとカメラで親子関係
	player_->SetParent(railCamera->GetWorldTransform());	

	waitCount_ = 0;
	isWait_ = false;
}




void GameScene::LoadEnemyPopData() {
	
	//ファイルを開く
	std::ifstream file("./Resources/enemyPop.csv");
	assert(file.is_open());
	//ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();
	//ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommand() {
	//待機処理
	if (isWait_) {
		waitCount_--;
		if (waitCount_ <= 0) {
		//待機完了
			isWait_ = false;
		}
	}
	
	//1行分の文字列を入れる変数
	std::string line;
	if (isWait_ == false) {
	//コマンド実行ループ
		while (std::getline(enemyPopCommands, line)) {
			// 1行分の文字列をストリームに変換して解析しやすくする
			std::istringstream line_stream(line);

			std::string word;
			// 区切りで行の戦闘文字列を取得
			std::getline(line_stream, word, ',');

			//"//"から始まる行はコメント
			if (word.find("//") == 0) {
				// コメント行を飛ばす
				continue;
			}

			// POPコマンド
			if (word.find("POP") == 0) {
				// x座標
				std::getline(line_stream, word, ',');
				float x = (float)std::atof(word.c_str());
				// y座標
				std::getline(line_stream, word, ',');
				float y = (float)std::atof(word.c_str());
				// z座標
				std::getline(line_stream, word, ',');
				float z = (float)std::atof(word.c_str());

				// 敵を発生させる
				AddEnemy(Vector3(x, y, z));
			}

			// WAITコマンド
			else if (word.find("WAIT") == 0) {
				std::getline(line_stream, word, ',');
				// 待ち時間
				int32_t waitTime = atoi(word.c_str());

				// 待機時間
				isWait_ = true;

				waitCount_ = waitTime;

				break;
			}
		}
	}
}
void GameScene::AddEnemy(Vector3 pos) { 
	
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(model_, EnemyTextureHandle,pos);
	enemy_.push_back(newEnemy);
	
}

void GameScene::Update() {
	
#pragma region // 視覚関係
	skydome->Update();
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
		// viewProjection_.UpdateMatrix();
	}
	viewProjection_.TransferMatrix();
#pragma endregion

	


	GameScene::UpdateEnemyPopCommand();



	player_->SetGameScene(this);
	player_->Update(viewProjection_);

	for (Enemy* enemy : enemy_) {
		enemy->SetPlayer(player_);
		enemy->SetGameScene(this);
		if (enemy) {
			enemy->Update();
		}
	}

	// 弾更新
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Update();
	}
	// 敵の弾更新処理
	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Update();
	}


	//削除処理
	enemy_.remove_if([](Enemy* enemy) {
		if (!enemy->IsDraw()) {
			delete enemy;
			return true;
		}
		return false;
	});

	GameScene::CheckAllCollosions();

	// デスフラグの立った球を削除
	playerBullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	
	// 削除処理
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
});

	


	
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {
	//リストに登録する
	enemyBullets_.push_back(enemyBullet);
}

void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {
	//リストに登録する
	playerBullets_.push_back(playerBullet);
}
    //弾の当たり判定
void GameScene::CheckAllCollosions() {
	//判定対象AとBの座標
	Vector3 posA, posB;
	//次弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = playerBullets_;
	//敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemyBullets_;
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
	for (Enemy* enemy : enemy_) {
		posB = enemy->GetWorldPosition();
		for (PlayerBullet* bulletA : playerBullets) {
			posA = bulletA->GetWorldPosition();
			if (Length(Subtract(posA, posB)) <= enemy->Getsize() + bulletA->Getsize()) {
				bulletA->OnCollision();
				enemy->OnCollision();
			}
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


	for (Enemy* enemy : enemy_) {
		enemy->Draw(viewProjection_);
	}

	for (EnemyBullet* bullet : enemyBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 弾描画
	for (PlayerBullet* bullet : playerBullets_) {
		bullet->Draw(viewProjection_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	player_->DrawUI();
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
