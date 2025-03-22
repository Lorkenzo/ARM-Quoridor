/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               TouchPanel.c
** Descriptions:            The TouchPanel application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "../GLCD/GLCD.h"
#include "../TouchPanel/TouchPanel.h"
#include "..\RIT\RIT.h"


/*******************************************************************************
* Function Name  : TP_DrawPoint
* Description    : 在指定座标画点
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos)
{
  LCD_SetPoint(Xpos,Ypos,White);  
}	

/*******************************************************************************
* Function Name  : Drawings
* Description    : 在指定座标画十字准星
* Input          : - Xpos: Row Coordinate
*                  - Ypos: Line Coordinate 
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/

void DrawSquare(uint16_t Xpos,uint16_t Ypos)
{
	int count=0;
  int i=0;
	int j=0;
	int k;
	int ystart=Ypos;
	for(i=0;i<7;i++){
		Xpos=ystart;
		for(j=0;j<7;j++){
			
				if(count%2==0){
				for(k=14;k>=0;k--){	
			  LCD_DrawLine(Xpos-k,Ypos+k,Xpos-k,Ypos-k,0x0);				
				LCD_DrawLine(Xpos-k,Ypos-k,Xpos+k,Ypos-k,0x0);				
				LCD_DrawLine(Xpos+k,Ypos-k,Xpos+k,Ypos+k,0x0);
				LCD_DrawLine(Xpos+k,Ypos+k,Xpos-k,Ypos+k,0x0);

				}
				count++;
				}
				else{
					
			  for(k=14;k>=0;k--){	
			  LCD_DrawLine(Xpos-k,Ypos+k,Xpos-k,Ypos-k,0x1CC6);				
				LCD_DrawLine(Xpos-k,Ypos-k,Xpos+k,Ypos-k,0x1CC6);				
				LCD_DrawLine(Xpos+k,Ypos-k,Xpos+k,Ypos+k,0x1CC6);
				LCD_DrawLine(Xpos+k,Ypos+k,Xpos-k,Ypos+k,0x1CC6);

				}
				count++;
				
				}
				Xpos+=34;
			
		}
		Ypos+=34;
	}
	Xpos=41;
	Ypos+=24;
	for(i=0;i<3;i++){
		if(i%2==0){
			for(j=38;j>=-38;j--){
				LCD_DrawLine(Xpos-j,Ypos+34,Xpos-j,Ypos-34,0x0); 
			}
		}
		else{
			for(j=38;j>=-38;j--){
				LCD_DrawLine(Xpos-j,Ypos+34,Xpos-j,Ypos-34,White); 
			}
			/*
		    LCD_DrawLine(Xpos-38,Ypos+34,Xpos-38,Ypos-34,0x0);  //sx				
				LCD_DrawLine(Xpos-38,Ypos-34,Xpos+38,Ypos-34,0x0);  //up
				LCD_DrawLine(Xpos+38,Ypos-34,Xpos+38,Ypos+34,0x0);  //dx
				LCD_DrawLine(Xpos+38,Ypos+34,Xpos-38,Ypos+34,0x0);  //down*/		}
		Xpos+=79;
	}
  
   	
}
extern int change;	

void DrawPlayer(uint16_t Xpos,uint16_t Ypos)
{
	int distcenter;
	int i;
	int j;
	int radius=64;
	
	for(i=-15;i<15;i++){
		for(j=-15;j<15;j++){
			distcenter=i*i+j*j;
			if (distcenter<=radius){
				if(change%2==0){
				LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,White);
				}
				else LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,Red);
			}
		}
	}
	
	for(i=0,j=0;i<14;i++,j++){
		if(change%2==0){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,White);
		}
		else LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,Red);
			}
	
	if(change==0) change++;
}

void DrawPlayerDir(uint16_t Xpos,uint16_t Ypos,uint16_t Color)
{
	int distcenter;
	int i;
	int j;
	int radius=64;
	
	for(i=-15;i<15;i++){
		for(j=-15;j<15;j++){
			distcenter=i*i+j*j;
			if (distcenter<=radius){

				LCD_DrawLine(Xpos+i,Ypos+j,Xpos+i,Ypos+j,Color);
			
			}
		}
	}

			
}

extern int black1;
extern int black2;
	
