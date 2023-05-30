#include<WorldTransform.h>
#include<Matrix.h>
void WorldTransform::UpdateMatrix() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	
	if (parent_) {
		matWorld_ =Multiply(matWorld_,parent_->matWorld_);
	}

	//定数バッファに転送する
	TransferMatrix();
}