#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Display.h"
#include "AutoMode.h"

extern JoystickPins joystickPins;

extern int lightOnTime;
extern int lightOffTime;
extern bool refreshHomePage;
extern bool refreshRelaysPage;
extern bool refreshSettingsPage;

void setupJoystick();

void resetJoystick(int joystickY);

void handleJoystickControl();

void moveCursorUp(int joystickY);

void moveCursorDown(int joystickY);

void switchPage();

void handleJoystickClick();

void handleHomePageClick();

void handleSettingsPageClick();

void handleRelaysPageClick();

void changeLightTime(int &lightTime, int joystickY);

void toggleAutoMode();

#endif