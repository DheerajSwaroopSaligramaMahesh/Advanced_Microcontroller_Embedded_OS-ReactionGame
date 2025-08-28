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
 * @file arcadian.c
 * @brief Implementation of LED fading and glowing operations.
 */

#include "project.h"
#include "arcadian.h"

/**
 * @brief Table defining a sequence of RGB colors and durations for glowing the LED.
 */
const RG_Glow_t RG_glow_table[] =
{
  //Red  Green  Blue  TimeInMS
    {255,  0,    0,    500},      // Red
    { 0,  255,   0,    500},      // Green
    { 0,   0,   255,   500},      // Blue
    { 0,   0,    0,    100},      // Off
    {255, 255,  255,   100},      // White
    { 0,   0,    0,    100},      // Off
    {255, 255,  255,   100},      // White
    { 0,   0,    0,    100},      // Off
    {255, 255,  255,   100},      // White
};

/**
* Function to fade and cycle through Red yellow and green LEDs
* @param none
* @return RC_SUCCESS if ok
*/
RC_t fader_Effect()
{
    // Initialization of led Intensity
    static unsigned int redIntense = 0, yellowIntense = 0, greenIntense = 0;
    
    SetRelAlarm(alrm_fader, 10, 5);
    if (redIntense < 255 && yellowIntense == 0 && greenIntense == 0) 
    {
        // Increase Red
        LED_RGB_Set(redIntense, 0, 255 - redIntense);
        redIntense++;
    } 
    else if (redIntense == 255 && yellowIntense < 255 && greenIntense == 0)
    {
        // Decrease Red, Increase Yellow
        LED_RGB_Set(255 - yellowIntense, yellowIntense, 0);
        yellowIntense++;
        
        if(yellowIntense == 255)
        {
            redIntense = 0;
        }
    }
    else if(redIntense == 0 && yellowIntense == 255 && greenIntense < 255)
    {
        // Decrease yellow, Increase Green
        LED_RGB_Set(0, 255 - greenIntense, greenIntense);
        greenIntense++;
        
        if(greenIntense == 255)
        {
            yellowIntense = 0;
        }
    }
    else
    {
        // Reset intensities
        redIntense = 0;
        yellowIntense = 0;
        greenIntense = 0;
    }
    
    return RC_SUCCESS;
}

/**
* Function to glow and cycle through the RGB LED
* @param none 
* @return RC_SUCCESS if ok
*/
RC_t glower_Effect()
{
    static int i = 0;
    
    if(i < 9)
    {
        SetRelAlarm(alrm_glower,10, RG_glow_table[i].duration);
        RGB_PWM_red_WriteCompare(RG_glow_table[i].red_rgb);
        RGB_PWM_green_WriteCompare(RG_glow_table[i].green_rgb);
        RGB_PWM_blue_WriteCompare(RG_glow_table[i].blue_rgb);
        i++;
    }
    else
    {
        i = 0;
    }
    
    return RC_SUCCESS;
}

// StartFader TASK starts the fader sequence
TASK(tsk_fader)
{
   fader_Effect();
   TerminateTask();
}

// StartGlower TASK starts the glower sequence
TASK(tsk_glower)
{
   glower_Effect();
   TerminateTask();
}

/* [] END OF FILE */