void DeletePlayer(uint16_t Xpos,uint16_t Ypos){
	int distcenter;
	int i;
	int j;
	int radius=64;
	
	for(i=-15;i<15;i++){
		for(j=-15;j<15;j++){
			distcenter=i*i+j*j;
			if (distcenter<=radius){
				if(change%2==0){
				if(black1==0) LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,0x1CC6);
				else LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,Black);
				}
				else {
					if(black2==0) LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,0x1CC6);
				  else LCD_DrawLine(Xpos+i,Ypos-5+j,Xpos+i,Ypos-5+j,Black);
				}
			}
		}
	}
	
	for(i=0,j=0;i<14;i++,j++){
		if(change%2==0){
				if(black1==0) LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,0x1CC6);
				else LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,Black);
		}
		else{
			if(black2==0) LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,0x1CC6);
				else LCD_DrawLine(Xpos-i,Ypos+j,Xpos+i,Ypos+j,Black);
		}
			}
}

void DeletePlayerDir(uint16_t Xpos,uint16_t Ypos){
	int distcenter;
	int i;
	int j;
	int radius=64;
	
	for(i=-15;i<15;i++){
		for(j=-15;j<15;j++){
			distcenter=i*i+j*j;
			if (distcenter<=radius){
				if(change%2==0){
				if(black1==0) LCD_DrawLine(Xpos+i,Ypos+j,Xpos+i,Ypos+j,0x1CC6);
				else LCD_DrawLine(Xpos+i,Ypos+j,Xpos+i,Ypos+j,Black);
				}
				else {
					if(black2==0) LCD_DrawLine(Xpos+i,Ypos+j,Xpos+i,Ypos+j,0x1CC6);
				  else LCD_DrawLine(Xpos+i,Ypos+j,Xpos+i,Ypos+j,Black);
				}
			}
		}
	}
	
}
//------------------WALL----------------------

void DrawWallO(uint16_t Xpos,uint16_t Ypos){
	int i=32;
	int j;
	
	
		for(j=-1;j<1;j++){
			  LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Yellow);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Yellow);
		}
}

void DrawWallV(uint16_t Xpos,uint16_t Ypos){
	int i;
	int j=32;
	
	
		for(i=-1;i<1;i++){
			  LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Yellow);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Yellow);
		}
}

void DeleteWallO(uint16_t Xpos,uint16_t Ypos){
	int i=32;
	int j;
	
	
		for(j=-2;j<1;j++){
			  LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x98F0);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x98F0);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x98F0);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x98F0);
		}
}

void DeleteWallV(uint16_t Xpos,uint16_t Ypos){
	int i;
	int j=32;
	
	
		for(i=-2;i<1;i++){
			  LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x98F0);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x98F0);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x98F0);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x98F0);
		}
}

//-----------------MENU--------------------------

void DrawMenu(){
	int Xpos=120;
	int Ypos=70;
	int i;
	int j;
	for(i=60,j=40;j>=0;i--,j--){
				if(i>54){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Yellow);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Yellow);
				}
				else{
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x1CC6);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x1CC6);
				}
			}
	
	Ypos+=120;

	for(i=60,j=20;j>=0;i--,j--){ 
				if(i>54){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Black);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Black);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Black);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Black);
				}
				else{
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x1CC6);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x1CC6);
				}
			}
	Ypos+=50;

	for(i=60,j=20;j>=0;i--,j--){ 
				if(i>54){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Black);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Black);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Black);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Black);
				}
				else{
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x1CC6);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x1CC6);
				}
			}
	GUI_Text(82,65,(uint8_t *)"GAME MODE",Black,0x1CC6);
	GUI_Text(72,185,(uint8_t *)"Single Board",Black,0x1CC6);
	GUI_Text(80,235,(uint8_t *)"Two Boards",Black,0x1CC6);

}

void DrawStart(){
	int Xpos=120;
	int Ypos=70;
	int i;
	int j;
	for(i=60,j=40;j>=0;i--,j--){
				if(i>54){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Yellow);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Yellow);
				}
				else{
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x1CC6);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x1CC6);
				}
			}
	Ypos+=120;

	for(i=100,j=20;j>=0;i--,j--){ 
				if(i>94){
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,Yellow);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,Yellow);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,Yellow);
				}
				else{
				LCD_DrawLine(Xpos-i,Ypos+j,Xpos-i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos-i,Ypos-j,Xpos+i,Ypos-j,0x1CC6);				
				LCD_DrawLine(Xpos+i,Ypos-j,Xpos+i,Ypos+j,0x1CC6);
				LCD_DrawLine(Xpos+i,Ypos+j,Xpos-i,Ypos+j,0x1CC6);
				}
			}
	
	GUI_Text(84,65,(uint8_t *)"QUORIDOR",Black,0x1CC6);
	GUI_Text(45,185,(uint8_t *)"PRESS INT0 TO START",Black,0x1CC6);
}




/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
