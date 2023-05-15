#include <cassert>
#include <player.h>
#include<Matrix.h>
#include<ImGuiManager.h>

#define _USE_MATH_DEFINES
#include<math.h>


void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();

	
}

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Update() {
	worldTransform_.UpdateMatrix();
	//移動
	Vector3 move = {0, 0, 0};
	//回転
	Vector3 rotate = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;

	const float kCharacterRoateS = (1.0f/60.0f)*(float)M_PI;


	const float kMoveLimitX = 10;
	const float kMoveLimitY = 10;





#pragma region// 移動処理
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

#pragma endregion


Attack();
//弾更新
for (PlayerBullet* bullet:bullets_) {
		bullet->Update();
}
	
	ImGui::Begin("Player Pos");
	ImGui::Text(
	    "%4.1f/%4.1f/%4.1f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z);
	ImGui::End();
	
}

void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		
		//弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//弾を登録する
		bullets_.push_back(newBullet);
	}
}


void Player::Draw(ViewProjection view) {
	//プレイヤー描画
	model_->Draw(worldTransform_, view, textureHandle_); 
	//弾描画
	for (PlayerBullet*bullet:bullets_) {
		bullet->Draw(view);
	}
}