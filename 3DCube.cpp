#include "3DCube.hpp"
using namespace Matrix3D;

void onCubePaint(PAINTER* Painter) {
	/*
	
	重新定义CUBE数据结构实现正方体

	*/
	CUBE in_cube();
	CUBE out_cube();
	in_cube.vertexes[0] = { 1,0,0 };
	in_cube.vertexes[1] = { 0,0,0 };
	in_cube.vertexes[2] = { 0,1,0 };
	in_cube.vertexes[3] = { 0,0,1 };
	in_cube.vertexes[4] = { 1,1,0 };
	in_cube.vertexes[5] = { 1,1,1 };
	in_cube.vertexes[6] = { 1,0,1 };
	in_cube.vertexes[7] = { 0,1,1 };

	in_cube.planes[0].vertexIndex[0] = 0;

	OrthoProjection3D(&in_cube, &out_cube);

	for (int i = 0; i < 8; i++){
		Vector3dScaleMove(&(out_cube.vertexes[i]), 200, 200, 200);
	}
	Painter->BeginPainter();
	Painter->setPen(2, RGB(255, 255, 255));
	for (int i = 0; i < 8; i++){
		if (i != 7) {
			Painter->line(
				out_cube.vertexes[i].x,
				out_cube.vertexes[i].y,
				out_cube.vertexes[i + 1].x,
				out_cube.vertexes[i + 1].y);
		}
		else {
			Painter->line(out_cube.vertexes[i].x, out_cube.vertexes[i].y, out_cube.vertexes[0].x, out_cube.vertexes[0].y);
		}
	}
	Painter->EndPainter();
}