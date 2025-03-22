#include "LPC17xx.h"

struct playerpos{
	int x;
	int y;
};


void move_bot(uint16_t Xpos,uint16_t Ypos);
void move_bot0(uint16_t Xpos,uint16_t Ypos);
void move_up(void);
void move_right(void);
void move_down(void);
void move_left(void);
void move_up_right(void);
void move_up_left(void);
void move_down_right(void);
void move_down_left(void);
void up_direction(void);
void right_direction(void);
void left_direction(void);
void down_direction(void);
void enlight_direction(void);
void delete_direction(void);
int check_trap_player(uint16_t Xpos,uint16_t Ypos,int player);
int trackmove(uint16_t Xpos,uint16_t Ypos);
void moveRecord(int change,int wallflag,int rotate,int xpos,int ypos);
void Textmessage(void);
