#ifndef TOUCHLIB_H
#define TOUCHLIB_H

#include <LovyanGFX.hpp>

// Estrutura para facilitar a leitura de coordenadas
struct TouchPos {
    uint16_t x;
    uint16_t y;
    bool touched;
};

class TouchLib {
public:
    TouchLib(LGFX_Device* display);

    // Atualiza o estado do touch e retorna se houve toque
    bool update();

    // Verifica se uma área específica foi tocada (Hitbox)
    bool isAreaPressed(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

    // Funções de conveniência para botões com debounce
    bool buttonPressed(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t debounceMs = 200);

    // Getters para as coordenadas atuais
    uint16_t getX() { return _pos.x; }
    uint16_t getY() { return _pos.y; }

private:
    LGFX_Device* _tft;
    TouchPos _pos;
    uint32_t _lastTouchTime;
};

#endif