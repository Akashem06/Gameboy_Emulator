#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SDLUI_Debugger {
public:
    SDLUI_Debugger();
    ~SDLUI_Debugger();

    void set_developer_name(const std::string &name);
    void set_ly(int ly);
    void set_instruction_cycles(int cycles);
    void set_status_text(const std::string &text);

    void set_registers(uint16_t af, uint16_t bc, uint16_t de, uint16_t hl, uint16_t sp, uint16_t pc);

    void render();

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    TTF_Font *font;

    std::string developer_name;
    int ly;
    int instruction_cycles;
    std::string status_text;

    uint16_t reg_af, reg_bc, reg_de, reg_hl, reg_sp, reg_pc;

    void draw_text(int x, int y, const std::string &text);
};
