#ifndef _WIN32
#include <termios.h>
#include <unistd.h>

static struct termios old_tio_i;

void init_direct_mode() {
  struct termios tio = {0};
  tcgetattr(STDIN_FILENO, &tio);
  old_tio_i = tio;
  tio.c_lflag &= ~(ICANON | ECHO);
  tio.c_cc[VMIN] = 1;
  tio.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &tio);
}

void reset_term() { tcsetattr(STDIN_FILENO, TCSADRAIN, &old_tio_i); }

#else

void init_direct_mode() {}
void reset_term() {}

#endif
