#include "TouchLib.h"

TouchLib::TouchLib(LGFX_Device* display) {
    _tft = display;
    _pos = {0, 0, false};
    _lastTouchTime = 0;
}

bool TouchLib::update() {
    _pos.touched = _tft->getTouch(&_pos.x, &_pos.y);
    return _pos.touched;
}

bool TouchLib::isAreaPressed(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    if (!_pos.touched) return false;
    
    // Lógica de colisão
    return (_pos.x >= x && _pos.x <= (x + w) && 
            _pos.y >= y && _pos.y <= (y + h));
}

bool TouchLib::buttonPressed(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t debounceMs) {
    if (isAreaPressed(x, y, w, h)) {
        if (millis() - _lastTouchTime > debounceMs) {
            _lastTouchTime = millis();
            return true;
        }
    }
    return false;
}