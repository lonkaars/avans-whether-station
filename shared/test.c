#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "protocol.h"

void ws_protocol_res_last_records(ws_s_protocol_parsed_cmd* parsed_cmd, ws_s_protocol_response* response) {
	printf("last-records detected!\n");
}

int main() {
  // disable echo and enable raw mode
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ECHO | ICANON);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, 0, &term);

  ws_s_protocol_parser_state* parser1 = ws_protocol_parser_alloc();

  for(;;) {
    fflush(stdout);

    char byte;
    while(read(STDIN_FILENO, &byte, 1) > 0)
      ws_protocol_parse_byte(parser1, byte);
  }

  ws_protocol_parser_free(parser1);

  return 0;
}
