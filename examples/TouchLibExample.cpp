#include <TouchLib.h>

TouchLib touch(&tft); // Cria a instância vinculada ao seu objeto tft

bool KeyPadLoop() {
    if (!touch.update()) return false;

    // Exemplo: Botão MENU
    if (touch.buttonPressed(5, 5, 80, 30)) {
        b_MENU = true;
        return true;
    }

    // Exemplo: Lógica de Controle (Zonas da tela)
    if (touch.isAreaPressed(0, 120, 120, 120)) { // Canto inferior esquerdo
        ClearKeys();
        b_LEFT = true;
        return true;
    }
    
    return false;
}