#include <cassert>
#include <player.h>
#include<Matrix.h>
#include<ImGuiManager.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<GameScene.h>

void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 position) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
	size = 1.0f;
	

}

Player::~Player() {
	
}

Vector3 Player::GetWorldPosition() { 
	return {
		worldTransform_.matWorld_.m[3][0], 
		worldTransform_.matWorld_.m[3][1],
	    worldTransform_.matWorld_.m[3][2]
	};
}

//当たった時の処理
void Player::OnCollision() {

}


void Player::Update() {
#pragma region 移動処理
	//移動
	Vector3 move = {0, 0, 0};
	//回転
	Vector3 rotate = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	const float kCharacterRoateS = (1.0f/120.0f)*(float)M_PI;

	const float kMoveLimitX = 20;
	const float kMoveLimitY = 20;


	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	
	//回転
	if (input_->PushKey(DIK_W)) {
		rotate.x -= kCharacterRoateS;
	}
	if (input_->PushKey(DIK_S)) {
		rotate.x += kCharacterRoateS;
	}

	if (input_->PushKey(DIK_D)) {
		rotate.y -= kCharacterRoateS;
	}

	if (input_->PushKey(DIK_A)) {
		rotate.y += kCharacterRoateS;
	}

	

	//移動処理
	worldTransform_.translation_ = AddVec3(worldTransform_.translation_, move);
	//回転処理
	worldTransform_.rotation_ = AddVec3(worldTransform_.rotation_,rotate);
	
// プレイヤーの移動制限
worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

worldTransform_.matWorld_ = MakeAffineMatrix(
	worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


//
worldTransform_.UpdateMatrix();

#pragma endregion
#pragma region Ammo

Attack();

#pragma endregion
#pragma region Debug
ImGui::Begin("Player Pos");
ImGui::Text(
	"%4.1f/%4.1f/%4.1f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	worldTransform_.translation_.z);
ImGui::End();
#pragma endregion	
}

//ベクトル変換
Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m) {
	return {
	    v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
	    v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
	    v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2],
	};
}


void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		//tamanosokudo
		const float lBulletSpeed = 5.0f;
		Vector3 velocity(0, 0, lBulletSpeed);
		//自機の向きに回転
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(
		    model_,
		    {
		        worldTransform_.matWorld_.m[3][0],
		        worldTransform_.matWorld_.m[3][1],
		        worldTransform_.matWorld_.m[3][2]
		    },
		    velocity);

		//弾を登録する
		gameScene_->AddPlayerBullet(newBullet);
	}
}


void Player::Draw(ViewProjection view) {
	//プレイヤー描画
	model_->Draw(worldTransform_, view, textureHandle_); 
}

void Player::SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }