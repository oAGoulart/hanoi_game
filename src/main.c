/* Augusto Goulart (1901560080) 28/03/2023 12:54:00 */
#include "../include/game.h"

void print_help(char* name)
{
  printf("\nSolve the Tower of Hanoi puzzle."
          "\nUsage: %s [OPTION]\n"
          "\n\t-h\t--help\tShow this help message."
          "\n\t-s\t--solve\tSolve the puzzle by pressing TAB.", name);
}

int main(int argc, char** argv)
{
  boolean_t solve = FALSE;

  if (argc == 2) {
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
      print_help(argv[0]);
    else if (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "--solve") == 0)
      solve = TRUE;
    else
      __throw("Invalid argument");
  }
  else if (argc > 2) __throw("Too many arguments");

  game_t* game;
  game_create(&game);

  game_run(game, solve);

  game_destroy(&game);
  return 0;
}
