#include "lpc17xx.h"
#include "RIT/RIT.h"
#include "GLCD/GLCD.h" 
#include "button_EXINT/button.h"
#include "TouchPanel/TouchPanel.h"
#include "timer\timer.h"
#include "joystick/joystick.h"
#include "Wall_moves.h"
#include "Moves.h"
#include "Game_Mode.h"
#include "CAN/CAN.h"

#define DIST_MOVE 34
//---------VARIABILI----------------
extern int player_index;
extern int change;
struct playerpos player[2];
int black1;
int black2;
int jumpflag;
extern int oblique;
extern int oblique1;
extern int wallflag;
extern int move;
extern int start;
extern struct Game_Mode game;
//--------------Win banner-------------------------
void player1win(){
				moveRecord(player_index,0,0,player[player_index].x,player[player_index].y);
				Textmessage();
				LCD_DrawLine(3,3,237,3,White);				
				LCD_DrawLine(237,3,237,237,White);				
				LCD_DrawLine(237,237,3,237,White);
				LCD_DrawLine(3,237,3,3,White);
	GUI_Text(90,115,(uint8_t *)"White Win",White,Black);
	//GUI_Text(5,160,(uint8_t *)"Click INT0 to restart",Blue,White);
	disable_timer(0);
	enable_RIT();
	game.gamestate=WAIT;
}

void player2win(){
				moveRecord(player_index,0,0,player[player_index].x,player[player_index].y);
				Textmessage();
				LCD_DrawLine(3,3,237,3,Red);				
				LCD_DrawLine(237,3,237,237,Red);				
				LCD_DrawLine(237,237,3,237,Red);
				LCD_DrawLine(3,237,3,3,Red);
	GUI_Text(90,115,(uint8_t *)"Red Win",Red,Black);
	//GUI_Text(5,160,(uint8_t *)"Click INT0 to restart",Red,White);
	disable_timer(0);
	enable_RIT();
	game.gamestate=WAIT;
}

//------------Control flags square black or green-----------
void blackorwhite(){
	if(player_index==0){
		black1=black1?0:1;
		}
	else{
		black2=black2?0:1;
	}
}

//------------------MOVE UP-------------------------

void move_up(){
	delete_direction();
	
		
			if(player[player_index].y-DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x){
			
				jumpflag=1;
				if(player[player_index].y-2*DIST_MOVE<0){
					jumpflag=0;
					return;
				}
			} else jumpflag=0;
			
			blackorwhite();
			
			DeletePlayer(player[player_index].x,player[player_index].y);
			player[player_index].y-=DIST_MOVE;
			if(jumpflag==1) {
				blackorwhite();
				player[player_index].y-=DIST_MOVE;
			}
			DrawPlayer(player[player_index].x,player[player_index].y);
			
			if(player[player_index].y==18 && player_index==1) player2win();
		
}
//---------------------MOVE RIGHT--------------------------
void move_right(){
	delete_direction();

		
			if(player[player_index].x+DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
				
				jumpflag=1;
				if(player[player_index].x+2*DIST_MOVE>240){
					jumpflag=0;
					return;
				}
			} else jumpflag=0;
			
			
			blackorwhite();
			
			DeletePlayer(player[player_index].x,player[player_index].y);
			player[player_index].x+=DIST_MOVE;
			if(jumpflag) {
				blackorwhite();
				player[player_index].x+=DIST_MOVE;}
			DrawPlayer(player[player_index].x,player[player_index].y);
		
				
}
//--------------------MOVE LEFT----------------------------
void move_left(){
	delete_direction();
	
			if(player[player_index].x-DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
				
				jumpflag=1;
				if(player[player_index].x-2*DIST_MOVE<0){
					jumpflag=0;
					return;
				}
			} else jumpflag=0;
			
			
			blackorwhite();
			
			DeletePlayer(player[player_index].x,player[player_index].y);
			if(jumpflag==1) {
				blackorwhite();
				player[player_index].x-=DIST_MOVE;}
			player[player_index].x-=DIST_MOVE;
			DrawPlayer(player[player_index].x,player[player_index].y);
				
}
//-------------------------MOVE DOWN------------------------
void move_down(){
	delete_direction();
	
					if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x){
					
						jumpflag=1;
						if(player[player_index].y+2*DIST_MOVE>240){
							jumpflag=0;
							return;
						}
					} else jumpflag=0;
					
					
					blackorwhite();
					
					DeletePlayer(player[player_index].x,player[player_index].y);
					player[player_index].y+=DIST_MOVE;
					if(jumpflag==1){
						blackorwhite();
						player[player_index].y+=DIST_MOVE;}
					DrawPlayer(player[player_index].x,player[player_index].y);
						
					if(player[player_index].y==222 && player_index==0) player1win();
				
}

