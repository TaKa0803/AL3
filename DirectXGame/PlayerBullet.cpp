#include<PlayerBullet.h>
#include<assert.h>
#include<Matrix.h>

void PlayerBullet::Initialize(Model* model, const Vector3& position,const Vector3& velocity) {
	//NULLポインタチェック
	assert(model);
	// モデル
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	if (isDead_ == false) {

		// 座標の移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

		// 行列の更新
		worldTransform_.UpdateMatrix();
	}
}

void PlayerBullet::OnCollision() { isDead_ = false; }

void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}