/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        High level joystick management functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "stdio.h"
#include "lpc17xx.h"
#include "joystick.h"
#include "../GLCD/GLCD.h" 
#include "../button_EXINT/button.h"
#include "../TouchPanel/TouchPanel.h"
#include "..\timer\timer.h"
#include "../joystick/joystick.h"
#include "../Moves.h"
#include "../Wall_moves.h"
#include "../Game_mode.h"
#define DIST_MOVE 34

extern int player_index;
extern int change;
extern struct playerpos player[2];
extern int black1;
extern int black2;
extern int jumpflag;
extern int oblique;
extern int oblique1;
extern int wallflag;
extern int move;
extern int count_timer;
extern struct wall W_O[16];
extern struct wall W_V[16];
extern int W_ind_O;
extern int W_ind_V;
extern int rotate;
extern char wall1s[5];
extern char wall2s[5];
extern int wall1;
extern int wall2;
/*----------------------------------------------------------------------------
  Function joystick
 *----------------------------------------------------------------------------*/
//------------------JOYSTICK INPUT------------
void joy_up(void){
	if (wallflag==0){
									
								//caso in cui l'avversario è nella casella sopra e ha il muro sopra
								if(player[player_index].y-DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x && check_wall_up(player[player_index].x,player[player_index].y-DIST_MOVE)==1) {
									if(oblique>0 && check_wall_right(player[player_index].x,player[player_index].y-DIST_MOVE)==0){
										oblique=0;
										if(player[player_index].x+DIST_MOVE<240) 
										{move=5;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,White);
											return;
										}
									} //up-right
									
									if(oblique1>0 && check_wall_left(player[player_index].x,player[player_index].y-DIST_MOVE)==0) {
										oblique1=0;
										if(player[player_index].x-DIST_MOVE>0) 
										{move=8;	
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,White);
											return;
									}} else return;	//up-left
								}
								//avversario a sinistra con muro dietro
								if(player[player_index].x-DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y && check_wall_left(player[player_index].x-DIST_MOVE,player[player_index].y)==1) 
								{
								if(oblique1>0 && check_wall_up(player[player_index].x-DIST_MOVE,player[player_index].y)==0){
									oblique1=0;
										if(player[player_index].y-DIST_MOVE>0) 
										{move=8;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,White);
											return;
								}}	//up-left
									}
								//avversario a destra con muro dietro
								if(player[player_index].x+DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y && check_wall_right(player[player_index].x+DIST_MOVE,player[player_index].y)==1) 
							{
									if(oblique>0 && check_wall_up(player[player_index].x+DIST_MOVE,player[player_index].y)==0) {
										oblique=0;
										if(player[player_index].y-DIST_MOVE>0){ 
											move=5;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,White);
											return;
									}}	//up-right
									}	
								if((check_wall_up(player[player_index].x,player[player_index].y)==1 || player[player_index].y-DIST_MOVE<0)) return;
									move=1;
									
									enlight_direction();
									if(player[player_index].y-DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x ){
										player_index? DrawPlayerDir(player[player_index].x,player[player_index].y-2*DIST_MOVE,Red)
									:DrawPlayerDir(player[player_index].x,player[player_index].y-2*DIST_MOVE,White);
									}
										else{
									player_index? DrawPlayerDir(player[player_index].x,player[player_index].y-DIST_MOVE,Red)
									:DrawPlayerDir(player[player_index].x,player[player_index].y-DIST_MOVE,White);
										}
						}
						else{
							wall_up();
						}
						
}
void joy_right(void){
		if(wallflag==0){	
								//avversario a destra con muro dietro	a destra
								if(player[player_index].x+DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y && check_wall_right(player[player_index].x+DIST_MOVE,player[player_index].y)==1) 
								{
								if(oblique>0 && check_wall_down(player[player_index].x+DIST_MOVE,player[player_index].y)==0){
									oblique=0;
									if(player[player_index].y+DIST_MOVE<240) {
											move=6;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,White);
										  return;
								}} else return;}//down-right}
								
								//avversario in basso con muro dietro
								if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x && check_wall_down(player[player_index].x,player[player_index].y+DIST_MOVE)==1) {
									if(oblique>0 && check_wall_right(player[player_index].x,player[player_index].y+DIST_MOVE)==0) {
										oblique=0;
											if(player[player_index].x+DIST_MOVE<240) {
											move=6;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,White);
											return;
										};
									}; //down-right
									}
									
								if((check_wall_right(player[player_index].x,player[player_index].y)==1 || player[player_index].x+DIST_MOVE>240)) return;	
								move=2;
									enlight_direction();
									if(player[player_index].x+DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
										player_index? DrawPlayerDir(player[player_index].x+2*DIST_MOVE,player[player_index].y,Red)
									:DrawPlayerDir(player[player_index].x+2*DIST_MOVE,player[player_index].y,White);
									}else{
									player_index? DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y,Red)
									:DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y,White);
									}
							}
							else{
							wall_right();
							}

}

