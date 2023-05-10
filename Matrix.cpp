#include<Matrix.h>
#include<assert.h>
#include<cmath>

// 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 NEW = {
	    (m1.m[0][0] + m2.m[0][0]), (m1.m[0][1] + m2.m[0][1]), (m1.m[0][2] + m2.m[0][2]),
	    (m1.m[0][3] + m2.m[0][3]), (m1.m[1][0] + m2.m[1][0]), (m1.m[1][1] + m2.m[1][1]),
	    (m1.m[1][2] + m2.m[1][2]), (m1.m[1][3] + m2.m[1][3]), (m1.m[2][0] + m2.m[2][0]),
	    (m1.m[2][1] + m2.m[2][1]), (m1.m[2][2] + m2.m[2][2]), (m1.m[2][3] + m2.m[2][3]),
	    (m1.m[3][0] + m2.m[3][0]), (m1.m[3][1] + m2.m[3][1]), (m1.m[3][2] + m2.m[3][2]),
	    (m1.m[3][3] + m2.m[3][3]),
	};
	return NEW;
}
// 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 NEW = {
	    (m1.m[0][0] - m2.m[0][0]), (m1.m[0][1] - m2.m[0][1]), (m1.m[0][2] - m2.m[0][2]),
	    (m1.m[0][3] - m2.m[0][3]), (m1.m[1][0] - m2.m[1][0]), (m1.m[1][1] - m2.m[1][1]),
	    (m1.m[1][2] - m2.m[1][2]), (m1.m[1][3] - m2.m[1][3]), (m1.m[2][0] - m2.m[2][0]),
	    (m1.m[2][1] - m2.m[2][1]), (m1.m[2][2] - m2.m[2][2]), (m1.m[2][3] - m2.m[2][3]),
	    (m1.m[3][0] - m2.m[3][0]), (m1.m[3][1] - m2.m[3][1]), (m1.m[3][2] - m2.m[3][2]),
	    (m1.m[3][3] - m2.m[3][3]),
	};
	return NEW;
};
// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 NEW = {
	    m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
	        m1.m[0][3] * m2.m[3][0],
	    m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
	        m1.m[0][3] * m2.m[3][1],
	    m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
	        m1.m[0][3] * m2.m[3][2],
	    m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
	        m1.m[0][3] * m2.m[3][3],

	    m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
	        m1.m[1][3] * m2.m[3][0],
	    m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
	        m1.m[1][3] * m2.m[3][1],
	    m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
	        m1.m[1][3] * m2.m[3][2],
	    m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
	        m1.m[1][3] * m2.m[3][3],

	    m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
	        m1.m[2][3] * m2.m[3][0],
	    m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
	        m1.m[2][3] * m2.m[3][1],
	    m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
	        m1.m[2][3] * m2.m[3][2],
	    m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
	        m1.m[2][3] * m2.m[3][3],

	    m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
	        m1.m[3][3] * m2.m[3][0],
	    m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
	        m1.m[3][3] * m2.m[3][1],
	    m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
	        m1.m[3][3] * m2.m[3][2],
	    m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
	        m1.m[3][3] * m2.m[3][3],
	};

	return NEW;
}
// 逆行列
Matrix4x4 Inverse(const Matrix4x4& m) {
	float A;
	A = 1.0f / (+m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3] +
	            m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1] +
	            m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]

	            - m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1] -
	            m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3] -
	            m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]

	            - m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3] -
	            m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1] -
	            m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]

	            + m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1] +
	            m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3] +
	            m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]

	            + m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3] +
	            m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1] +
	            m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]

	            - m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1] -
	            m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3] -
	            m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]

	            - m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0] -
	            m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0] -
	            m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]

	            + m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0] +
	            m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0] +
	            m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Matrix4x4 NEW = {
	    A * (m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] +
	         m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][3] * m.m[2][2] * m.m[3][1] -
	         m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][2]),

	    A * (-m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] -
	         m.m[0][3] * m.m[2][1] * m.m[3][2] + m.m[0][3] * m.m[2][2] * m.m[3][1] +
	         m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][2]),

	    A * (m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] +
	         m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][3] * m.m[1][2] * m.m[3][1] -
	         m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][2]),

	    A * (-m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] -
	         m.m[0][3] * m.m[1][1] * m.m[2][2] + m.m[0][3] * m.m[1][2] * m.m[2][1] +
	         m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][2]),

	    //
	    A * (-m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] -
	         m.m[1][3] * m.m[2][0] * m.m[3][2] + m.m[1][3] * m.m[2][2] * m.m[3][0] +
	         m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][2]),

	    A * (m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] +
	         m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][3] * m.m[2][2] * m.m[3][0] -
	         m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][2]),

	    A * (-m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] -
	         m.m[0][3] * m.m[1][0] * m.m[3][2] + m.m[0][3] * m.m[1][2] * m.m[3][0] +
	         m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][2]),

	    A * (m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] +
	         m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][3] * m.m[1][2] * m.m[2][0] -
	         m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][2]),
	    //
	    A * (-m.m[1][0] * m.m[2][1] * m.m[3][3] - m.m[1][1] * m.m[2][3] * m.m[3][0] -
	         m.m[1][3] * m.m[2][0] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][0] +
	         m.m[1][1] * m.m[2][0] * m.m[3][3] + m.m[1][0] * m.m[2][3] * m.m[3][1]),

	    A * (m.m[0][0] * m.m[2][1] * m.m[3][3] + m.m[0][1] * m.m[2][3] * m.m[3][0] +
	         m.m[0][3] * m.m[2][0] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][0] -
	         m.m[0][1] * m.m[2][0] * m.m[3][3] - m.m[0][0] * m.m[2][3] * m.m[3][1]),

	    A * (-m.m[0][0] * m.m[1][1] * m.m[3][3] - m.m[0][1] * m.m[1][3] * m.m[3][0] -
	         m.m[0][3] * m.m[1][0] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][0] +
	         m.m[0][1] * m.m[1][0] * m.m[3][3] + m.m[0][0] * m.m[1][3] * m.m[3][1]),

	    A * (m.m[0][0] * m.m[1][1] * m.m[2][3] + m.m[0][1] * m.m[1][3] * m.m[2][0] +
	         m.m[0][3] * m.m[1][0] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][0] -
	         m.m[0][1] * m.m[1][0] * m.m[2][3] - m.m[0][0] * m.m[1][3] * m.m[2][1]),
	    //
	    A * (-m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] -
	         m.m[1][2] * m.m[2][0] * m.m[3][1] + m.m[1][2] * m.m[2][1] * m.m[3][0] +
	         m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][0] * m.m[2][2] * m.m[3][1]),

	    A * (m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] +
	         m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][2] * m.m[2][1] * m.m[3][0] -
	         m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][2] * m.m[3][1]),

	    A * (-m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] -
	         m.m[0][2] * m.m[1][0] * m.m[3][1] + m.m[0][2] * m.m[1][1] * m.m[3][0] +
	         m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][0] * m.m[1][2] * m.m[3][1]),

	    A * (m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] +
	         m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][2] * m.m[1][1] * m.m[2][0] -
	         m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][2] * m.m[2][1]),

	};
	return NEW;
}

