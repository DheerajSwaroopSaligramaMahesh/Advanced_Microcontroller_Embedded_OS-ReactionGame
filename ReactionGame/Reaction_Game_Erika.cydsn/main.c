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

#include "project.h"
#include "global.h"
#include "seven.h"
#include "game.h"
#include "arcadian.h"

// ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    timeCount++;
    CounterTick(cnt_systick);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    UART_LOG_Start();
    
    StartOS(OSDEFAULTAPPMODE);
    for(;;)
    {  
    }
}

TASK(tsk_init)
{
    //Initialising MCAL Drivers
    SEVEN_Init();
    PWM_red_Start();
    PWM_yellow_Start();
    PWM_green_Start();
    RGB_PWM_blue_Start();
    RGB_PWM_green_Start();
    RGB_PWM_red_Start();
    
    EE_system_init();
    EE_systick_start();
    UART_LOG_PutString("Welcome to Reaction Game\r\n");
    UART_LOG_PutString("\r\n");
    
    UART_LOG_PutString("Reaction test program round: 1\r\n");
    UART_LOG_PutString("Press one of the two buttons to start...\r\n");
    UART_LOG_PutString("\r\n");
    
    ActivateTask(tsk_event);
    
    //SetRelAlarm(alrm_glower, 100, 100); //Activating alarm for Glower which will trigger task glower
    //SetRelAlarm(alrm_fader, 100, 100);  //Activating alarm for Fader which will trigger task fader
    
    ActivateTask(tsk_fader);
    ActivateTask(tsk_glower);
    
    TerminateTask();
}

TASK(tsk_event)
{
    EventMaskType ev = 0;
    GAME_event_t event = GAME_NOEVENT;
     
    while(1)
    {
        // As long as no event is received it will wait
        WaitEvent(ev_Button1_Press | ev_Button2_Press | ev_Timeout);
        GetEvent(tsk_event, &ev);
        ClearEvent(ev);
        
        if(ev & ev_Button1_Press)
        {
            event = GAME_BUTTON1; // Event button 1 is pressed
        }
        else if (ev & ev_Button2_Press)
        {
            event = GAME_BUTTON2; // Event button 2 is pressed
        }
        else if (ev & ev_Timeout)
        {
            event = GAME_TIMEOUT; // Event button is pressed but timeout occured
        }
        if(GAME_NOEVENT != event)
        {  
            GAME_Play(event);
        }
    }
    TerminateTask();
}

// Interrupt function whenever button is pressed by user
CY_ISR(isr_Button)
{
    //Whenever Button 1 or Button 2 is pressed, it will pass the event to the Task
    if(Button_1_Read() == 1)
    {
        SetEvent(tsk_event, ev_Button1_Press);    
    }
    else if (Button_2_Read() == 1)
    {
        SetEvent(tsk_event, ev_Button2_Press);
    }
}

/* [] END OF FILE */
