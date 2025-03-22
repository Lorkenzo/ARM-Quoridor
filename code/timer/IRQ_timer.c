/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "stdio.h"
#include "lpc17xx.h"
#include "timer.h"
#include "..\RIT\RIT.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../Moves.h"
#include "../Wall_moves.h"
#include "../Game_mode.h"
#include "../joystick/joystick.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
//------VARIABILI----------------
extern struct Game_Mode game;
extern struct playerpos player[2];
extern struct wall W_O[16];
extern struct wall W_V[16];
extern int W_ind_O;
extern int W_ind_V;
extern int wallflag;
extern int rotate;
extern int move;
volatile int count_timer;
char timer[5]="";
int change=0;
int player_index;
extern int recording;

//Gestisce il cambio di turno e il conteggio del timer del turno
void TIMER0_IRQHandler (void)
{
	
	switch(game.gamestate){
		case ONE_BOARD_ONE_PLAYER:
			
			sprintf(timer,"%02d",count_timer);
	GUI_Text(110, 270, (uint8_t *) timer , Black, White);
		if (count_timer==0){
			
			if(wallflag==1){
			if(rotate==1){
				DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			}
			else {
				DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			}
			wallflag=0;
			rotate=0;
		}
		//se era in modalità muro ed è scaduto il tempo o se la mossa non è stata finalizzata (move=-1) ed è scaduto il tempo registra mossa persa
		if(wallflag==1 || move!=-1){
			
			moveRecord(player_index,0,1,player[player_index].x,player[player_index].y);
					
		}
		//se era in modalità muro cancella il muro e resetta i parametri
		
		move=0;
		delete_direction();
		change++;
		player_index=change%2;
		//------MOSSA NPC------------
		bot_function();
		//---------------------------
		if(player[player_index].y!=222){   //test
		change++;
		player_index=change%2;
		enlight_direction();
		count_timer=20;
		}
		
		}
		else count_timer--;

			break;
		
		case ONE_BOARD_TWO_PLAYERS:
			
			sprintf(timer,"%02d",count_timer);
			GUI_Text(110, 270, (uint8_t *) timer , Black, White);
		if (count_timer==0){
			
			if(wallflag==1){
			if(rotate==1){
				DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			}
			else {
				DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			}
			wallflag=0;
			rotate=0;
		}
		//se era in modalità muro ed è scaduto il tempo o se la mossa non è stata finalizzata (move=-1) ed è scaduto il tempo registra mossa persa
		if(wallflag==1 || move!=-1){
			
			moveRecord(player_index,0,1,player[player_index].x,player[player_index].y);
					
		}
		//se era in modalità muro cancella il muro e resetta i parametri
		//----------CAMBIO TURNO--------------
		move=0;
		delete_direction();
		change++;
		player_index=change%2;
		enlight_direction();
		count_timer=20;}
		count_timer--;
			break;
		
		case TWO_BOARD_TWO_PLAYER:
			
			sprintf(timer,"%02d",count_timer);
			GUI_Text(110, 270, (uint8_t *) timer , Black, White);
		if (count_timer==0){
			
			if(wallflag==1){
			if(rotate==1){
				DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			}
			else {
				DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			}
			wallflag=0;
			rotate=0;
		}
		//se era in modalità muro ed è scaduto il tempo o se la mossa non è stata finalizzata (move=-1) ed è scaduto il tempo registra mossa persa
		if(wallflag==1 || move!=-1){
			
			moveRecord(player_index,0,1,player[player_index].x,player[player_index].y);
					
		}
		//se era in modalità muro cancella il muro e resetta i parametri
		
		move=0;
		change++;
		player_index=change%2;
		delete_direction();
		disable_RIT();
		disable_timer(0);
		count_timer=20;
		//-----INVIO MESSAGGIO DELLA PROPRIA MOSSA-------
		Textmessage();
		//----------------------------------------------
		}
		count_timer--;
			break;
		
		default:
			break;
	}
		
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
//disegna i muri alla frequenza di 1 Hz quando si entra in modalità muro
void TIMER1_IRQHandler (void)
{
	int i;
	
	for(i=0;i<W_ind_O;i++){
		DrawWallO(W_O[i].x,W_O[i].y);
	}
	for(i=0;i<W_ind_V;i++){
		DrawWallV(W_V[i].x,W_V[i].y);
	}
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
//aspetta 5 secondi per la schermata di attesa di connessione in modalità twoboard,
//oppure stampa messaggio di errore di connesione per 5 sec
int c=0;
void TIMER2_IRQHandler (void)
{

	if(recording==0 && c==0){
		GUI_Text(5,160,(uint8_t *)"No response received...",White,0x98F0);
		enable_timer(2);
		c=1;
	}
	else if (recording==0 && c==1){
		c=0;
	joystick_init();
	enable_RIT();
	game.gamestate=BOARD_CHOOSE;
	change_mode();
	}
	
	LPC_TIM2->IR = 1;
	return;
}

//aspetta 1 secondo per fare la mossa dell'npc
void TIMER3_IRQHandler (void)
{
	if(( player[0].y!=222) && ( player[1].y!=18)){
			enable_RIT();
			bot_function();
			disable_RIT();
			change++;
			player_index=change%2;
			Textmessage();
			}
	LPC_TIM3->IR = 1;
	return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
