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
 * @file game.c
 * @brief Implementation of the reaction time game.
 *
 * This file contains the game logic, including state transitions,
 * random delay generation, and seven-segment display updates.
 */

#include "project.h"
#include <stdlib.h>
#include <stdio.h> 
#include "game.h" 
#include "seven.h"

/**
 * @brief Waits for a random delay between 1 and 3 seconds.
 *
 * @return uint8_t The generated random delay time in seconds.
 */
uint8_t WaitForRandomDelay(void)
{
    randomDelay = (rand() % 3) + 1;
    CyDelay(randomDelay * 1000);
    
    return randomDelay;
}

/**
 * @brief Displays a random value (1 or 2) on the seven-segment displays.
 *
 * @return uint8_t The randomly generated value displayed.
 */
uint8_t DisplayRandomValue(void)
{
    randomValue = (rand() % 2) + 1;

    SEVEN_Set(SEVEN_0, randomValue); 
    SEVEN_Set(SEVEN_1, randomValue); 
    
    return randomValue;
}

/**
 * @enum GAME__State_t
 * @brief Enumerates the states of the game.
 */
typedef enum
{
    IDLE_STATE,             /**< Waiting for user input to start the game. */
    SEGMENT_WAITING_STATE,  /**< Waiting for the random value to be displayed. */
    BUTTON_WAITING_STATE    /**< Waiting for the user to press a button. */
} GAME__State_t;            

static GAME__State_t GAME__State = IDLE_STATE;

/**
 * @brief Timer task that increments the `timeCount` variable every millisecond.
 */
TASK(tsk_timer)
{
    timeCount++;
    TerminateTask(); 
}

/**
 * @brief Main function for handling game logic and state transitions.
 *
 * This function handles the different game states, tracks the user's reaction time,
 * and calculates the score and total time across multiple rounds.
 *
 * @param ev The current game event.
 * @return RC_t Returns a status code indicating the success or failure of the operation.
 */
RC_t GAME_Play(GAME_event_t ev)
{
    static uint32_t totalTime = 0;
    static uint32_t averageTime = 0;
    
    // Check if the game round has reached the limit
    if (round > TOTAL_ROUNDS)
    {
        return RC_SUCCESS;
    }
    
    switch (GAME__State)
    {
        // user to press any button to start the game and then wait for ~3 seconds   
        case IDLE_STATE :
            if (GAME_BUTTON1 == ev || GAME_BUTTON2 == ev)
            {
                SEVEN_Init();
                SetRelAlarm(alrm_random_time, WaitForRandomDelay(), 0);
                GAME__State = SEGMENT_WAITING_STATE; 
            }
            break;
        
        // Waiting to display random digit on seven segment
        case SEGMENT_WAITING_STATE : 
            if (GAME_TIMEOUT == ev)
            {   
                CancelAlarm(alrm_random_time);
                DisplayRandomValue();
                timeCount = 0;
                SetRelAlarm(alrm_timer, 1, 1);       // Starting the stop watch timer
                SetRelAlarm(alrm_timeout, 1000, 0);  // Timeout if no button press within 1 second
                GAME__State = BUTTON_WAITING_STATE;
            }
            break; 
        
        // Waiting for user to press the button after display
        case BUTTON_WAITING_STATE : 
            if (GAME_TIMEOUT == ev)
            {
                UART_LOG_PutString("Too Slow\r\n");
                SEVEN_Init();
            }
            
            if (GAME_BUTTON1 == ev || GAME_BUTTON2 == ev)
            {
                CancelAlarm(alrm_timer); //Stop the counter as soon as user press button
                
                if ((GAME_BUTTON1 == ev && randomValue == 2 && timeCount < 1000) ||
                    (GAME_BUTTON2 == ev && randomValue == 1 && timeCount < 1000))
                {
                    UART_LOG_PutString("Great - correct button pressed\r\n");
                    UART_LOG_PutString("Reaction time in ms: ");
                    
                    char showReactionTime[200];
                    sprintf(showReactionTime,"%d\r\n", timeCount);
                    UART_LOG_PutString(showReactionTime);
                    
                    score++;
                    totalTime += timeCount;
                    
                    SEVEN_Init();
                }
                else
                {
                    UART_LOG_PutString("Wrong button pressed.\r\n");
                    SEVEN_Init();
                }
            }
            
            round++;

            if ((GAME_BUTTON1 == ev || GAME_BUTTON2 == ev || GAME_TIMEOUT == ev) &&
                 round <= TOTAL_ROUNDS)
            {
                /* Before transitioning back to IDLE_STATE for the next round,
                   print the round transition messages */
                UART_LOG_PutString("========================================\r\n");
                UART_LOG_PutString("Reaction test program round: ");
                
                char showRound[200];
                sprintf(showRound, "%d\r\n", round);
                UART_LOG_PutString(showRound);
                
                UART_LOG_PutString("Press one of the two buttons to start...\r\n");
                UART_LOG_PutString("\r\n");
                
                GAME__State = IDLE_STATE;
            }
                
            if (round > TOTAL_ROUNDS)
            {
                UART_LOG_PutString("========================================\r\n");
                UART_LOG_PutString("Game Over\r\n");

                char showScore[200];
                sprintf(showScore,"Score = %d\r\n", score);
                UART_LOG_PutString(showScore);

                char showTotalTime[200];
                sprintf(showTotalTime,"Total Time in ms = %u\r\n", totalTime);
                UART_LOG_PutString(showTotalTime);
                
                if (score > 0)
                {
                    averageTime = totalTime / score;
                }
                else
                {
                    averageTime = 0;
                }
                char showAverageTime[200];
                sprintf(showAverageTime, "Average Time in ms = %u\r\n", averageTime);
                UART_LOG_PutString(showAverageTime);
            }
            
            break;
    }
    return RC_SUCCESS;
}
/* [] END OF FILE */
