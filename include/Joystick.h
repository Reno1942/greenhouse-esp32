#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Display.h"

extern int lightOnTime;
extern int lightOffTime;

void setupJoystick();
void resetJoystick(int joystickY);
void moveCursorUp(int joystickY);
void moveCursorDown(int joystickY);
void switchPage();
void handleJoystickControl();
void handleJoystickClick();
void changeLightTime(int &lightTime, int joystickY);

#endif