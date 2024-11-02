#include "LinearAlgebra.hpp"
#define PI 3.1415926535
#include <cmath>

/*

CUBE初始化
v1 左下角
v2 右上角

*/
Matrix3D::CUBE::CUBE(Vector3D v1, Vector3D v2) {
	Vector3D buffer;
	this->vertexes[0] = v1;
	this->vertexes[7] = v2;

	this->vertexes[1] = buffer;
	this->vertexes[2] = buffer;
	this->vertexes[3] = buffer;
	this->vertexes[4] = buffer;
	this->vertexes[5] = buffer;
	this->vertexes[6] = buffer;

	planes[0].vertexIndex[0] = 4;
	planes[0].vertexIndex[1] = 5;
	planes[0].vertexIndex[2] = 7;
	planes[0].vertexIndex[3] = 6;

	planes[1].vertexIndex[0] = 0;
	planes[1].vertexIndex[1] = 3;
	planes[1].vertexIndex[2] = 2;
	planes[1].vertexIndex[3] = 1;

	planes[2].vertexIndex[0] = 0;
	planes[2].vertexIndex[1] = 4;
	planes[2].vertexIndex[2] = 6;
	planes[2].vertexIndex[3] = 3;

	planes[3].vertexIndex[0] = 1;
	planes[3].vertexIndex[1] = 2;
	planes[3].vertexIndex[2] = 7;
	planes[3].vertexIndex[3] = 5;

	planes[4].vertexIndex[0] = 2;
	planes[4].vertexIndex[1] = 3;
	planes[4].vertexIndex[2] = 6;
	planes[4].vertexIndex[3] = 7;

	planes[5].vertexIndex[0] = 0;
	planes[5].vertexIndex[1] = 1;
	planes[5].vertexIndex[2] = 5;
	planes[5].vertexIndex[3] = 4;
	return;
}

void Matrix3D::Vector3dScaleMove(Vector3D* vector3d, float sx, float sy, float sz) {
	float matrix[4][4] = {
		{sx, 0, 0, 0},
		{0, sy, 0, 0},
		{0,  0, sz,0},
		{0,  0, 0, 1},
	};
	MatrixMultiply3D_4x4(vector3d, matrix);
	return;
}

void Matrix3D::OrthoProjection3D(CUBE* in_cube, CUBE* out_cube) {
	Vector3D vector3d = { 0 };
	// 构造正交投影矩阵
	float r_l = in_cube->vertexes[7].x - in_cube->vertexes[0].x;
	float rAl = in_cube->vertexes[7].x + in_cube->vertexes[0].x;
	float t_b = in_cube->vertexes[7].y - in_cube->vertexes[0].y;
	float tAb = in_cube->vertexes[7].y + in_cube->vertexes[0].y;
	float n_f = in_cube->vertexes[7].z - in_cube->vertexes[0].z;
	float nAf = in_cube->vertexes[7].z + in_cube->vertexes[0].z;
	float matrix[4][4] = {
		{2 / r_l, 0, 0, -(rAl / r_l)},
		{0, 2 / t_b, 0, -(tAb / t_b)},
		{0, 0, 2 / n_f, -(nAf / n_f)},
		{0, 0, 0, 1},
	};

	// 正交投影
	for (int i = 0; i < 8; i++){
		vector3d = in_cube->vertexes[i];
		MatrixMultiply3D_4x4(&vector3d, matrix);
		out_cube->vertexes[i] = vector3d;
	}
	return;
}

void Matrix3D::MatrixMultiply3D_4x4(Vector3D* vector3d, float matrix[4][4]) {
	vector3d->x = matrix[0][0] * vector3d->x + matrix[0][1] * vector3d->y + matrix[0][2] * vector3d->z + matrix[0][3] * vector3d->w;
	vector3d->y = matrix[1][0] * vector3d->x + matrix[1][1] * vector3d->y + matrix[1][2] * vector3d->z + matrix[1][3] * vector3d->w;
	vector3d->z = matrix[2][0] * vector3d->x + matrix[2][1] * vector3d->y + matrix[2][2] * vector3d->z + matrix[2][3] * vector3d->w;
	vector3d->w = matrix[3][0] * vector3d->x + matrix[3][1] * vector3d->y + matrix[3][2] * vector3d->z + matrix[3][3] * vector3d->w;
	return;
}

void Matrix2D::MatrixMultiply2D_3x3(Vector2D* vector2d, float matrix[3][3]) {
	vector2d->x = matrix[0][0] * vector2d->x + matrix[0][1] * vector2d->y + matrix[0][2] * vector2d->w;
	vector2d->y = matrix[1][0] * vector2d->x + matrix[1][1] * vector2d->y + matrix[1][2] * vector2d->w;
	vector2d->w = matrix[2][0] * vector2d->x + matrix[2][1] * vector2d->y + matrix[2][2] * vector2d->w;
	return;
}

void Matrix2D::Vector2dPosMove(Vector2D* vector2d, float dx, float dy) {
	float matrix[3][3] = { 
		{1,0,dx},
		{0,1,dy},
		{0,0, 1} 
	};

	MatrixMultiply2D_3x3(vector2d, matrix);
	return;
}

void Matrix2D::Vector2dScaleMove(Vector2D* vector2d, float sx, float sy) {
	float matrix[3][3] = {
		{sx,0,0},
		{0,sy,0},
		{0,0, 1}
	};

	MatrixMultiply2D_3x3(vector2d, matrix);
	return;
}

void Matrix2D::Vector2dRotationMove(Vector2D* vector2d, float beta, float relative_x, float relative_y) {
	float angle = beta * PI / 180;
	float matrix[3][3] = {
		{cos(angle),-sin(angle),0},
		{sin(angle),cos(angle),0},
		{0,0,1}
	};
	Vector2dPosMove(vector2d, -relative_x, -relative_y);
	MatrixMultiply2D_3x3(vector2d, matrix);
	Vector2dPosMove(vector2d, relative_x, relative_y);
	return;
}