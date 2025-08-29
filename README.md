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
```
---

# How to Use

Follow the steps below to build and run the project on hardware:

1. **Download the Project**  
   - Clone this repository or download the ZIP file directly from GitHub.  
   - Extract the contents if downloaded as ZIP.  

2. **Import into PSoC Creator**  
   - Open **PSoC Creator (version 4.4 or higher recommended)**.  
   - Use *File → Import Project* and select the extracted project folder.  

3. **Build the Project**  
   - Compile the project by clicking on **Build → Build <ProjectName>**.  
   - Ensure there are no build errors.  

4. **Flash to Hardware**  
   - Connect the **PSoC 5LP development board** (with 7-segment display and push buttons mounted on PCB).  
   - Use **Program → Program Device** in PSoC Creator to flash the firmware.  

5. **Play the Game**  
   - Once the board is programmed, open the **serial terminal** (baud rate as configured in code).  
   - Press either button to start a round.  
   - Follow the on-screen instructions and enjoy the reaction game!
