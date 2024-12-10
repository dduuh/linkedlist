#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

int main(int argc, char* argv[])
{
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    fprintf(stdout, "Welcome, my user!\n  Options:\n  \t--run  (running program)\n  \t--help (see information, so you're here)\n");
    return 0;
  } else if (argc == 2 && strcmp(argv[1], "--run") == 0) {
    run();
  } else {
    if (argv[1] != NULL) {
      fprintf(stderr, "Unknown command: %s\nUse: --help", argv[1]);
    } else {
      fprintf(stderr, "Usage: %s <option>\nUse: --help", argv[0]);
    }
    return 1;
  }
  return 0;
}