#include <Matrix.h>
#include <EnemyBullet.h>
#include <assert.h>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);
	// モデル
	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("red.png");
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	size = 1.0f;
}

void EnemyBullet::Update() {

	
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	if (isDead_ == false) {
		// 座標の移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// 行列の更新
		
	}
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::OnCollision() { isDead_ = true; }

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}