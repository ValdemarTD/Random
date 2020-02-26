#include "../inc/clicker.h"
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <string>
#pragma comment(lib, "User32.lib")

int main(){
  ClickerStruct* clicker = init_struct();
  greeting_message();
  run_clicker(clicker);
  delete clicker;
  return 0;
}

ClickerStruct * init_struct(){
  ClickerStruct* new_clicker = new ClickerStruct;

#if DEBUG
  std::cout << "Struct initializing" << std::endl;
#endif // DEBUG


  // Sets the initial key for toggling the clicker
  update_key(new_clicker, TOGGLE_KEY);

  // Sets default values for struct
  new_clicker->clicker_active = false;
  new_clicker->end_program = false;
  new_clicker->speed = BASE_SPEED;

  return new_clicker;

}

// Updates toggle key. Individual function for future features (GUI and custom keybindings)
void update_key(ClickerStruct* clicker, int toggle_key){
#if DEBUG
    std::cout << "Toggle key updated" << std::endl;
#endif // DEBUG

  clicker->toggle_key = toggle_key;
}

// Increments the speed of the clicker in hz by the given amount
void update_speed(ClickerStruct* clicker, int speed_mod){
#if DEBUG
    std::cout << "Changing speed to: ";
#endif
  switch (speed_mod) {
    case S_INCREASE: clicker->speed++;
            break;
    case S_DECREASE: clicker->speed--;
            break;
    case S_DOUBLE: clicker->speed = clicker->speed * 2;
            break;
    case S_HALVE: clicker->speed = clicker->speed / 2;
    default: break;
  }
  if(clicker->speed < LOWER_CLICKER_BOUND){
    clicker->speed = LOWER_CLICKER_BOUND;
  }
  if(clicker->speed > UPPER_CLICKER_BOUND){
    clicker->speed = UPPER_CLICKER_BOUND;
  }
#if DEBUG
  std::cout << clicker->speed << std::endl;
#endif
}

//Good example for click and check_keys: https://github.com/sndcode/AutoClicker/blob/master/cMain.cpp

// Checks all keys for updates
void check_keys(ClickerStruct* clicker){
  if(GetAsyncKeyState(E_STOP_KEY)){
    delete clicker;
    exit(1);
  }
  if(GetAsyncKeyState(TOGGLE_KEY)){
    clicker->clicker_active = !clicker->clicker_active;
    custom_sleep(SECOND_LENGTH_NS/2);
    #if DEBUG
      std::cout << "Clicker toggled" << std::endl;
    #endif
  }
  if(GetAsyncKeyState(SPEED_UP_KEY)){
    update_speed(clicker, S_INCREASE);
    custom_sleep(SECOND_LENGTH_NS/50);
  }
  else if(GetAsyncKeyState(SPEED_DOWN_KEY)){
    update_speed(clicker, S_DECREASE);
    custom_sleep(SECOND_LENGTH_NS/50);
  }
  else if(GetAsyncKeyState(SPEED_DOUBLE_KEY)){
    update_speed(clicker, S_DOUBLE);
    custom_sleep(SECOND_LENGTH_NS/50);
  }
  else if(GetAsyncKeyState(SPEED_HALF_KEY)){
    update_speed(clicker, S_HALVE);
    custom_sleep(SECOND_LENGTH_NS/50);
  }
  if(GetAsyncKeyState(END_PROGRAM_KEY)){
    clicker->end_program = true;
    custom_sleep(SECOND_LENGTH_NS/100);
  }
}

void click(){
  POINT p;
  if(GetCursorPos(&p)){
    SetCursorPos(p.x, p.y);
    mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
  }
}

// Sleep code modified from macklin01 on this forum: https://www.overclockers.com/forums/showthread.php/263352-Wait-command-in-C
void custom_sleep(int wait_length){
  clock_t wait_nanoseconds = (clock_t) wait_length;
  clock_t start_time = clock();
  while(clock() <= start_time + wait_nanoseconds);
  return;
}

// Runs the autoclicker loop
void run_clicker(ClickerStruct* clicker){
  while(true){
    check_keys(clicker);
    if(clicker->end_program)
      break;
    if(clicker->clicker_active && clicker->speed > 0){
      click();
      #if DEBUG
        std::cout << "Clicked" << std::endl;
      #endif
      custom_sleep(SECOND_LENGTH_NS/clicker->speed);
    }
    else{
      custom_sleep(SECOND_LENGTH_NS/5);
    }

  }
}

// Shows starting message
void greeting_message(){
  printf("Welcome to Dana's Autoclicker V1.0! Below are the current keybindings\n\n");
  printf("Shift: Turn the clicker on or off\n");
  printf("Control: Exit the clicker entirely\n");
  printf("Up arrow: Incrase the clicker speed by one click per second\n");
  printf("Down arrow: Decrease the clicker speed by one click per second\n");
  printf("Left arrow: Cut the clicker speed in half\n");
  printf("Right arrow: Double the clicker speed\n");
  printf("Escape key: Emergency stop\n\n");
  printf("The current maximum speed for the clicker is %d clicks per second\n", UPPER_CLICKER_BOUND);
  printf("The current starting speed for the clicker is %d clicks per second\n\n", BASE_SPEED);
  printf("I hope you enjoy your clicking experience!\n\n");
  printf("Sincerely,\n");
  printf("Zachary Lee, AKA ValdemarTD\n");
}