//----------OBLIQUO-----------------

void move_up_right(){
	delete_direction();
	blackorwhite();
	DeletePlayer(player[player_index].x,player[player_index].y);
	player[player_index].x+=DIST_MOVE;
	player[player_index].y-=DIST_MOVE;
	blackorwhite();
	DrawPlayer(player[player_index].x,player[player_index].y);
	
};
	
void move_up_left(){
	delete_direction();
	blackorwhite();
	DeletePlayer(player[player_index].x,player[player_index].y);
	player[player_index].x-=DIST_MOVE;
	player[player_index].y-=DIST_MOVE;
	blackorwhite();
	DrawPlayer(player[player_index].x,player[player_index].y);
};

void move_down_right(){
	delete_direction();
	blackorwhite();
	DeletePlayer(player[player_index].x,player[player_index].y);
	player[player_index].x+=DIST_MOVE;
	player[player_index].y+=DIST_MOVE;
	blackorwhite();
	DrawPlayer(player[player_index].x,player[player_index].y);
};

void move_down_left(){
	delete_direction();
	blackorwhite();
	DeletePlayer(player[player_index].x,player[player_index].y);
	player[player_index].x-=DIST_MOVE;
	player[player_index].y+=DIST_MOVE;
	blackorwhite();
	DrawPlayer(player[player_index].x,player[player_index].y);
};	

//------------------Show direction move----------------
int deldir;

void up_direction(){
		if(check_wall_up(player[player_index].x,player[player_index].y)==1) return; 
		//caso in cui l'avversario è sopra
		if(player[player_index].y-DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x){
						//caso in cui dietro l'avversario c'è un muro
						if(check_wall_up(player[player_index].x,player[player_index].y-DIST_MOVE)==1) {
								if(check_wall_left(player[player_index].x,player[player_index].y-DIST_MOVE)==0){ 
									if(deldir==0) DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,Yellow);
										else {
											blackorwhite();
											DeletePlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE);
											blackorwhite();
									}
								}
								if(check_wall_right(player[player_index].x,player[player_index].y-DIST_MOVE)==0) {
									if(deldir==0) DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,Yellow);
										else {
											blackorwhite();
											DeletePlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE);
											blackorwhite();
								}}
								
								return;
						}
			
						jumpflag=1;
						if(player[player_index].y-2*DIST_MOVE<0){
							jumpflag=0;
							return;
						}
					} else jumpflag=0;
					if(player[player_index].y-DIST_MOVE<0) return;
					
					if(deldir==0){
						if (jumpflag==1) {
							DrawPlayerDir(player[player_index].x,player[player_index].y-2*DIST_MOVE,Yellow);
						}
						else{
							DrawPlayerDir(player[player_index].x,player[player_index].y-DIST_MOVE,Yellow);
						}
				}
					else{
							if (jumpflag==1) {
							blackorwhite();
							DeletePlayerDir(player[player_index].x,player[player_index].y-2*DIST_MOVE);
							blackorwhite();
						}
						else{
							DeletePlayerDir(player[player_index].x,player[player_index].y-DIST_MOVE);
						}
					}
}

