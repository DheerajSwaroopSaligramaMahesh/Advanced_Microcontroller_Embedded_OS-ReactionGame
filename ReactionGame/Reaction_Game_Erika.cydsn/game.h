/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

/**
 * @file game.h
 * @brief Header file for the reaction time game implementation.
 *
 * This file defines the game constants, enums, and function declarations
 * used in the reaction time game.
 */

#ifndef GAME_H
#define GAME_H
#include "global.h"

/** @brief Total number of game rounds. */
#define TOTAL_ROUNDS 10

uint8_t randomDelay;       // To store the random delay time
uint8_t randomValue;       // To store the value seven segment is displaying
static int timeCount = 0;  // To count the time taken by user to press the button
static int score = 0;      // To print the score of each round whenever user presses correct button
static int round = 1;      // To print which round of game is currently executing 
    
/*
Declaring an enum called GAME_event_t wherein it has enum constants as:
1) No Button is pressed : GAME_NOEVENT
2) Button 1 is pressed
3) Button 2 is pressed
4) Button was not pressed within the timeout period.
*/
typedef enum
{
    GAME_NOEVENT,
    GAME_BUTTON1,
    GAME_BUTTON2,
    GAME_TIMEOUT
} GAME_event_t;

/**
 * @brief Handles the main game logic and state transitions.
 *
 * @param ev The current game event.
 * @return RC_t Returns a status code indicating the success or failure of the operation.
 */
RC_t GAME_Play(GAME_event_t);

#endif

/* [] END OF FILE */
