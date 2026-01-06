<img width="838" height="420" alt="image" src="https://github.com/user-attachments/assets/a4fdc501-041e-48ae-b1a4-5d2304619fc6" />
# TouchLib 🚀
Uma biblioteca leve e eficiente para gerenciamento de toque e criação de botões interativos para ESP32-2432S028 (conhecido como "Cheap Yellow Display" ou CYD) utilizando a stack LovyanGFX.

# 📌 Descrição
A TouchLib simplifica a detecção de áreas de toque (hitboxes) e a criação de botões táteis. Ela foi desenhada especificamente para facilitar a transição de lógicas complexas de jogos (como Tetris) para sistemas de menus e interfaces de usuário (UI).

# ✨ Recursos
Detecção de Áreas: Defina retângulos de colisão para transformar qualquer parte da tela em um botão.

Debounce Integrado: Evita múltiplos acionamentos com um único toque.

Integração LovyanGFX: Funciona nativamente com objetos LGFX.

Leve: Otimizada para o ESP32, ocupando o mínimo de memória RAM.

# 🛠️ Instalação
Baixe este repositório como .zip.

No Arduino IDE, vá em Screctch -> Incluir Biblioteca -> Adicionar Biblioteca .ZIP.

Certifique-se de ter a biblioteca LovyanGFX instalada.

# 🚀 Como usar
1. Inicialização
C++

#include <LovyanGFX.hpp>
#include <TouchLib.h>

LGFX tft; 
TouchLib touch(&tft); // Passa a instância do display para a biblioteca

			void setup() {
			tft.init();
			tft.setRotation(1);
			}
# 2. No Loop Principal
Você pode usar isAreaPressed para controles contínuos (como o direcional de um jogo) ou buttonPressed para ações únicas (como abrir um menu).

C++

			void loop() {
			  // Atualiza as coordenadas do touch
			  if (touch.update()) {
    
			    // Lógica de Botão com Debounce (Ação única)
			    if (touch.buttonPressed(5, 5, 80, 30)) {
 			     Serial.println("Botão Menu Pressionado!");
			    }
			
			    // Lógica de Área (Ideal para controles de jogos)
			    if (touch.isAreaPressed(0, 120, 120, 120)) {
			      Serial.println("Lado Esquerdo da Tela");
			    }
			  }
			}
			
# 📐 Lógica de Coordenadas
A biblioteca utiliza o sistema de coordenadas padrão do display após a rotação. No modo paisagem (Rotation 1):

			X: 0 a 320

			Y: 0 a 240

# 📝 Licença
Este projeto está sob a licença LGPL-3.0. Veja o arquivo LICENSE para mais detalhes.

# 👤 Autor
Desenvolvido por Annabel369. Se este projeto te ajudou, deixe uma ⭐ no GitHub!

Dica para o seu GitHub:
Para que o README fique ainda melhor, tire uma foto do seu ESP32 rodando o código com os botões desenhados e coloque na pasta do projeto. Depois, adicione o link da imagem no README usando ![Demonstração](link_da_imagem.jpg).

Deseja que eu te ajude a criar um arquivo de exemplo (examples/BasicTouch/BasicTouch.ino) para vir junto com a biblioteca?