void right_direction(){
	
				if(check_wall_right(player[player_index].x,player[player_index].y)==1) return; 
	
					if(player[player_index].x+DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
						if(check_wall_right(player[player_index].x+DIST_MOVE,player[player_index].y)==1) {
							if(check_wall_up(player[player_index].x+DIST_MOVE,player[player_index].y)==0){
									if(deldir==0) DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE,Yellow);
										else {
											blackorwhite();
											DeletePlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y-DIST_MOVE);
											blackorwhite();
							}}
											
							if(check_wall_down(player[player_index].x+DIST_MOVE,player[player_index].y)==0) {
								if(deldir==0) DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,Yellow);
									else {
										blackorwhite();
										DeletePlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE);
										blackorwhite();}}
							return;
						}
						jumpflag=1;
						if(player[player_index].x+2*DIST_MOVE>240){
							jumpflag=0;
							return;
						}
					} else jumpflag=0;
					
					
					
					if(player[player_index].x+DIST_MOVE>240) return;
					
					if(deldir==0){
						if(jumpflag==1) {
								DrawPlayerDir(player[player_index].x+2*DIST_MOVE,player[player_index].y,Yellow);
							}else{
								DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y,Yellow);
							}}
					else{
						if(jumpflag==1) {
								blackorwhite();
								DeletePlayerDir(player[player_index].x+2*DIST_MOVE,player[player_index].y);
								blackorwhite();
							}else{
								DeletePlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y);
							}
					}				
				
}

void left_direction(){
	
		if(check_wall_left(player[player_index].x,player[player_index].y)==1) return;
		
		if(player[player_index].x-DIST_MOVE==player[player_index?0:1].x && player[player_index].y==player[player_index?0:1].y){
						if(check_wall_left(player[player_index].x-DIST_MOVE,player[player_index].y)==1) {
							
							if(check_wall_up(player[player_index].x-DIST_MOVE,player[player_index].y)==0) {
									if(deldir==0)DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE,Yellow);
										else {
											blackorwhite();
											DeletePlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y-DIST_MOVE);
											blackorwhite();
							}}
							if(check_wall_down(player[player_index].x-DIST_MOVE,player[player_index].y)==0) {
								if(deldir==0)DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,Yellow);
									else {
										blackorwhite();
										DeletePlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE);
										blackorwhite();
									}
							}
							return;
						}
						jumpflag=1;
						if(player[player_index].x-2*DIST_MOVE<0){
							jumpflag=0;
							return;
						}
					} else jumpflag=0;
					
					if(player[player_index].x-DIST_MOVE<0) return;
					if(deldir==0){
						if(jumpflag==1)	{
							DrawPlayerDir(player[player_index].x-2*DIST_MOVE,player[player_index].y,Yellow);
							}
						else{
							DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y,Yellow);
						}
					}
					else{
						if(jumpflag==1)	{
								blackorwhite();
								DeletePlayerDir(player[player_index].x-2*DIST_MOVE,player[player_index].y);
								blackorwhite();
								}
							else{
								DeletePlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y);
							}
					}	
}

void down_direction(){

		if(check_wall_down(player[player_index].x,player[player_index].y)==1) return; 
	
					if(player[player_index].y+DIST_MOVE==player[player_index?0:1].y && player[player_index].x==player[player_index?0:1].x){
						if(check_wall_down(player[player_index].x,player[player_index].y+DIST_MOVE)==1) {
							
							if(check_wall_left(player[player_index].x,player[player_index].y+DIST_MOVE)==0) {
								if(deldir==0)DrawPlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE,Yellow);
									else {
										blackorwhite();
										DeletePlayerDir(player[player_index].x-DIST_MOVE,player[player_index].y+DIST_MOVE);
									blackorwhite();}
							}
							if(check_wall_right(player[player_index].x,player[player_index].y+DIST_MOVE)==0) {
								if(deldir==0) DrawPlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE,Yellow);	
									else {
										blackorwhite();
										DeletePlayerDir(player[player_index].x+DIST_MOVE,player[player_index].y+DIST_MOVE);
										blackorwhite();}
							}
							return;
						}
						jumpflag=1;
						if(player[player_index].y+2*DIST_MOVE>240){
							jumpflag=0;
							return;
						}
					} else jumpflag=0;
					
					if(player[player_index].y+DIST_MOVE>240) return;
					
					if(deldir==0){
						if(jumpflag==1) {
								DrawPlayerDir(player[player_index].x,player[player_index].y+2*DIST_MOVE,Yellow);
							}else{
								DrawPlayerDir(player[player_index].x,player[player_index].y+DIST_MOVE,Yellow);
							}
					}else{
						if(jumpflag==1) {
								blackorwhite();
								DeletePlayerDir(player[player_index].x,player[player_index].y+2*DIST_MOVE);
								blackorwhite();
							}else{
								DeletePlayerDir(player[player_index].x,player[player_index].y+DIST_MOVE);
							}
					}
}

