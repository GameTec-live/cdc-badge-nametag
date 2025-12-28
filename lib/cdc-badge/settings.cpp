#include "badge.h"
#include "i2c_bus.h"
#include <Preferences.h>
#include <nvs_flash.h>

Preferences settings;

void settings_clear() {
    Serial.println("settings_clear()");
    settings.begin("badge", false);
    settings.clear();
    settings.end();
}

void settings_format() {
    Serial.println("settings_format()");
    nvs_flash_erase(); // erase the NVS partition and...
    nvs_flash_init();  // initialize the NVS partition.
}

bool settings_init() {
    bool success = true;
    Serial.println("settings_init()");
    settings.begin("badge", false);
    settings.end();

    return success;
}

int get_setting_brightness() {
    settings.begin("badge", true);
    int brightness = settings.getInt("brightness", 5);
    settings.end();
    return brightness;
}
void set_setting_brightness(int brightness) {
    settings.begin("badge", false);
    settings.putInt("brightness", brightness);
    settings.end();
}