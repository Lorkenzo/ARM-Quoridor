/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               TouchPanel.h
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

#ifndef _TOUCHPANEL_H_
#define _TOUCHPANEL_H_

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"

/* Private typedef -----------------------------------------------------------*/
typedef	struct POINT 
{
   uint16_t x;
   uint16_t y;
}Coordinate;


typedef struct Matrix 
{						
long double An,  
            Bn,     
            Cn,   
            Dn,    
            En,    
            Fn,     
            Divider ;
} Matrix ;

/* Private variables ---------------------------------------------------------*/
extern Coordinate ScreenSample[3];
extern Coordinate DisplaySample[3];
extern Matrix 		matrix ;
extern Coordinate display ;

#define	CHX 	        0x90 	/* 通道Y+的选择控制字 */	
#define	CHY 	        0xd0	/* 通道X+的选择控制字 */

#define SSPSR_RNE       2
#define SSPSR_BSY       4

/* bit-frequency = PCLK / CPSR */
#define SPI_SPEED_4MHz    18 	  /* 4MHz */
#define SPI_SPEED_2MHz    36 	  /* 2MHz */
#define	SPI_SPEED_1MHz	  72	  /* 1MHz */
#define	SPI_SPEED_500kHz  144	  /* 500kHz */
#define SPI_SPEED_400kHz  180	  /* 400kHz */


/* Private function prototypes -----------------------------------------------*/				
void DrawStart(void);
void DrawMenu(void);
void DrawSquare(uint16_t Xpos,uint16_t Ypos);	
void DrawPlayer(uint16_t Xpos,uint16_t Ypos);	
void DeletePlayer(uint16_t Xpos,uint16_t Ypos);	
void DrawPlayerDir(uint16_t Xpos,uint16_t Ypos,uint16_t Color);
void DeletePlayerDir(uint16_t Xpos,uint16_t Ypos);	
void DrawWallO(uint16_t Xpos,uint16_t Ypos);	
void DrawWallV(uint16_t Xpos,uint16_t Ypos);	
void DeleteWallO(uint16_t Xpos,uint16_t Ypos);	
void DeleteWallV(uint16_t Xpos,uint16_t Ypos);						
void TP_DrawPoint(uint16_t Xpos,uint16_t Ypos);
uint8_t getDisplayPoint(Coordinate * displayPtr,Coordinate * screenPtr,Matrix * matrixPtr );

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