void enlight_direction(){
	deldir=0;
	left_direction();
	right_direction();
	up_direction();
	down_direction();
}

void delete_direction(){
	deldir=1;
	left_direction();
	right_direction();
	up_direction();
	down_direction();
}

//-------------------------Controllo trappola----------------------------------------

struct playerpos trackplayer[49];
int fronte=0;						//tiene numero degli elementi esaminati
int coda=0;             //tiene numero degli elementi nell'array

int trackmove(uint16_t Xpos,uint16_t Ypos){           //verifica se la posizione è gia stata esaminata
	int i;
	for(i=0;i<coda;i++){
		if(trackplayer[i].x==Xpos && trackplayer[i].y==Ypos) return 1;
	}
	return 0;
	
}	

int check_trap_player(uint16_t Xpos,uint16_t Ypos,int player){
	int tempx;
	int tempy;
	
	trackplayer[coda].x=Xpos;   //coordinate di partenza
	trackplayer[coda].y=Ypos;
	coda++;
	
	while(fronte<coda){
		if(trackplayer[fronte].y==222 && player==1) {
			fronte=0;
			coda=0;
			return 1;
		}
		if(trackplayer[fronte].y==18 && player==2) {
			fronte=0;
			coda=0;
			return 1;
		}
		 
			tempx=trackplayer[fronte].x;              //prende elemento corrente
			tempy=trackplayer[fronte].y;
			 
			if(check_wall_up(tempx,tempy)==0 && tempy-DIST_MOVE>0){  //controlla se non ha muri sopra e se la posizione sopra non è stata esaminata
				if(trackmove(tempx,tempy-DIST_MOVE)==0){
					trackplayer[coda].x=tempx;																											//aggiunge posizione in coda
					trackplayer[coda].y=tempy-DIST_MOVE;
					coda++;
				}
			}
			if(check_wall_down(tempx,tempy)==0 && tempy+DIST_MOVE<240){ //controlla se non ha muri sotto e se la posizione sotto non è stata esaminata
				if(trackmove(tempx,tempy+DIST_MOVE)==0){
					trackplayer[coda].x=tempx;																													//aggiunge posizione in coda
					trackplayer[coda].y=tempy+DIST_MOVE;
					coda++;
				}	
			}
			if(check_wall_right(tempx,tempy)==0 && tempx+DIST_MOVE<240){ //controlla se non ha muri a destra e se la posizione a destra non è stata esaminata
				if(trackmove(tempx+DIST_MOVE,tempy)==0){
					trackplayer[coda].x=tempx+DIST_MOVE;																												//aggiunge posizione in coda
					trackplayer[coda].y=tempy;
					coda++;
				}
			}
			if(check_wall_left(tempx,tempy)==0 && tempx-DIST_MOVE>0){   //controlla se non ha muri a sinistra e se la posizione a sinistra non è stata esaminata
				if(trackmove(tempx-DIST_MOVE,tempy)==0){
					trackplayer[coda].x=tempx-DIST_MOVE;																												//aggiunge posizione in coda
					trackplayer[coda].y=tempy;
					coda++;
				}
			}
			fronte++;																																						//passa a elemento successivo
	
	}
	fronte=0;        //reset indici 
	coda=0;
	return 0;
	}
//save current moveplayer or movewall
	
