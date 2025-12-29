#include "app.h"
#include "badge.h"
#include "display.h"
#include "settings.h"
#include <Arduino.h>

int calculate_brightness_step(int current_brightness) { // Kinda logarithmic brightness
    if (current_brightness < 10)
        return 1;
    if (current_brightness < 50)
        return 5;
    if (current_brightness < 150)
        return 15;
    if (current_brightness < 400)
        return 30;
    if (current_brightness < 700)
        return 50;
    return 80;
}

void app_setup(app_state_t *state) { state->is_initialized = true; }

void app_loop(app_state_t *state) {

    char pressed = pin_expander_process_irq();
    if (pressed != 'x') {
        Serial.print("Button pressed: ");
        Serial.println(pressed);
        switch (pressed) {
        case '1': {
            Serial.println("Brightness +");
            int current_brightness = get_setting_brightness();
            int step = calculate_brightness_step(current_brightness);
            int new_brightness = current_brightness + step;
            if (new_brightness >= 1023) {
                new_brightness = 1023;
                Serial.println("already at maximum brightness");
            }
            set_setting_brightness(new_brightness);
            display_show();
            brightness_osd(new_brightness);
            break;
        }
        case '2': {
            Serial.println("Brightness -");
            int current_brightness = get_setting_brightness();
            int step = calculate_brightness_step(current_brightness);
            int new_brightness = current_brightness - step;
            if (new_brightness <= 0) {
                new_brightness = 0;
                Serial.println("already at minimum brightness");
            }
            set_setting_brightness(new_brightness);
            display_show();
            brightness_osd(new_brightness);
            break;
        }

        default:
            break;
        }
    }

    // Switch battery OFF if FLASH button is pressed
    powerdown_process_irq();

    // Once we have some menu, we can update it here
    // update_menu();
}