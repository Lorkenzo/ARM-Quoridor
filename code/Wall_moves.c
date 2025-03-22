#include "lpc17xx.h"
#include "RIT/RIT.h"
#include "GLCD/GLCD.h" 
#include "button_EXINT/button.h"
#include "TouchPanel/TouchPanel.h"
#include "timer\timer.h"
#include "joystick/joystick.h"
#include "Wall_moves.h"
#include "Moves.h"
#include "stdio.h"

#define DIST_MOVE 34
#define WALL_LEN 32

struct wall W_O[16];
struct wall W_V[16];
extern int W_ind_O;
extern int W_ind_V;
extern int rotate;

//-------MURO SU----------
void wall_up(){
	if(rotate==0){
		if(W_O[W_ind_O].y-DIST_MOVE<18) return;
			DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			W_O[W_ind_O].y-=DIST_MOVE;
			DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
	}else{
		if(W_V[W_ind_V].y-DIST_MOVE<18) return;
		DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			W_V[W_ind_V].y-=DIST_MOVE;
			DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
	}

}
//-------MURO A DESTRA---------
void wall_right(){
	if(rotate==0){
		if(W_O[W_ind_O].x+DIST_MOVE>222) return;
			DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			W_O[W_ind_O].x+=DIST_MOVE;
			DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
	}else{
		if(W_V[W_ind_V].x+DIST_MOVE>222) return;
			DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			W_V[W_ind_V].x+=DIST_MOVE;
			DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
	}
}
//-------MURO A SINISTRA-------
void wall_left(){
	if(rotate==0){
		if(W_O[W_ind_O].x-DIST_MOVE<18) return;
			DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			W_O[W_ind_O].x-=DIST_MOVE;
			DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
	}else{
		if(W_V[W_ind_V].x-DIST_MOVE<18) return;
			DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			W_V[W_ind_V].x-=DIST_MOVE;
			DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
	}

}
//-----MURO IN BASSO---------
void wall_down(){
	if(rotate==0){
		if(W_O[W_ind_O].y+DIST_MOVE>222) return;
			DeleteWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
			W_O[W_ind_O].y+=DIST_MOVE;
			DrawWallO(W_O[W_ind_O].x,W_O[W_ind_O].y);
	}else{
		if(W_V[W_ind_V].y+DIST_MOVE>222) return;
			DeleteWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
			W_V[W_ind_V].y+=DIST_MOVE;
			DrawWallV(W_V[W_ind_V].x,W_V[W_ind_V].y);
	}

}
//-----VERIFICA DELLA PRESENZA DI UN MURO NELLE 4 DIREZIONI
int check_wall_up(uint16_t Xpos,uint16_t Ypos){
	int i;
		for(i=0;i<W_ind_O;i++){
			if(Xpos>W_O[i].x-WALL_LEN && Xpos<W_O[i].x+WALL_LEN && Ypos-DIST_MOVE<W_O[i].y && Ypos>W_O[i].y) return 1;
		}
		return 0;
}

int check_wall_down(uint16_t Xpos,uint16_t Ypos){
	int i;
		for(i=0;i<W_ind_O;i++){
			if(Xpos>W_O[i].x-WALL_LEN && Xpos<W_O[i].x+WALL_LEN && Ypos+DIST_MOVE>W_O[i].y && Ypos<W_O[i].y) return 1;
		}
		return 0;
}

int check_wall_right(uint16_t Xpos,uint16_t Ypos){
	int i;
		for(i=0;i<W_ind_V;i++){
			if(Ypos>W_V[i].y-WALL_LEN && Ypos<W_V[i].y+WALL_LEN && Xpos+DIST_MOVE>W_V[i].x && Xpos<W_V[i].x) return 1;
		}
		return 0;
}

