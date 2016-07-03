#include "cab202_graphics.h"

int main(int argc, char *argv[]) {

  setup_screen();
  //your code goes here
  draw_char(0, 0, 'o' );
  show_screen();
  while (1);

  cleanup_screen();
}
