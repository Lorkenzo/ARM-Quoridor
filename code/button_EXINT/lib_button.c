
#include "stdio.h"
#include "lpc17xx.h"
#include "../joystick/joystick.h"
#include "../GLCD/GLCD.h" 
#include "button.h"
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

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */

  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT2_IRQn, 1);				 /* priority, the lower the better     */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, 2);				 
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, 3);				 /* decreasing priority	from EINT2->0	 */
}


void key1func(void){
	if(player_index==0 && wall1==0){
						 return;
								} 
	else if(player_index!=0 && wall2==0) return;
								
								enable_timer(1);
								if(wallflag==0){
									delete_direction();
									W_O[W_ind_O].x=103;
									W_O[W_ind_O].y=103;
									DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
								if(change%2==0){
									wall1--;
								}
								else {
									wall2--;
								}
								wallflag=1;
								return;
							}else{
								
								if(rotate==1){
									DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
									W_V[W_ind_V].x=0;
									W_V[W_ind_V].y=0;
								} else{
									DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
									W_O[W_ind_O].x=0;
									W_O[W_ind_O].y=0;
								}
							if(change%2==0){
									wall1++;
								}
								else {
									wall2++;
								}
							rotate=0;	
							wallflag=0;
							enlight_direction();
							}
}
void key2func(void){
	if(wallflag==1){
	if(rotate==0){
						rotate=1;
						DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
						W_V[W_ind_V].x=W_O[W_ind_O].x;
						W_V[W_ind_V].y=W_O[W_ind_O].y;
						DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
						W_O[W_ind_O].x=0;
						W_O[W_ind_O].y=0;	
					}
					else {
						rotate=0;
						DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
						W_O[W_ind_O].x=W_V[W_ind_V].x;
						W_O[W_ind_O].y=W_V[W_ind_V].y;
						DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
						W_V[W_ind_V].x=0;
						W_V[W_ind_V].y=0;
					}
				}
}
