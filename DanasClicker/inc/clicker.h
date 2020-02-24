#pragma once
#include <winuser.h>


/* VK_SHIFT = 0x10
 * VK_UP = 0x26
 * VK_RIGHT = 0x27
 * VK_DOWN = 0x28
 * VK_LEFT = 0x25
 * VK_CONTROL = 0x11
 */
#define TOGGLE_KEY = 0x10
#define SPEED_UP_KEY = 0x26
#define SPEED_DOUBLE_KEY = 0x27
#define SPEED_DOWN_KEY = 0x28
#define SPEED_HALF_KEY = 0x25
#define END_PROGRAM_KEY = 0x11

#define UPPER_CLICKER_BOUND = 500
#define LOWER_CLICKER_BOUND = 0

#define SECOND_LENGTH_NS = 1000000000

// enums speed modifiers
enum{S_INCREASE, S_DECREASE, S_DOUBLE, S_HALVE};

typedef struct ClickerStruct{
  bool clicker_active; //whether the clicker is running on/off
  bool end_program; //exit clicker
  int toggle_key; //toggle clicker on/off
  int speed; //hz
}ClickerStruct;

// Initializes the struct with default values
ClickerStruct * init_struct();

// Updates the toggle key
//TODO: Allow updates for other keys
void update_key(ClickerStruct*, int);

// Modifies the speed by the int value
void update_speed(ClickerStruct*, int);

// Checks all keys for updates
void check_keys(ClickerStruct*);

// Clicks the left mouse button
void click();

// Custom sleep function
void custom_sleep(int);

// Runs the clicker inside of main
void run_clicker(ClickerStruct*);
