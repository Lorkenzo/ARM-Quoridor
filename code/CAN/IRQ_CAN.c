/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC17xx with MCB1700
 * Note(s): see also http://www.port.de/engl/canprod/sv_req_form.html
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/
#include "stdio.h"
#include "lpc17xx.h"
#include "../GLCD/GLCD.h" 
#include "../button_EXINT/button.h"
#include "../TouchPanel/TouchPanel.h"
#include "../timer\timer.h"
#include "../joystick/joystick.h"
#include "../Wall_moves.h"
#include "../Moves.h"
#include "../Game_Mode.h"
#include "../RIT/RIT.h"
#include "CAN.h"
#define DIST_MOVE 34
extern uint8_t icr ; 										//icr and result must be global in order to work with both real and simulated landtiger.
extern uint32_t result;
extern CAN_msg       CAN_TxMsg;    /* CAN message for sending */
extern CAN_msg       CAN_RxMsg;    /* CAN message for receiving */   

extern uint32_t recording;

uint16_t val_RxCoordX = 0;            /* Locals used for display */
uint16_t val_RxCoordY = 0;

extern int player_index;
extern int wallflag;
extern int rotate;
extern struct playerpos player[2];
extern struct wall W_O[16];
extern struct wall W_V[16];
extern int W_ind_O;
extern int W_ind_V;
extern int wall1;
extern int wall2;
extern int start;
extern int change;
extern int count_timer;
extern char wall1s[5];
extern char wall2s[5];
extern int num_board;
extern int num_player;
extern struct Game_Mode game;
/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/ 
 
void CAN_IRQHandler (void)  {
	int xpos;
	int ypos;
	
  /* check CAN controller 1 */
	icr = 0;
  icr = (LPC_CAN1->ICR | icr) & 0xFF;               /* clear interrupts */
	//-------CAN1 CHE RICEVE IL MESSAGGIO-----------------
  if (icr & (1 << 0)) {                          		/* CAN Controller #1 meassage is received */
		CAN_rdMsg (1, &CAN_RxMsg);	                		/* Read the message */
    LPC_CAN1->CMR = (1 << 2);                    		/* Release receive buffer */
		
		recording = *(uint32_t*) CAN_RxMsg.data;
		//-------------HANDSHAKE---------------
		if(recording==0xFF && start==2){
			LCD_Clear(0x98F0); 
			DrawMenu();
			num_board=2;
			game.gamestate=PLAYERS_CHOOSE;
			change_mode();
		}
		else if(recording==0xFF && start==1){
			if(num_board==2 && num_player==1)game.gamestate=TWO_BOARD_NPC;
			if(num_board==2 && num_player==2)game.gamestate=TWO_BOARD_TWO_PLAYER;
			enable_RIT();
			change_mode();
		}
		//----CONVERSIONE MOSSA RICEVUTA--------
		else{
		player_index=(recording>>24) & 0xFF;
		wallflag= (recording>>20) & 0xF;
		rotate = (recording>>16) & 0xF;
		
		//in caso un dispositivo voglia giocare con noi avendo indici dei giocatori invertiti
		//if(player_index) player_index=0; else player_index=1;  
		//-------------------------------------------------------------------------------
		
		if(wallflag==0 && rotate!=1){

			
			xpos = (recording>>8) & 0xFF;
			ypos = recording & 0xFF;
			xpos=18 + xpos *34;
			ypos=18 + ypos *34;	
			
			if((player[player_index].x+DIST_MOVE==xpos && player[player_index].y==ypos) || (player[player_index].x+2*DIST_MOVE==xpos && player[player_index].y==ypos)) move_right();
			if((player[player_index].x-DIST_MOVE==xpos && player[player_index].y==ypos) || (player[player_index].x-2*DIST_MOVE==xpos && player[player_index].y==ypos)) move_left();
			if((player[player_index].x==xpos && player[player_index].y+DIST_MOVE==ypos) || (player[player_index].x==xpos && player[player_index].y+2*DIST_MOVE==ypos)) move_down();
			if((player[player_index].x==xpos && player[player_index].y-DIST_MOVE==ypos) || (player[player_index].x==xpos && player[player_index].y-2*DIST_MOVE==ypos)) move_up();
			if(player[player_index].x+DIST_MOVE==xpos && player[player_index].y+DIST_MOVE==ypos) move_down_right();
			if(player[player_index].x-DIST_MOVE==xpos && player[player_index].y+DIST_MOVE==ypos) move_down_left();
			if(player[player_index].x-DIST_MOVE==xpos && player[player_index].y-DIST_MOVE==ypos) move_up_left();
			if(player[player_index].x+DIST_MOVE==xpos && player[player_index].y-DIST_MOVE==ypos) move_up_right();
		}
		else if(wallflag==1){
			if(rotate){
					W_V[W_ind_V].x = (recording>>8) & 0xFF;
					W_V[W_ind_V].y = recording & 0xFF;
					W_V[W_ind_V].x=35 + W_V[W_ind_V].x *34;
					W_V[W_ind_V].y=35 + W_V[W_ind_V].y *34;	
					DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
					W_ind_V++;
					player_index? wall2--:wall1--;
			}
			else{
					W_O[W_ind_O].x = (recording>>8) & 0xFF;
					W_O[W_ind_O].y = recording & 0xFF;
					W_O[W_ind_O].x=35 + W_O[W_ind_O].x *34;
					W_O[W_ind_O].y=35 + W_O[W_ind_O].y *34;	
					DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
					W_ind_O++;
					player_index? wall2--:wall1--;
			}
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
		}
		
		//cambio turno
		wallflag=0;
		rotate=0;
		change++;
		player_index=change%2;
		
		//se è in modalità npc muove l'npc una volta ricevuta la mossa
		if(game.gamestate==TWO_BOARD_NPC){
			enable_timer(3);
		}
		//se è in modalità giocatore cambia turno e attiva i tasti
		else {
			if(( player[0].y!=222) && ( player[1].y!=18)){
			enlight_direction();
			enable_RIT();
			count_timer=20;
			enable_timer(0);
			}
			else disable_timer(0);
		}
		
  }
}
	//
	
}
