/*
 * gf_library.c
 *
 *  Created on: 17 Mar 2026
 *      Author: Murat
 */
#include "gf_library.h"
#include <stdio.h>
#include <string.h>
extern UART_HandleTypeDef huart2;


void send_nextion(char* cmd){
	const uint8_t end[] = {0xFF , 0xFF, 0xFF};
	HAL_UART_Transmit(&huart2,(uint8_t *)cmd,strlen(cmd),100);
	HAL_UART_Transmit(&huart2,end,3,100);
}

void draw_line(Line* line){
	char buffer[64];
	sprintf(buffer,"line %d,%d,%d,%d,%d",line->x1,line->y1,line->x2,line->y2,line->color);
	send_nextion(buffer);
}

void draw_circle_fill(Circle* circle){
	char buffer[64];
	sprintf(buffer,"cirs %d,%d,%d,%d",circle->x,circle->y,circle->r,circle->color);
	send_nextion(buffer);
}

void draw_circle(Circle* circle){
	char buffer[64];
	sprintf(buffer,"cir %d,%d,%d,%d",circle->x,circle->y,circle->r,circle->color);
	send_nextion(buffer);
}

void draw_triangle(Triangle* tri){
	Line edge1 ={tri->x1,tri->y1,tri->x2,tri->y2,tri->color};
	draw_line(&edge1);
	Line edge2 ={tri->x2,tri->y2,tri->x3,tri->y3,tri->color};
	draw_line(&edge2);
	Line edge3 ={tri->x3,tri->y3,tri->x1,tri->y1,tri->color};
	draw_line(&edge3);

}
