#include "LPC17xx.h"

enum STATES{
	WAIT,
	BOARD_CHOOSE,
	PLAYERS_CHOOSE,
	ONE_BOARD_TWO_PLAYERS,
	ONE_BOARD_ONE_PLAYER,
	TWO_BOARD_TWO_PLAYER,
	TWO_BOARD_NPC,
	HANDSHAKE
};

struct Game_Mode{
	enum STATES gamestate;
};

void initialize_game(void);
void change_mode(void);
void change_option(void);
void bot_function(void);
void TextHandshake(void);
void TextResponse(void);
