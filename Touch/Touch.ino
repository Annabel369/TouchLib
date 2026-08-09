#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <lvgl.h>

// --- PINOS DO TOUCH (Cheap Yellow Display) ---
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// --- FUNÇÃO DO TOUCH PARA O LVGL ---
void touchscreen_read(lv_indev_t * indev, lv_indev_data_t * data) {
  if(touchscreen.tirqTouched() && touchscreen.touched()) {
    TS_Point p = touchscreen.getPoint();
    
    // Mapeia coordenadas cruas para os pixels da tela
    int x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    int y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);

    data->state = LV_INDEV_STATE_PRESSED;
    data->point.x = x;
    data->point.y = y;
  }
  else {
    data->state = LV_INDEV_STATE_RELEASED;
  }
}

// --- VARIÁVEIS DAS TELAS ---
lv_obj_t * tela_1;
lv_obj_t * tela_2;

// Evento: Botão clicado -> Vai para Tela 2
static void ir_para_tela2_event_cb(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_screen_load(tela_2); 
    }
}

// Evento: Botão clicado -> Vai para Tela 1
static void ir_para_tela1_event_cb(lv_event_t * e) {
    if(lv_event_get_code(e) == LV_EVENT_CLICKED) {
        lv_screen_load(tela_1); 
    }
}

void criar_telas(void) {
    // ======== TELA 1 ========
    tela_1 = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(tela_1, lv_color_hex(0x000000), 0); 

    lv_obj_t * label1 = lv_label_create(tela_1);
    lv_label_set_text(label1, "TELA PRINCIPAL");
    lv_obj_set_style_text_color(label1, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(label1, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * btn_ir_tela2 = lv_button_create(tela_1);
    lv_obj_set_size(btn_ir_tela2, 200, 50);
    lv_obj_align(btn_ir_tela2, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(btn_ir_tela2, ir_para_tela2_event_cb, LV_EVENT_CLICKED, NULL); 
    
    lv_obj_t * label_btn1 = lv_label_create(btn_ir_tela2);
    lv_label_set_text(label_btn1, "Ir para Tela 2");
    lv_obj_center(label_btn1);

    // ======== TELA 2 ========
    tela_2 = lv_obj_create(NULL); 
    lv_obj_set_style_bg_color(tela_2, lv_color_hex(0x005500), 0); 

    lv_obj_t * label2 = lv_label_create(tela_2);
    lv_label_set_text(label2, "TELA SECUNDARIA");
    lv_obj_set_style_text_color(label2, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(label2, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t * btn_voltar = lv_button_create(tela_2);
    lv_obj_set_size(btn_voltar, 200, 50);
    lv_obj_align(btn_voltar, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(btn_voltar, lv_color_hex(0xFF0000), 0); 
    lv_obj_add_event_cb(btn_voltar, ir_para_tela1_event_cb, LV_EVENT_CLICKED, NULL); 
    
    lv_obj_t * label_btn2 = lv_label_create(btn_voltar);
    lv_label_set_text(label_btn2, "Voltar p/ Tela 1");
    lv_obj_center(label_btn2);

    // Inicia mostrando a Tela 1
    lv_screen_load(tela_1);
}

void setup() {
  Serial.begin(115200);
  
  // 1. Inicia o LVGL
  lv_init();

  // 2. Inicia o SPI e o Touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  touchscreen.setRotation(2); // Ajuste se o toque ficar invertido (0, 1, 2 ou 3)

  // 3. Inicia o Display no LVGL
  lv_display_t * disp = lv_tft_espi_create(SCREEN_WIDTH, SCREEN_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0); // Rotação 0 corrige a tela espelhada e o posicionamento
    
  // 4. Configura e registra o Touch no LVGL
  lv_indev_t * indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchscreen_read);

  // 5. Cria nossa interface visual
  criar_telas();
}

void loop() {
  lv_task_handler();  // LVGL processa os toques e desenha
  lv_tick_inc(5);     // Avisa o LVGL que passaram 5ms
  delay(5);           
}