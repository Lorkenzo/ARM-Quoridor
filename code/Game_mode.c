#include "stdio.h"
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "button_EXINT/button.h"
#include "joystick\joystick.h"
#include "RIT/RIT.h"
#include "Moves.h"
#include "Wall_moves.h"
#include "Game_mode.h"
#include "CAN/CAN.h"
//---------VARIABILI-------------

extern int player_index;
extern struct playerpos player[2];
extern int black1;
extern int black2;
extern int change;
extern int move;
extern int wallflag;
extern int wall1;
extern int wall2;
extern int W_ind_O;
extern int W_ind_V;
extern int rotate;
extern int count_timer;
extern char wall1s[5];
extern char wall2s[5];
int bot;
extern int movebot[49];
extern int current_bot;
extern int tot_bot;
extern int passi;
int num_board;
int num_player;
int rand_num;
extern int recording;
extern struct Game_Mode game;
extern int start;
//------CAMBIO MODALITA DI GIOCO-----------
void change_mode(){
	int i,j;
	switch (game.gamestate) {
        case BOARD_CHOOSE:
            LCD_Clear(0x98F0); 
						DrawMenu();
				for(i=60,j=20;i>54;i--,j--){
						LCD_DrawLine(120-i,190+j,120-i,190-j,Yellow);				
						LCD_DrawLine(120-i,190-j,120+i,190-j,Yellow);				
						LCD_DrawLine(120+i,190-j,120+i,190+j,Yellow);
						LCD_DrawLine(120+i,190+j,120-i,190+j,Yellow);
				}
				num_board=1;
            break;
				
        case PLAYERS_CHOOSE:
					if(num_board==2) change_option();
				
					if(num_board==1){
            GUI_Text(70,65,(uint8_t *) "OPPONENT MODE",Black,0x1CC6);
						GUI_Text(70,185,(uint8_t *)"     NPC     ",Black,0x1CC6);
						GUI_Text(70,235,(uint8_t *)"    HUMAN    ",Black,0x1CC6);
					}
					else{
						GUI_Text(70,65,(uint8_t *) "CHOOSE PLAYER",Black,0x1CC6);
						GUI_Text(70,185,(uint8_t *)"     NPC     ",Black,0x1CC6);
						GUI_Text(70,235,(uint8_t *)"    HUMAN    ",Black,0x1CC6);
					}
            break;
				
        case ONE_BOARD_TWO_PLAYERS:
						start=1;
            initialize_game();
            break;
				case HANDSHAKE:
							disable_RIT();
							TextHandshake();
							break;
				case ONE_BOARD_ONE_PLAYER:
						start=1;
						initialize_game();
						break;
				case TWO_BOARD_TWO_PLAYER:
						initialize_game();
					break;
				case TWO_BOARD_NPC:
						initialize_game();
						GUI_Text(110, 270, (uint8_t *) "--" , Black, White);
					if(recording==0xFF && start==1){
						enable_RIT();
						bot_function();
						disable_RIT();
						change++;
						player_index=change%2;
						Textmessage();
					}
					break;
				
        default:
            break;
    }

}
// funzione per cambiare opzione nel menù
void change_option(){
	if(game.gamestate==BOARD_CHOOSE){
		if(num_board==1){
								int i;
								int j;
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,190+j,120-i,190-j,Black);				
										LCD_DrawLine(120-i,190-j,120+i,190-j,Black);				
										LCD_DrawLine(120+i,190-j,120+i,190+j,Black);
										LCD_DrawLine(120+i,190+j,120-i,190+j,Black);
								}	
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,240+j,120-i,240-j,Yellow);				
										LCD_DrawLine(120-i,240-j,120+i,240-j,Yellow);				
										LCD_DrawLine(120+i,240-j,120+i,240+j,Yellow);
										LCD_DrawLine(120+i,240+j,120-i,240+j,Yellow);
								}	
								 num_board=2;
							}
							else {
								int i;
								int j;
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,240+j,120-i,240-j,Black);				
										LCD_DrawLine(120-i,240-j,120+i,240-j,Black);				
										LCD_DrawLine(120+i,240-j,120+i,240+j,Black);
										LCD_DrawLine(120+i,240+j,120-i,240+j,Black);
								}	
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,190+j,120-i,190-j,Yellow);				
										LCD_DrawLine(120-i,190-j,120+i,190-j,Yellow);				
										LCD_DrawLine(120+i,190-j,120+i,190+j,Yellow);
										LCD_DrawLine(120+i,190+j,120-i,190+j,Yellow);
								}	
								 num_board=1;
							
							}
						}
	if(game.gamestate==PLAYERS_CHOOSE){
			if(num_player==1){
								int i;
								int j;
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,190+j,120-i,190-j,Black);				
										LCD_DrawLine(120-i,190-j,120+i,190-j,Black);				
										LCD_DrawLine(120+i,190-j,120+i,190+j,Black);
										LCD_DrawLine(120+i,190+j,120-i,190+j,Black);
								}	
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,240+j,120-i,240-j,Yellow);				
										LCD_DrawLine(120-i,240-j,120+i,240-j,Yellow);				
										LCD_DrawLine(120+i,240-j,120+i,240+j,Yellow);
										LCD_DrawLine(120+i,240+j,120-i,240+j,Yellow);
								}	
								 num_player=2;
							}
							else {
								int i;
								int j;
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,240+j,120-i,240-j,Black);				
										LCD_DrawLine(120-i,240-j,120+i,240-j,Black);				
										LCD_DrawLine(120+i,240-j,120+i,240+j,Black);
										LCD_DrawLine(120+i,240+j,120-i,240+j,Black);
								}	
								for(i=60,j=20;i>54;i--,j--){
										LCD_DrawLine(120-i,190+j,120-i,190-j,Yellow);				
										LCD_DrawLine(120-i,190-j,120+i,190-j,Yellow);				
										LCD_DrawLine(120+i,190-j,120+i,190+j,Yellow);
										LCD_DrawLine(120+i,190+j,120-i,190+j,Yellow);
								}	
								 num_player=1;
							
							}
	}
}

