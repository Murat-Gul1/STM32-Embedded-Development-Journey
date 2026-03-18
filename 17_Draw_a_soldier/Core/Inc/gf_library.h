#ifndef GF_LIBRARY_H_
#define GF_LIBRARY_H_
#include "stm32f4xx_hal.h"

#define COLOR_WHITE 65535
#define COLOR_BLACK 0
#define COLOR_RED 	63488

typedef struct {
	uint16_t x1,y1;
	uint16_t x2,y2;
	uint16_t color;
}Line;

typedef struct{
	uint16_t x;
	uint16_t y;
	uint16_t r;
	uint16_t color;
}Circle;

typedef struct{
	uint16_t x1,y1;
	uint16_t x2,y2;
	uint16_t x3,y3;
	uint16_t color;
}Triangle;


void draw_circle(Circle* circle);
void draw_line(Line* line);
void draw_circle_fill(Circle* circle);
void draw_triangle(Triangle* tri);
#endif