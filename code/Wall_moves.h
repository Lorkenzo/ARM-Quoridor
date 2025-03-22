#include "LPC17xx.h"

struct wall{
	int x;
	int y;
};

void wall_up(void);
void wall_right(void);
void wall_down(void);
void wall_left(void);
int check_wall_up(uint16_t Xpos,uint16_t Ypos);
int check_wall_down(uint16_t Xpos,uint16_t Ypos);
int check_wall_right(uint16_t Xpos,uint16_t Ypos);
int check_wall_left(uint16_t Xpos,uint16_t Ypos);
int check_existing_wall(uint16_t Xwall,uint16_t Ywall);
void place_wall_bot(void);