int check_wall_left(uint16_t Xpos,uint16_t Ypos){
	int i;
		for(i=0;i<W_ind_V;i++){
			if(Ypos>W_V[i].y-WALL_LEN && Ypos<W_V[i].y+WALL_LEN && Xpos-DIST_MOVE<W_V[i].x && Xpos>W_V[i].x) return 1; 
		}
		return 0;    
}
//----VERIFICA DELLA PRESENZA DI UN MURO GIA ESISTENTE NELLA POSIZIONE SELEZIONATA----------
int check_existing_wall(uint16_t Xwall,uint16_t Ywall){
	int i;

	for(i=0;i<W_ind_O;i++){
		if(Xwall==W_O[i].x && Ywall==W_O[i].y) return 1;
		if(rotate==0) {
			if((Xwall==W_O[i].x+DIST_MOVE && Ywall==W_O[i].y) || (Xwall==W_O[i].x-DIST_MOVE && Ywall==W_O[i].y)) return 1;
		}
	}
	for(i=0;i<W_ind_V;i++){
		if(Xwall==W_V[i].x && Ywall==W_V[i].y) return 1;
		if(rotate==1) {
			if((Xwall==W_V[i].x && Ywall==W_V[i].y+DIST_MOVE) || (Xwall==W_V[i].x && Ywall==W_V[i].y-DIST_MOVE)) return 1;
		}
	}
	
	return 0;

}
//---------PIAZZAMENTO MURO DA PARTE DELL'NPC----------------
extern int player_index;
extern struct playerpos player[2];
extern int wall1;
extern int wall2;
extern int wallflag;
extern char wall1s[5];
extern char wall2s[5];
extern int bot;
//funzione per piazzare muro all'npc nei casi sia giocatore 0 o 1
void place_wall_bot(void){
	int xwall;
	int ywall;
	
	if(player_index==0){
	if(wall1==0 || (player[player_index].y+DIST_MOVE==222 && check_wall_down(player[player_index].x,player[player_index].y)==0)) {
		move_bot(player[player_index].x,player[player_index].y);
		bot=0;
		return;
	}}
	if(player_index==1){
	if(wall2==0 || (player[player_index].y-DIST_MOVE==18 && check_wall_up(player[player_index].x,player[player_index].y)==0)) {
		move_bot0(player[player_index].x,player[player_index].y);
		bot=0;
		return;
	}}
	//l'algoritmo prova a posizionare il muro davanti al giocatore o di fianco in verticale
	//se non riesce perche crea una trappola o sono gia presenti altri muri allora sposta il bot invece di posizionare il muro
	if(player_index==0){
				xwall=35;
				ywall=35;
				rotate=0;
				
				while(ywall+DIST_MOVE<player[player_index?0:1].y){
					ywall+=DIST_MOVE;
				}
				while(xwall+DIST_MOVE<player[player_index?0:1].x){
					xwall+=DIST_MOVE;
				}
				if(check_existing_wall(xwall,ywall)==1){
				if(xwall+DIST_MOVE<222) xwall+=DIST_MOVE;
				else if(ywall-DIST_MOVE>18) ywall-=DIST_MOVE;
				
				if(check_existing_wall(xwall,ywall)==1){
				rotate=1;
		}	
		}	
			}
	else{
				xwall=205;
				ywall=205;
				rotate=0;
				
				while(ywall-DIST_MOVE>player[player_index?0:1].y){
					ywall-=DIST_MOVE;
				}
				while(xwall-DIST_MOVE>player[player_index?0:1].x){
					xwall-=DIST_MOVE;
				}
				if(check_existing_wall(xwall,ywall)==1){
				if(xwall-DIST_MOVE>18) xwall-=DIST_MOVE;
				else if(ywall+DIST_MOVE<222) ywall+=DIST_MOVE;
				
				if(check_existing_wall(xwall,ywall)==1){
				rotate=1;
		}	
		}	
			}
		
		//se il muro non è presente crea il nuovo muro
		if(check_existing_wall(xwall,ywall)==0){
			if(rotate==1){
				W_V[W_ind_V].x=xwall;
				W_V[W_ind_V].y=ywall;
				W_ind_V++;
			}
			else{
				W_O[W_ind_O].x=xwall;
				W_O[W_ind_O].y=ywall;
				W_ind_O++;
			}
		}
		//se no muovi il giocatore
		else{
			if(player_index){
				move_bot0(player[player_index].x,player[player_index].y);
			}
			else move_bot(player[player_index].x,player[player_index].y);
			bot=0;
			return;
		}
		//se il muro creato crea una trappola elimina il muro
		
		if((player_index==0 && (check_trap_player(player[player_index].x,player[player_index].y,1)==0 || check_trap_player(player[player_index?0:1].x,player[player_index?0:1].y,2)==0))
			 || (player_index==1 && (check_trap_player(player[player_index].x,player[player_index].y,2)==0 || check_trap_player(player[player_index?0:1].x,player[player_index?0:1].y,1)==0))) {
				if(rotate==1) {
				W_ind_V--;}
				else {
				W_ind_O--;
				}
				if(player_index){
				move_bot0(player[player_index].x,player[player_index].y);
			}
			else move_bot(player[player_index].x,player[player_index].y);
				bot=0;
				return;
			}
		
		//se è valido lo disegna
		else{
			if(rotate==1){
				DrawWallV(xwall,ywall);
				moveRecord(player_index,1,1,xwall,ywall);
			}
			else {DrawWallO(xwall,ywall);
			moveRecord(player_index,1,0,xwall,ywall);}
		}
		
		//aggiorna la board del muro
		if(player_index==0) wall1--; else wall2--;
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
		
		bot=1;
		
}