// inizializzazione del gioco
void initialize_game(){
	//init variable
					count_timer=20;
					black1=1;
					black2=1;
					W_ind_O=0;
					W_ind_V=0;
					wall1=8;
					wall2=8;
					rotate=0;
					change=0;
					wallflag=0;
					current_bot=0;
					tot_bot=0;
					passi=0;
//------init pos--------------	
					player[0].x=120;
					player[0].y=18;
					
					player[1].x=120;
					player[1].y=222;
//--------------------	
					disable_timer(0);
					disable_timer(1);
					LCD_Clear(White);
				  GUI_Text(5,160,(uint8_t *)"Red Starts",Red,White);
					LCD_Clear(0x98F0);
					DrawSquare(18,18);
					DrawPlayer(player[0].x,player[0].y);
					DrawPlayer(player[1].x,player[1].y);
					//change++;                //test per invertire bot
					player_index=change%2;
					GUI_Text(4, 260, (uint8_t *) " Red", Red, Black);
				  GUI_Text(162, 260, (uint8_t *) " White", White, Black);
					sprintf(wall1s,"%d",wall1);
					sprintf(wall2s,"%d",wall2);
					GUI_Text(15, 280, (uint8_t *) wall2s, Red, Black);
					GUI_Text(173, 280, (uint8_t *) wall1s, White, Black); 						 
					init_timer(0, 0x17D7840 );	
					if(game.gamestate!=TWO_BOARD_NPC){
					enable_timer(0);
					if(start==1) enlight_direction();
					NVIC_EnableIRQ(EINT1_IRQn);
					NVIC_EnableIRQ(EINT2_IRQn);
					}
}
//-------funzione che gestisce le mosse dell'NPC
void bot_function(){
	//numero casuale prelevato dal rit
	rand_num=LPC_RIT->RICOUNTER%2;
		//50% spostamento giocatore, 50% piazzamento muro
		if(rand_num==0){
			if(player_index){
				move_bot0(player[player_index].x,player[player_index].y);
			}
			else move_bot(player[player_index].x,player[player_index].y);
			
			bot=0;
		}
		else {
			place_wall_bot();
		}
		if(bot==0){
		switch(movebot[current_bot]){
			case 1:
				joy_up();
				break;
			case 2:
				joy_right();
				break;
			case 3:
				joy_left();
				break;
			case 4: 
				joy_down();
				break;
			default:
				break;
		}
		joy_select();
		moveRecord(player_index,0,0,player[player_index].x,player[player_index].y);
	}

}
//-------funzione di handshake-----------
void TextHandshake(){
	LCD_Clear(0x98F0);
	GUI_Text(5,160,(uint8_t *)"Waiting for response...",White,0x98F0);
	init_timer(2,0x7735940);
	enable_timer(2);
	start=1;
	*(uint32_t*) CAN_TxMsg.data=0xFF;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);    


};
//--------risposta all'handshake---------------
void TextResponse(){
	*(uint32_t*) CAN_TxMsg.data=0xFF;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);    


};