// 転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 NEW = {
	    m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0], m.m[0][1], m.m[1][1],
	    m.m[2][1], m.m[3][1], m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2],
	    m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]

	};
	return NEW;
}
// 単位行列の生成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 NEW = {
	    1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	};
	return NEW;
}




// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 NEW = {
	    1,
	    0,
	    0,
	    0,
	    0,
	    std::cos(radian),
	    std::sin(radian),
	    0,
	    0,
	    -std::sin(radian),
	    std::cos(radian),
	    0,
	    0,
	    0,
	    0,
	    1,
	};
	return NEW;
}
// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 NEW = {
	    std::cos(radian), 0, -std::sin(radian), 0, 0, 1, 0, 0,
	    std::sin(radian), 0, std::cos(radian),  0, 0, 0, 0, 1,
	};
	return NEW;
}
// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 NEW = {
	    std::cos(radian),
	    std::sin(radian),
	    0,
	    0,
	    -std::sin(radian),
	    std::cos(radian),
	    0,
	    0,
	    0,
	    0,
	    1,
	    0,
	    0,
	    0,
	    0,
	    1,
	};
	return NEW;
}



// ３次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	// Scale
	Matrix4x4 S = {scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1};
	// Rotate
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 R = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	// translate
	Matrix4x4 T = {
	    1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translate.x, translate.y, translate.z, 1,
	};

	Matrix4x4 NEW = Multiply(S, Multiply(R, T));
	return NEW;
}

Vector3 AddVec3(Vector3 translate, Vector3 vec) {
	return {
		translate.x+vec.x,
		translate.y+vec.y,
		translate.z+vec.z
	};
}




/*
Matrix4x4 MakeAffineMatrix(Matrix4x4 scale, Matrix4x4 rotate, Matrix4x4 translate) {
	
	return Multiply(scale, Multiply(rotate, translate));

}
*/