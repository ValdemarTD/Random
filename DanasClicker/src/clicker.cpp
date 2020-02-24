#include "../inc/clicker.h"
#include <winuser.h>
#include <time.h>


int main(){
  ClickerStruct* clicker = init_struct();
  run_clicker(clicker);
  delete clicker;
  return 0;
}


ClickerStruct * init_struct(){
  ClickerStruct* new_clicker = new ClickerStruct;

  // Sets the initial key for toggling the clicker
  update_key(new_clicker, TOGGLE_KEY);

  // Sets default values for struct
  new_clicker->clicker_active = false;
  new_clicker->end_program = false;
  new_clicker->speed = BASE_SPEED;
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
  if(clicker->speed < LOWER_CLICKER_BOUND){
    clicker->speed = LOWER_CLICKER_BOUND;
  }
  if(clicker->speed > UPPER_CLICKER_BOUND){
    clicker->speed = UPPER_CLICKER_BOUND;
  }
}

//Good example for click and check_keys: https://github.com/sndcode/AutoClicker/blob/master/cMain.cpp

// Checks all keys for updates
void check_keys(ClickerStruct*){
  if(ASyncKeyState(E_STOP_KEY)){
    delete clicker;
    exit(1);
  }
  if(ASyncKeyState(TOGGLE_KEY)){
    clicker->clicker_active = !clicker->clicker_active;
    custom_sleep(SECOND_LENGTH_NS/2);
  }
  if(ASyncKeyState(SPEED_UP_KEY))
    update_speed(clicker, S_INCREASE);
  else if(ASyncKeyState(SPEED_DOWN_KEY))
    update_speed(clicker, S_DECREASE);
  else if(ASyncKeyState(SPEED_DOUBLE_KEY))
    update_speed(clicker, S_DOUBLE);
  else if(ASyncKeyState(SPEED_HALF_KEY))
    update_speed(clicker, S_HALVE);
  if(ASyncKeyState(END_PROGRAM_KEY))
    clicker->end_program = true;
}

void click(){
  POINT p;
  if(GetCursorPos(&p)){
    INPUT gen_input;
    MOUSEINPUT b_click;

    //Sets up base values for mouse event
    b_click.dx = p.X;
    b_click.dy = p.Y;
    b_click.mouseData = XBUTTON1;
    b_click.dwFlags = MOUSEEVENTF_ABSOLUTE & MOUSEEVENTF_LEFTDOWN;
    b_click.time = 0;

    //Sets input type to mouse and adds a mouse event
    gen_input.type = 0;
    gen_input.DUMMYUNIONNAME.mi = b_click;

    //Button down
    SendInput(1, &gen_input, sizeof gen_input);

    //Changes to a button up event
    b_click.dwFlags = MOUSEEVENTF_ABSOLUTE & MOUSEEVENTF_LEFTUP;
    gen_input.DUMMYUNIONNAME.mi = b_click;

    //Button up
    SendInput(1, &gen_input, sizeof gen_input);
  }
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
  while(true){
    check_keys(clicker);
    if(clicker->end_program)
      break;
    if(clicker->clicker_active && clicker->speed > 0){
      click();
      custom_sleep(SECOND_LENGTH_NS/clicker->speed);
    }
  }
}