void joy_left(void){
		if(wallflag==0){
							//avversario a sinistra con muro dietro a sinistra
							if(player[player_index].x-DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y && check_wall_left(player[player_index].x-DIST_MOVE,player[player_index].y)==1) 
							{
								if(oblique>0 && check_wall_down(player[player_index].x-DIST_MOVE,player[player_index].y)==0){ 
									oblique=0;
									if(player[player_index].y+DIST_MOVE<240)
									{		move=7;
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,White);
										return;
								}} else return; //down-left
							}
							
							//avversario in basso con muro dietro
							if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x && check_wall_down(player[player_index].x,player[player_index].y+DIST_MOVE)==1){
								if(oblique>0 && check_wall_left(player[player_index].x,player[player_index].y+DIST_MOVE)==0) {
									oblique=0;
										if(player[player_index].x-DIST_MOVE>0) 
								{			move=7;	
											enlight_direction();
											player_index? DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,Red)
											:DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,White);
										return;
								}}	//down-left
								}
							
							if((check_wall_left(player[player_index].x,player[player_index].y)==1 || player[player_index].x-DIST_MOVE<0)) return;
							move=3;
								
								enlight_direction();
								if(player[player_index].x-DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
								player_index? DrawPlayerDir(player[player_index].x-2*DIST_MOVE,player[player_index].y,Red)
								:DrawPlayerDir(player[player_index].x-2*DIST_MOVE,player[player_index].y,White);
								}
								else{
								player_index? DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y,Red)
								:DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y,White);
								}
							}
							else{
							wall_left();
							}	
}

void joy_down(void){
		if(wallflag==0){
							if(check_wall_down(player[player_index].x,player[player_index].y)==1 || player[player_index].y+DIST_MOVE>240) return;
							
							//player in basso con il muro in basso
							if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x && check_wall_down(player[player_index].x,player[player_index].y+DIST_MOVE)==1) 
							{
							return;}
							
							move=4;
								enlight_direction();
							if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x){
									player_index? DrawPlayerDir(player[player_index].x,player[player_index].y+2*DIST_MOVE,Red)
								:DrawPlayerDir(player[player_index].x,player[player_index].y+2*DIST_MOVE,White);
							}
							else {
								player_index? DrawPlayerDir(player[player_index].x,player[player_index].y+DIST_MOVE,Red)
								:DrawPlayerDir(player[player_index].x,player[player_index].y+DIST_MOVE,White);
							}
							}
							else{
							wall_down();
							}
}

void joy_select(){
	
	if(wallflag==0){
			  switch(move){
					case 1: 
						move_up();
						count_timer=0;
						move=-1;
						break;
					case 2: 
						move_right();
						count_timer=0;
						move=-1;
						break;
					case 3:
						move_left();
						count_timer=0;
						move=-1;
						break;
					case 4:
						move_down();
						count_timer=0;
						move=-1;
						break;
					case 5:
						move_up_right();
						count_timer=0;
						move=-1;
						break;
					case 6:
						move_down_right();
						count_timer=0;
						move=-1;
						break;
					case 7:
						move_down_left();
						count_timer=0;
						move=-1;
						break;
					case 8:
						move_up_left();
						count_timer=0;
						move=-1;
						break;
				
					default:
						break;
				}
				//salvataggio mossa
				if(move!=0){moveRecord(player_index,wallflag,rotate,player[player_index].x,player[player_index].y); }
					else if(move==0){moveRecord(player_index,0,1,player[player_index].x,player[player_index].y);}
					
						}else{
							//controllo muro gia posizionato in una determinata posizione;
							if(rotate==0){
								if(check_existing_wall(W_O[W_ind_O].x,W_O[W_ind_O].y)==1) return;
							} 
							else {
								if(check_existing_wall(W_V[W_ind_V].x,W_V[W_ind_V].y)==1) return;
							}
							//controllo via di uscita possibile per entrambi i giocatori in caso di posizionamento del muro
							if(rotate==1) {
								W_ind_V++;}
							else {
								W_ind_O++;}
							if((player_index==0 && (check_trap_player(player[player_index].x,player[player_index].y,1)==0 || check_trap_player(player[player_index?0:1].x,player[player_index?0:1].y,2)==0))
									|| (player_index==1 && (check_trap_player(player[player_index].x,player[player_index].y,2)==0 || check_trap_player(player[player_index?0:1].x,player[player_index?0:1].y,1)==0))) {
								if(rotate==1) {
								W_ind_V--;}
								else {
								W_ind_O--;}
								return;
							}
							//muro posizionato, salvataggio mossa
							if(rotate==1) {
								moveRecord(player_index,wallflag,rotate,W_V[W_ind_V-1].x,W_V[W_ind_V-1].y);}
							else {
								moveRecord(player_index,wallflag,rotate,W_O[W_ind_O-1].x,W_O[W_ind_O-1].y);}
							
							move=-1;
							wallflag=0;
							rotate=0;
							sprintf(wall1s,"%d",wall1);
							sprintf(wall2s,"%d",wall2);
							GUI_Text(15, 280, (uint8_t *) wall2s, Red, Black);
							GUI_Text(173, 280, (uint8_t *) wall1s, White, Black);
							if(wall1==0) {
								GUI_Text(163, 280, (uint8_t *) "No walls", White, Black);
								GUI_Text(163, 295, (uint8_t *) "Use Token", White, Black);
							}
							if(wall2==0){
								GUI_Text(4, 280, (uint8_t *) "No walls", Red, Black);
								GUI_Text(4, 295, (uint8_t *) "Use Token", Red, Black);
							}
							count_timer=0;
							disable_timer(1);
						}
}
