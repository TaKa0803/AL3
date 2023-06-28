#include <cassert>
#include <player.h>
#include<Matrix.h>
#include<ImGuiManager.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include<GameScene.h>
#include<Vector4.h>
#define WHITE 

Vector3 MulVec(Vector3 v1, Matrix4x4 m) {
	Vector4 a = {
		v1.x * m.m[0][0] + v1.y * m.m[1][0] + v1.z * m.m[2][0] +  m.m[3][0],
	    v1.x * m.m[0][1] + v1.y * m.m[1][1] + v1.z * m.m[2][1] +  m.m[3][1],
	    v1.x * m.m[0][2] + v1.y * m.m[1][2] + v1.z * m.m[2][2] +  m.m[3][2],
	    v1.x * m.m[0][3] + v1.y * m.m[1][3] + v1.z * m.m[2][3] +  m.m[3][3]	
	};
	if (a.w == 0) {
		assert(true);
	}
	/*
	return {
		a.x / a.w,
		a.y / a.w, 
		a.z / a.w
	};
	*/
	return {a.x , a.y , a.z };
}





void Player::Initialize(Model* model, uint32_t textureHandle,Vector3 position,uint32_t reticleTexture) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
	worldTransform_.translation_ = position;
	size = 1.0f;
	
	//3Dレティクルの初期化
	worldtransform3DReticle_.Initialize();
	reticleModel_ = model;
	reticleTextureHandle_ = reticleTexture;

	
	sprite2DReticle_ = Sprite::Create(
	    reticleTexture, {640, 360}, {1,1,1,1},
	    {0.5, 0.5});


}

Player::~Player() { delete sprite2DReticle_; }

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


void Player::Update(ViewProjection view) {
	
#pragma region マウス座標を取得する
	POINT mousePosition;
	//マウス座標（スクリーン座標）を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));
#pragma endregion
#pragma region 合成行列の逆行列
	Matrix4x4 matViewport = MakeViewPortMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matVPV =
	    Multiply(Multiply(view.matView, view.matProjection), matViewport);

	Matrix4x4 matInverseVPV = Inverse(matVPV);
#pragma endregion
	//スクリーン座標
	Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
	Vector3 posFar =  Vector3((float)mousePosition.x, (float)mousePosition.y, 1);


	//スクリーン座標系からワールド座標系へ
	posNear = Transform(posNear, matInverseVPV);
	posFar	= Transform(posFar,	 matInverseVPV);
#pragma region 3Dレティクルの座標計算
	//マウスレイの方向
	Vector3 mouseDirection = Subtract(posFar, posNear);
	mouseDirection = Normalize(mouseDirection);
	//カメラから標準オブジェクトの距離
	const float kDistanceTextObject=200; // 設定距離;
	worldtransform3DReticle_.translation_ =Add(posNear,Scalar(kDistanceTextObject, mouseDirection));
	worldtransform3DReticle_.UpdateMatrix();
#pragma endregion

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
		rotate.y += kCharacterRoateS;
	}

	if (input_->PushKey(DIK_A)) {
		rotate.y -= kCharacterRoateS;
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




Attack();

#pragma region Debug
ImGui::Begin("Player");
ImGui::Text(
	"PlayerPos:(%f,%f,%f)", worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
	worldTransform_.matWorld_.m[3][2]);
ImGui::Text(
	"2DReticle:(%f,%f)", sprite2DReticle_->GetPosition().x, sprite2DReticle_->GetPosition().y);
ImGui::Text("Near:(%+.2f,%+.2f,%+.2f)",posNear.x,posNear.y,posNear.z);
ImGui::Text("Far:(%+.2f,%+.2f,%+.2f)",posFar.x,posFar.y,posFar.z);
ImGui::Text(
	"3DReticle:(%+.2f,%+.2f,%+.2f)", worldtransform3DReticle_.translation_.x,
	worldtransform3DReticle_.translation_.y, worldtransform3DReticle_.translation_.z);
ImGui::End();
#pragma endregion
}




void Player::Attack() {
	if (input_->PushKey(DIK_SPACE)) {
		
		float lBulletSpeed = 5.0f;
		Vector3 velocity = {0, 0, lBulletSpeed};

		//自機から標準オブジェクトへのベクトル
		//Vector2 a = sprite2DReticle_->GetPosition();	
		Vector3 st = {
		    worldTransform_.matWorld_.m[3][0],
		    worldTransform_.matWorld_.m[3][1],
		    worldTransform_.matWorld_.m[3][2],
		};
		Vector3 ed = {
		    worldtransform3DReticle_.matWorld_.m[3][0], worldtransform3DReticle_.matWorld_.m[3][1],
		    worldtransform3DReticle_.matWorld_.m[3][2]
		};	
		velocity = Subtract(ed,st);
		
		//velocity = Subtract(worldtransform3DReticle_.translation_, worldTransform_.translation_);
		velocity = Scalar(lBulletSpeed, Normalize(velocity));
		
		
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
	reticleModel_->Draw(worldtransform3DReticle_,view ,reticleTextureHandle_);
}

void Player::SetParent(const WorldTransform* parent) {
	worldTransform_.parent_ = parent;
	worldtransform3DReticle_.parent_ = parent;
}

void Player::DrawUI() { 
	sprite2DReticle_->Draw();
}