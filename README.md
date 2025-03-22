# ARM-Quoridor

# APPLICATION NOTE FILE: QUORIDOR GAME

## 1. Game Overview
Quoridor Game is a strategy game created and inspired by the board game of the same name, published in 1997 by Gigamic. The game consists of a 7x7 chessboard (reduced from the original 9x9) and 8 walls per player, for a maximum total of 16 walls (reduced from the original 20 maximum). The goal of the game is to reach the opposite side of the board.

## 2. Development Environment and Compatibility
The game code and functionalities have been created and tested for use on the LPC1768 System-on-Chip (SoC), which supports an ARM Cortex-M3 microprocessor on a Landtiger development board.  
The game is playable in its **ONE BOARD** version on a single Landtiger board, or in the **TWO BOARDS** version with two Landtiger boards connected via a CAN interface.

## 3. Controls

### Buttons:
- **INT0**: Used to start the game from the initial screen or as a reset during gameplay.
- **KEY1**: Used to switch between movement mode and wall placement mode.
- **KEY2**: Used in wall mode to change the wall orientation.

### Joystick:
- **UP/LEFT/RIGHT/DOWN**: Moves the player or wall in the four directions based on the selected move mode. Also used to change game options in the main menu.
- **SELECT**: Confirms the selected move and changes turn. Confirms menu options.
- **UP-LEFT/UP-RIGHT/DOWN-LEFT/DOWN-RIGHT**: See special rules.

## 4. Special Rules
Even if walls are available, it is not possible to place one and press SELECT if:
- It is totally or partially overlapping an already placed wall.
- It creates a trap for the opponent and prevents their possible victory.

You can jump over the opponent if they are face-to-face in one of the four directions, unless there is a wall behind them. In that case, an oblique jump to the side of the opponent is allowed (if not blocked by walls) by using the joystick diagonally and pressing SELECT.

For further information on the game rules: [Quoridor Rules](https://www.ultraboardgames.com/quoridor/game-rules.php#:~:text=Quoridor%20Game%20Rules%201%20Components%20one%20board%2020,Face%20...%207%20End%20of%20the%20Game%20)

## 5. NPC Implementation
The NPC is implemented using a depth-first search algorithm, which searches for the path to victory by keeping track of the path taken and moves made. If the algorithm encounters a dead end, it backtracks to find an exit. Once a path is found, the NPC performs the next move recorded by the algorithm to reach victory.

## 6. Playing on a Single Landtiger Board
The game on a single board only supports the **ONE BOARD** mode. If attempting to select **TWO BOARDS** mode, the game will not detect any connected boards and will automatically return to the main menu.  
Single-board gameplay allows playing against another player or against an NPC.

## 7. Playing on Dual Landtiger Boards
With two boards connected via CAN1, the **TWO BOARDS** mode is available, and each player can choose to play as either a player or an NPC. Ensure that the cables are properly connected and that the game is loaded on both boards, followed by pressing the RESET button.
