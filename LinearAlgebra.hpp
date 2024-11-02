#pragma once
#ifndef _LINEARALGEBRA_
#define _LINEARALGEBRA_

namespace Matrix3D {
	struct Vector3D {
		float x;
		float y;
		float z;
		float w = 1;
	};

	// ƽ��
	struct Plane {
		int vertexNum = 4;
		int vertexIndex[4];	// ����1~4���
	};

	// ������
	struct CUBE {
	public:
		CUBE(Vector3D v1, Vector3D v2);
		Vector3D vertexes[8];	// ���㼯
		Plane planes[6];
	};
	
	// 4x4�����������˷�
	void MatrixMultiply3D_4x4(Vector3D* vector3d, float matrix[4][4]);
	// 3D����ͶӰ�任
	void OrthoProjection3D(CUBE* in_cube, CUBE* out_cube);

	// ��άƽ�Ʊ任
	//void Vector3dPosMove(Vector3D* vector3d, float dx, float dy, float dz);
	// ��ά�����任
	void Vector3dScaleMove(Vector3D* vector3d, float sx, float sy, float sz);
	// ��ά��ת�任
	//void Vector3dRotationMove(Vector3D* vector3d, float beta, float relative_x, float relative_y);
}

namespace Matrix2D {
	struct Vector2D {
		float x;
		float y;
		float w = 1;
	};

	// 3x3�����������˷�
	void MatrixMultiply2D_3x3(Vector2D* vector2d, float matrix[3][3]);
	// ƽ�Ʊ任
	void Vector2dPosMove(Vector2D* vector2d, float dx, float dy);	
	// �����任
	void Vector2dScaleMove(Vector2D* vector2d, float sx, float sy);	
	// ���������һ����ת�任
	void Vector2dRotationMove(Vector2D* vector2d, float beta, float relative_x, float relative_y);	

};

#endif