#pragma once
#ifndef _DIAMONDMAIN_
#define _DIAMONDMAIN_
#include <random>
#include "PaintFramework.hpp"

using std::default_random_engine;
using std::uniform_int_distribution;

extern void onDiamondPaint(PAINTER* Painter, int screen_width, int screen_height,int n, bool isAnimated = false);

#endif // !_DIAMONDMAIN_

