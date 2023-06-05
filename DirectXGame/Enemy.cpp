#include<Enemy.h>
#include <cassert>
#include<Matrix.h>
#include"player.h"
#include"GameScene.h"
//イニシャライズ
void Enemy::Initialize(Model* model, uint32_t textureHandle,Vector3 translation) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = translation;

	input_ = Input::GetInstance();

	size = 1.0f;
}

void Enemy::ApproachFazeInitialize() { timer = kFireIntervaal; }

Vector3 Enemy::GetWorldPosition() { return worldTransform_.translation_; }

void Enemy::OnCollision() { isdraw = false; }
bool Enemy::Approach() {
	// 移動
	Vector3 move = {0, 0, -0.5f};

	// 移動処理
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// エリア外出さない処理
	if (worldTransform_.translation_.z <= 0.0f) {
		worldTransform_.translation_.z = 0.0f;
		return true;
	}

	//timer
	timer--;
	if (timer < 0) {
		timer = 0;
	}
	if (timer <= 0) {
		//発射処理
		Fire();
		timer = kFireIntervaal;
	}

	//affine
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	return false;
}

bool Enemy::Leave() {
	// 移動
	Vector3 move = {0, 0, 0.5f};

	// 移動処理
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// エリア外出さない処理
	if (worldTransform_.translation_.z >= 100.0f) {
		worldTransform_.translation_.z = 100.0f;
		return true;
	}

	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_,
	    worldTransform_.translation_);
	return false;
}

// ベクトル変換
Vector3 TransformNormall(const Vector3& v, const Matrix4x4& m) {
	return {
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
}

//二点の差分ベクトルの計算(v1→v2)
Vector3 DifferenceVector3(Vector3 v1, Vector3 v2) {
	return {
		v2.x - v1.x, 
	    v2.y - v1.y,
	    v2.z - v1.z,
	};
}


void Enemy::Fire() {
		// 弾の速度
		const float kBulletSpeed = -1.0f;
		//自キャラのワールド座標を取得
	    Vector3 player1 = player_->GetWorldPosition();
		//敵キャラのワールド座標を求める
	    Vector3 Enemy1 = GetWorldPosition();	
		//差分ベクトルと正規化とスカラー倍
	    Vector3 velocity = Scalar(kBulletSpeed, Normalize(Subtract(Enemy1,player1)));
		// 自機の向きに回転
		velocity = TransformNormall(velocity, worldTransform_.matWorld_); 
		// 弾を生成し、初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);
		// 弾を登録する
	    gameScene_->AddEnemyBullet(newBullet);
}


//更新
void Enemy::Update() { 
	worldTransform_.UpdateMatrix();
	
	if (isdraw == true) {
		switch (phase_) {
		case Enemy::Phase::Approach:

			if (Approach() == true) {
				phase_ = Phase::Leave;
			}
			break;
		case Enemy::Phase::Leave:
			if (Leave() == true) {
				phase_ = Phase::Approach;
				ApproachFazeInitialize();
			}
			break;
		default:
			break;
		}
	}
}


//描画
void Enemy::Draw(ViewProjection view) { 
	if (isdraw == true) {
		// pureiya-
		model_->Draw(worldTransform_, view, textureHandle_);
	}
}