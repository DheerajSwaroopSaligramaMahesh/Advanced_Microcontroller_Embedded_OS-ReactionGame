# Reaction Game

This project implements a simple **reaction game** as an AUTOSAR application.

## Game Description
- Upon startup, the program shows a **welcome message** via the serial port.  
- The game starts when the user presses one of the **two white buttons**.  
- After a random delay of **1s to 3s**, a random value (`1` or `2`) is displayed on both 7-segment displays.  

### Rules
- If **`1`** is displayed → Press the **right button**.  
- If **`2`** is displayed → Press the **left button**.  
- **Correct press** → The measured **reaction time (ms)** is shown.  
- **Wrong press** → An **error message** is displayed.  
- **No press within 1s** → The message **“Too slow”** is shown.  
- The game can be restarted anytime by pressing one of the two buttons.

### Game Flow
- One game consists of **10 rounds**.  
- At the end of the game, the following statistics are shown:
  - **Score** (number of correct button presses)  
  - **Total time**  
  - **Average time**  

---

# Arcadian Style Light

In this part, we implement an **Arcadian style fading traveling light**.  
Three LEDs glow in the following sequence:

![Arcadian Light Pattern](/ReactionGame/Images/arcadian.png)

## RGB LED Glow Function
We define a glow sequence using a **constant configuration table**:  

```c
const RG__Glow_t RG_glowtable_1[] = {
    // Red  Green  Blue   TimeInMS
    {255,   0,     0,     500},   // Red
    {0,   255,     0,     500},   // Green
    {0,     0,   255,     500},   // Blue
    {0,     0,     0,     100},   // Off
    {255, 255,   255,     100},   // White
    {0,     0,     0,     100},   // Off
    {255, 255,   255,     100},   // White
    {0,     0,     0,     100},   // Off
    {255, 255,   255,     100}    // White
};
