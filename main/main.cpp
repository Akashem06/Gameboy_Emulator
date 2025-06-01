#include "main.hpp"

#include "gameboy.hpp"

int main(int argc, char **argv) {
  Gameboy gameboy = Gameboy();

  return gameboy.run(argc, argv);
}