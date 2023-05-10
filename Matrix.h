#pragma once
#include<Vector3.h>
#include<Matrix4x4.h>

/*
struct Matrix4x4 {
	float m[4][4];
};
*/
// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
// 単位行列の生成
Matrix4x4 MakeIdentity4x4();

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);
// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);
// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

//heikou
Vector3 AddVec3(Vector3 translate, Vector3 vec);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

//Matrix4x4 MakeAffineMatrix(Matrix4x4 scale, Matrix4x4 rotate, Matrix4x4 translate);
