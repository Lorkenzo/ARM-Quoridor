/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "stdio.h"
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h" 
#include "../button_EXINT/button.h"
#include "../TouchPanel/TouchPanel.h"
#include "..\timer\timer.h"
#include "../joystick/joystick.h"
#include "../Moves.h"
#include "../Wall_moves.h"
#include "../Game_mode.h"
#define DIST_MOVE 34

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
//------VARIABILI----------
volatile int down0=0;
volatile int down1=0;
volatile int down2=0;
extern int change;
extern volatile int count_timer;
extern struct playerpos player[2];
extern struct wall W_O[16];
extern struct wall W_V[16];
extern int black1;
extern int black2;
int move;
int wallflag;
int wall1;
int wall2;
int W_ind_O;
int W_ind_V;
int rotate;
extern int player_index;
char wall1s[5]="";
char wall2s[5]="";
int oblique=0;
int oblique1=0;
extern int num_board;
extern int num_player;
extern int recording;
struct Game_Mode game;
extern int start;

void RIT_IRQHandler (void)
{					
	static int joy=0;
		
	//JOYSTICK IN ALTO
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && (LPC_GPIO1->FIOPIN & (1<<28))!=0 && (LPC_GPIO1->FIOPIN & (1<<27))!=0){
			
		/* Joytick pressed */
   		joy++;
  		switch(joy){
			case 1:
				
				switch (game.gamestate){
						case BOARD_CHOOSE:
								change_option();
							break;
						case PLAYERS_CHOOSE:
								change_option();
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_up();
							break;
						
						case ONE_BOARD_ONE_PLAYER:
							joy_up();
						break;
						
						case TWO_BOARD_TWO_PLAYER:
							joy_up();
							break;
						default:
							break;
					}
				
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK IN ALTO A DESTRA
	else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && (LPC_GPIO1->FIOPIN & (1<<28))==0){
				oblique++;
			
				
		/* Joytick pressed */
   		joy++;
  		switch(joy){

			case 1:
				
				switch (game.gamestate){
						case BOARD_CHOOSE:
								change_option();
							break;
						case PLAYERS_CHOOSE:
								change_option();
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_up();
							break;
						
						case ONE_BOARD_ONE_PLAYER:
							joy_up();
						break;
						
						case TWO_BOARD_TWO_PLAYER:
							joy_up();
							break;
						default:
							break;
					}
				
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK IN ALTO A SINISTRA
	else if((LPC_GPIO1->FIOPIN & (1<<29)) == 0 && (LPC_GPIO1->FIOPIN & (1<<27))==0){
				oblique1++;
				
		/* Joytick pressed */
   		joy++;
  		switch(joy){
			case 1:
				
				switch (game.gamestate){
						case BOARD_CHOOSE:
								change_option();
							break;
						case PLAYERS_CHOOSE:
								change_option();
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_up();
							break;
						
						case ONE_BOARD_ONE_PLAYER:
							joy_up();
						break;
						
						case TWO_BOARD_TWO_PLAYER:
							joy_up();
							break;
						default:
							break;
					}
				
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK A DESTRA
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && (LPC_GPIO1->FIOPIN & (1<<26))!=0){
	
		/* Joytick pressed */
 		joy++;
		switch(joy){
			case 1:
				switch (game.gamestate){
						case BOARD_CHOOSE:
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_right();
							break;
							
							case ONE_BOARD_ONE_PLAYER:
							joy_right();	
							break;
							
							case TWO_BOARD_TWO_PLAYER:
								joy_right();	
							break;
							default:
								break;
					}
			  
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK IN BASSO A DESTRA
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && (LPC_GPIO1->FIOPIN & (1<<26))==0){
			oblique++;
			
		/* Joytick  pressed */
 		joy++;
		switch(joy){
			
			case 1:
				switch (game.gamestate){
						case BOARD_CHOOSE:
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_right();
							break;
							
							case ONE_BOARD_ONE_PLAYER:
							joy_right();	
							break;
							
							case TWO_BOARD_TWO_PLAYER:
								joy_right();	
							break;
							default:
								break;
					}
			  
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK A SINISTRA
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && (LPC_GPIO1->FIOPIN & (1<<26))!=0){	
		/* Joytick pressed */
		joy++;
		switch(joy){
			case 1:
				switch (game.gamestate){
						case BOARD_CHOOSE:
							
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_left();
							break;
							
							case ONE_BOARD_ONE_PLAYER:
							joy_left();	
							break;
							
							case TWO_BOARD_TWO_PLAYER:
								joy_left();
							break;
							default:
								break;
					}
			  
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK IN BASSO A SINISTRA
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && (LPC_GPIO1->FIOPIN & (1<<26))==0){	
			oblique++;
				
		/* Joytick pressed */
		joy++;
		switch(joy){
			case 1:
				switch (game.gamestate){
						case BOARD_CHOOSE:
							
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_left();
							break;
							
							case ONE_BOARD_ONE_PLAYER:
							joy_left();	
							break;
							
							case TWO_BOARD_TWO_PLAYER:
								joy_left();
							break;
							default:
								break;
					}
			  
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK IN BASSO
	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick pressed */
		joy++;
		switch(joy){
			case 1:
				switch (game.gamestate){
						case BOARD_CHOOSE:
								change_option();
							break;
						case PLAYERS_CHOOSE:
								change_option();
							break;
						case ONE_BOARD_TWO_PLAYERS:	
							joy_down();
							break;
						case ONE_BOARD_ONE_PLAYER:
							joy_down();
						break;
						
						case TWO_BOARD_TWO_PLAYER:
							joy_down();
							break;
						default:
							break;
					}
				
				break;
			
			default:
				break;
		}
	}
	//JOYSTICK SELECT
	else if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick pressed */
		joy++;
		switch(joy){
			case 1:
			
				switch (game.gamestate){
						case BOARD_CHOOSE:
							game.gamestate=PLAYERS_CHOOSE;
							if(num_board==2)num_player=2;
							else num_player=1;
							change_mode();
							break;
						case PLAYERS_CHOOSE:
							if(num_board==1 && num_player==2) game.gamestate=ONE_BOARD_TWO_PLAYERS;
							if(num_board==1 && num_player==1) game.gamestate=ONE_BOARD_ONE_PLAYER;
							if(num_board==2 && recording==0) game.gamestate=HANDSHAKE;
							else if(num_board==2){
							if(num_board==2 && recording==0xFF) TextResponse();
							if(num_board==2 && num_player==1)game.gamestate=TWO_BOARD_NPC;
							if(num_board==2 && num_player==2)game.gamestate=TWO_BOARD_TWO_PLAYER;
								disable_RIT();
								change_mode();
								disable_timer(0);
								break;
							}
							change_mode();
							break;
						case ONE_BOARD_TWO_PLAYERS:
							joy_select();
							break;
						
						case ONE_BOARD_ONE_PLAYER:
							joy_select();
						break;
						
						case TWO_BOARD_TWO_PLAYER:
							joy_select();
							break;
						default:
							break;
					}
				
				break;

			default:
				break;
		}
	}
	else{
			joy=0;
	}
	
	/* button management */
	if(down1>=1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* Key1 pressed */
			switch(down1){				
				case 2:
					switch (game.gamestate){
						case BOARD_CHOOSE:
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							key1func();
							break;
							
							case ONE_BOARD_ONE_PLAYER:
								key1func();
								break;
							
							case TWO_BOARD_TWO_PLAYER:
								key1func();
							break;
							default:
								break;
					}
		
				default:
					break;
			}
			down1++;
		}
		
		else {	/* button released */
			down1=0;
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
			
		}
	}
	
	if(down0>=1){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* Key0 pressed */
			switch(down0){				
				case 2:	
					joystick_init();
					game.gamestate=BOARD_CHOOSE;
					change_mode();
					break;
				
				default:
					break;
			}
			down0++;
		}
		
		else {	/* button released */
			down0=0;
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
			
		}
	}
	
	if(down2>=1){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* Key2 pressed */
			switch(down2){				
				case 2:	
					switch (game.gamestate){
						case BOARD_CHOOSE:
							break;
						case PLAYERS_CHOOSE:
							break;
						case ONE_BOARD_TWO_PLAYERS:
							key2func();
							break;
					
					case ONE_BOARD_ONE_PLAYER:
						key2func();
						break;
					case TWO_BOARD_TWO_PLAYER:
						key2func();
							break;
					default:
						
						break;
					}
					
					break;
				
				default:
					break;
			}
			down2++;
		}
		
		else {	/* button released */
			down2=0;
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
			
		}
	}
	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
