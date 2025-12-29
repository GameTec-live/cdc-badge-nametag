#ifndef SETTINGS_H
#define SETTINGS_H

bool settings_init();
int get_setting_brightness();
void set_setting_brightness(int brightness);
void settings_format();
void settings_clear();

#endif // SETTINGS_H