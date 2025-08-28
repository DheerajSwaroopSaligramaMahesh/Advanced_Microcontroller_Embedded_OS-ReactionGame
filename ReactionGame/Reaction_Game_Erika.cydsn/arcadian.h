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
 * @file arcadian.h
 * @brief Header file for LED fading and glowing operations.
 */

#ifndef ARCADIAN_H
#define ARCADIAN_H
    
#include "global.h"
#include "project.h"
#include "led.h"

/**
 * @struct RG_Glow_t
 * @brief Structure to define the RGB color and duration for LED glowing.
 * 
 * @var RG_Glow_t::red
 * Red intensity (0-255).
 * 
 * @var RG_Glow_t::green
 * Green intensity (0-255).
 * 
 * @var RG_Glow_t::blue
 * Blue intensity (0-255).
 * 
 * @var RG_Glow_t::duration
 * Duration (in milliseconds) for this RGB configuration.
 */
typedef struct
{
    uint8_t red_rgb;
    uint8_t green_rgb;
    uint8_t blue_rgb;
    uint16_t duration;
} RG_Glow_t;

/**
* Function to fade and cycle through Red yellow and green LEDs
* @param none
* @return RC_SUCCESS if ok
*/    
RC_t fader_Effect(void);
/**
* Function to glow and cycle through the RGB LED
* @param none 
* @return RC_SUCCESS if ok
*/
RC_t glower_Effect(void);

#endif

/* [] END OF FILE */
