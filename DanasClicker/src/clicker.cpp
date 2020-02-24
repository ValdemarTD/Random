#include "../inc/clicker.h"
#include <winuser.h>
#include <time.h>


int main(){
  ClickerStruct* clicker = init_struct();
  run_clicker(clicker);
  return 0;
}


ClickerStruct * init_struct(){
  ClickerStruct* new_clicker = new ClickerStruct;

  // Sets the initial key for toggling the clicker
  update_key(new_clicker, TOGGLE_KEY);

  // Sets default values for struct
  new_clicker->clicker_active = false;
  new_clicker->end_program = false;
  new_clicker->speed = 20;
}

// Updates toggle key. Individual function for future features (GUI and custom keybindings)
void update_key(ClickerStruct* clicker, int toggle_key){
  clicker->toggle_key = toggle_key;
}

// Increments the speed of the clicker in hz by the given amount
void update_speed(ClickerStruct* clicker, int speed_mod){
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
}

//Good example for click and check_keys: https://github.com/sndcode/AutoClicker/blob/master/cMain.cpp

// Checks all keys for updates
void check_keys(ClickerStruct*){

}

void click(){

}

// Sleep code modified from macklin01 on this forum: https://www.overclockers.com/forums/showthread.php/263352-Wait-command-in-C
void custom_sleep(int wait_length){
  clock_t wait_nanoseconds = (clock_t) wait_length;
  clock_t start_time = clock();
  while(clock() != start_time + wait_nanoseconds);
  return;
}

// Runs the autoclicker loop
void run_clicker(ClickerStruct* clicker){
  while(!clicker->end_program){
    check_keys(clicker);
    if(clicker->end_program)
      break;
    if(clicker->clicker_active && clicker->speed > 0){
      click();
      custom_sleep(SECOND_LENGTH_NS/clicker->speed);
    }
  }
}