uint32_t recording=0;	
void moveRecord(int player_index,int wallflag,int rotate,int xpos,int ypos){
	//conversione da coordinate pixel a coordinate indici
	if(wallflag==0){
		xpos=(xpos-18)/34;
		ypos=(ypos-18)/34;
	}
	else{
		xpos=(xpos-35)/34;
		ypos=(ypos-35)/34;
	}
	//in caso un dispositivo voglia giocare con noi avendo indici dei giocatori invertiti
	//if(player_index) player_index=0; else player_index=1;  
	//-------------------------------------------------------------------------------
	recording=(player_index<<24)+(wallflag<<20)+(rotate<<16)+(xpos<<8)+ypos;
}
//-----invio mossa-----------
void Textmessage(){
	
	*(uint32_t*) CAN_TxMsg.data=recording;
	CAN_TxMsg.len = 4;
	CAN_TxMsg.id = 1;
	CAN_TxMsg.format = STANDARD_FORMAT;
	CAN_TxMsg.type = DATA_FRAME;
	CAN_wrMsg (1, &CAN_TxMsg);     
	
}

//-----------GESTIONE SPOSTAMENTO NPC-------------
int current_bot=0;
int tot_bot=0;
struct playerpos trackbot[49];
int movebot[49];
int passi=0;
//---FUNZIONE PER VERIFICARE SE LA POSIZIONE ATTUALE è GIA STATA ESAMINATA
int visited(uint16_t Xpos,uint16_t Ypos){           //verifica se la posizione è gia stata esaminata
	int i;
	for(i=0;i<tot_bot+1;i++){
		
		if(trackbot[i].x==Xpos && trackbot[i].y==Ypos) return 1;
	}
	return 0;
	
}	
//----FUNZIONE DFS PER LA RICERCA DELLA STRADA PER LA VITTORIA DEL BOT-----
void move_bot(uint16_t Xpos,uint16_t Ypos){
	int tempx;
	int tempy;
	int j;
		trackbot[current_bot].x=Xpos;   //coordinate di partenza
		trackbot[current_bot].y=Ypos;
		
	//finche non eaggiunge la vittoria
			while(trackbot[current_bot].y!=222){
				
				tempx=trackbot[current_bot].x;              //prende posizione corrente
				tempy=trackbot[current_bot].y;
			
				//se puo andare giu ricerca giu
			if(check_wall_down(tempx,tempy)==0 && tempy+DIST_MOVE<240){ //controlla se non ha muri sotto e se la posizione sotto non è stata esaminata
				if(visited(tempx,tempy+DIST_MOVE)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx;																													//aggiunge posizione in coda
					trackbot[current_bot].y=tempy+DIST_MOVE;
					movebot[current_bot]=4;
					
					continue;
				}	
			}
			//se no se non ci sono muri sotto ricerca a destra
			if(check_wall_right(tempx,tempy)==0 && tempx+DIST_MOVE<240 && check_wall_down(tempx+DIST_MOVE,tempy)==0){				//controlla se non ha muri a destra e se la posizione a destra non è stata esaminata
				if(visited(tempx+DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx+DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=2;
									
					continue;
				}
			}
			//se no se non ci sono muri sotto ricerca a sinista
			if(check_wall_left(tempx,tempy)==0 && tempx-DIST_MOVE>0 && check_wall_down(tempx-DIST_MOVE,tempy)==0){   //controlla se non ha muri a sinistra e se la posizione a sinistra non è stata esaminata
				if(visited(tempx-DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx-DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=3;
									
					continue;
				}
			} 
			//se no ricerca a destra
			if(check_wall_right(tempx,tempy)==0 && tempx+DIST_MOVE<240){				//controlla se non ha muri a destra e se la posizione a destra non è stata esaminata
				if(visited(tempx+DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx+DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=2;
									
					continue;
				}
			}
			//se no ricerca a sinistra
			if(check_wall_left(tempx,tempy)==0 && tempx-DIST_MOVE>0){   //controlla se non ha muri a sinistra e se la posizione a sinistra non è stata esaminata
				if(visited(tempx-DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx-DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=3;
									
					continue;
				}
			} 
			//se no ricerca in alto
			if(check_wall_up(tempx,tempy)==0 && tempy-DIST_MOVE>0){  //controlla se non ha muri sopra e se la posizione sopra non è stata esaminata
				if(visited(tempx,tempy-DIST_MOVE)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx;																											//aggiunge posizione in coda
					trackbot[current_bot].y=tempy-DIST_MOVE;
					movebot[current_bot]=1;
						
					continue;
				}
			}
			
			//se non ci sono più strade disponibili torna indietro nella strada
			current_bot--;
			//se torna al punto di partenza dimentica la strada iniziale che aveva fatto effettivamente l'NPC
			//azzera i passi fatti per continuare a cercare da dove è arrivato
			if(current_bot<passi) {
				for(j=current_bot;j>=0;j--) {
					trackbot[j].x=0;
					trackbot[j].y=0;
				}
				trackbot[0].x=trackbot[current_bot+1].x;
				trackbot[0].y=trackbot[current_bot+1].y;;
				passi=0;
				current_bot=passi;
			}
		}
		//l'algoritmo ha trovato la strada
		//incrementiamo la variabile che tiene il conto dei passi effettuati dall'NPC, in modo da ricordarle alla prossima ricerca
		passi++;	
		current_bot=passi;
		tot_bot=passi;
		return;
}
//ripetizione dell'algoritmo di ricerca con spostamenti inversi per l'npc che parte dal basso
void move_bot0(uint16_t Xpos,uint16_t Ypos){
	int tempx;
	int tempy;
	int j;
	
		trackbot[current_bot].x=Xpos;   //coordinate di partenza
		trackbot[current_bot].y=Ypos;
		
	
			while(trackbot[current_bot].y!=18){
				
				tempx=trackbot[current_bot].x;              //prende posizione corrente
				tempy=trackbot[current_bot].y;
			
				
	
			
			if(check_wall_up(tempx,tempy)==0 && tempy-DIST_MOVE>0){  //controlla se non ha muri sopra e se la posizione sopra non è stata esaminata
				if(visited(tempx,tempy-DIST_MOVE)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx;																											//aggiunge posizione in coda
					trackbot[current_bot].y=tempy-DIST_MOVE;
					movebot[current_bot]=1;
						
					continue;
				}
			}
			if(check_wall_right(tempx,tempy)==0 && tempx+DIST_MOVE<240 && check_wall_up(tempx+DIST_MOVE,tempy)==0){				//controlla se non ha muri a destra e se la posizione a destra non è stata esaminata
				if(visited(tempx+DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx+DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=2;
									
					continue;
				}
			}
			if(check_wall_left(tempx,tempy)==0 && tempx-DIST_MOVE>0 && check_wall_up(tempx-DIST_MOVE,tempy)==0){   //controlla se non ha muri a sinistra e se la posizione a sinistra non è stata esaminata
				if(visited(tempx-DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx-DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=3;
									
					continue;
				}
			} 
			if(check_wall_right(tempx,tempy)==0 && tempx+DIST_MOVE<240){				//controlla se non ha muri a destra e se la posizione a destra non è stata esaminata
				if(visited(tempx+DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx+DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=2;
									
					continue;
				}
			}
			if(check_wall_left(tempx,tempy)==0 && tempx-DIST_MOVE>0){   //controlla se non ha muri a sinistra e se la posizione a sinistra non è stata esaminata
				if(visited(tempx-DIST_MOVE,tempy)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx-DIST_MOVE;																												//aggiunge posizione in coda
					trackbot[current_bot].y=tempy;
					movebot[current_bot]=3;
									
					continue;
				}
			} 
			if(check_wall_down(tempx,tempy)==0 && tempy+DIST_MOVE<240){ //controlla se non ha muri sotto e se la posizione sotto non è stata esaminata
				if(visited(tempx,tempy+DIST_MOVE)==0){
					current_bot++;
					tot_bot++;
					trackbot[current_bot].x=tempx;																													//aggiunge posizione in coda
					trackbot[current_bot].y=tempy+DIST_MOVE;
					movebot[current_bot]=4;
					
					continue;
				}	
			}
			
			//nessuna strada, torna indietro
			current_bot--;
			if(current_bot<passi) {
				for(j=current_bot;j>=0;j--) {
					trackbot[j].x=0;
					trackbot[j].y=0;
				}
				trackbot[0].x=trackbot[current_bot+1].x;
				trackbot[0].y=trackbot[current_bot+1].y;;
				passi=0;
				current_bot=passi;
			}
		}
			
		passi++;	
		current_bot=passi;
		tot_bot=passi;
		return;
}

