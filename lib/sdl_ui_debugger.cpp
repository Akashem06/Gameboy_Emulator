#include "sdl_ui_debugger.hpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <iomanip>

static std::string to_hex16(uint16_t val) {
    std::stringstream ss;
    ss << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << val;
    return ss.str();
}

SDLUI_Debugger::SDLUI_Debugger()
    : ly(0), instruction_cycles(0), developer_name(""), status_text(""),
      reg_af(0), reg_bc(0), reg_de(0), reg_hl(0), reg_sp(0), reg_pc(0),
      window(nullptr), renderer(nullptr), texture(nullptr), font(nullptr)
{
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) != 0) {
        std::cerr << "Failed to create SDL window/renderer: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetWindowTitle(window, "Debug Info");
    SDL_ShowWindow(window); // Ensure it appears in front

    font = TTF_OpenFont("utils/RobotoMono[200].ttf", 14);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    } else {
        std::cout << "Font loaded successfully.\n";
    }
}

SDLUI_Debugger::~SDLUI_Debugger() {
    if (font) TTF_CloseFont(font);
    if (texture) SDL_DestroyTexture(texture);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    TTF_Quit();
}

void SDLUI_Debugger::set_developer_name(const std::string &name) {
    developer_name = name;
}

void SDLUI_Debugger::set_ly(int value) {
    ly = value;
}

void SDLUI_Debugger::set_instruction_cycles(int cycles) {
    instruction_cycles = cycles;
}

void SDLUI_Debugger::set_status_text(const std::string &text) {
    status_text = text;
}

void SDLUI_Debugger::set_registers(uint16_t af, uint16_t bc, uint16_t de, uint16_t hl, uint16_t sp, uint16_t pc) {
    reg_af = af;
    reg_bc = bc;
    reg_de = de;
    reg_hl = hl;
    reg_sp = sp;
    reg_pc = pc;
}

void SDLUI_Debugger::draw_text(int x, int y, const std::string &text) {
    if (!font) return;

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (!surface) return;

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!textTexture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &dst);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(textTexture);
}

void SDLUI_Debugger::render() {
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    int y = 10;
    draw_text(10, y, "Developer: " + developer_name); y += 30;
    draw_text(10, y, "LY: " + std::to_string(ly)); y += 30;
    draw_text(10, y, "Instruction Cycles: " + std::to_string(instruction_cycles)); y += 30;
    draw_text(10, y, "Status: " + status_text); y += 40;

    draw_text(10, y, "AF: 0x" + to_hex16(reg_af)); y += 20;
    draw_text(10, y, "BC: 0x" + to_hex16(reg_bc)); y += 20;
    draw_text(10, y, "DE: 0x" + to_hex16(reg_de)); y += 20;
    draw_text(10, y, "HL: 0x" + to_hex16(reg_hl)); y += 20;
    draw_text(10, y, "SP: 0x" + to_hex16(reg_sp)); y += 20;
    draw_text(10, y, "PC: 0x" + to_hex16(reg_pc)); y += 20;

    SDL_RenderPresent(renderer);
}
