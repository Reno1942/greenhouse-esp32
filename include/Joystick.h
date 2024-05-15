#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Display.h"

extern JoystickPins joystickPins;

extern int lightOnTime;
extern int lightOffTime;
extern bool refreshHomePage;
extern bool refreshRelaysPage;
extern bool refreshSettingsPage;

void setupJoystick();
void resetJoystick(int joystickY);
void moveCursorUp(int joystickY);
void moveCursorDown(int joystickY);
void switchPage();
void handleJoystickControl();
void handleJoystickClick();
void changeLightTime(int &lightTime, int joystickY);

#endif