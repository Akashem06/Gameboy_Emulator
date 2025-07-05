#include "main.hpp"

#include "config.hpp"
#include "gameboy.hpp"

Config gameboy_config = {
  .trace = true,
  .disable_logs = false,
  .print_serial = true,
};

int main(int argc, char **argv) {
  Gameboy gameboy = Gameboy(&gameboy_config);

  return gameboy.run(argc, argv);
}