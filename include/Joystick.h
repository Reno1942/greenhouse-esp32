/**
 * @file Joystick.h
 * @brief This file contains the declaration of functions related to joystick control.
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "PinsDefinitions.h"
#include "Display.h"
#include "AutoMode.h"

extern JoystickPins joystickPins; /**< External declaration of joystick pins. */

extern int lightOnTime; /**< External declaration of light on time. */
extern int lightOffTime; /**< External declaration of light off time. */
extern bool refreshHomePage; /**< External declaration of flag to refresh home page. */
extern bool refreshRelaysPage; /**< External declaration of flag to refresh relays page. */
extern bool refreshSettingsPage; /**< External declaration of flag to refresh settings page. */

/**
 * @brief Initializes the joystick.
 */
void setupJoystick();

/**
 * @brief Resets the joystick position.
 * @param joystickY The current position of the joystick in the Y-axis.
 */
void resetJoystick(int joystickY);

/**
 * @brief Handles the joystick control.
 */
void handleJoystickControl();

/**
 * @brief Moves the cursor up based on the joystick position.
 * @param joystickY The current position of the joystick in the Y-axis.
 */
void moveCursorUp(int joystickY);

/**
 * @brief Moves the cursor down based on the joystick position.
 * @param joystickY The current position of the joystick in the Y-axis.
 */
void moveCursorDown(int joystickY);

/**
 * @brief Switches to the next page.
 */
void switchPage();

/**
 * @brief Handles the click event of the joystick.
 */
void handleJoystickClick();

/**
 * @brief Handles the click event on the home page.
 */
void handleHomePageClick();

/**
 * @brief Handles the click event on the settings page.
 */
void handleSettingsPageClick();

/**
 * @brief Handles the click event on the relays page.
 */
void handleRelaysPageClick();

/**
 * @brief Changes the light time based on the joystick position.
 * @param lightTime The current light time.
 * @param joystickY The current position of the joystick in the Y-axis.
 */
void changeLightTime(int &lightTime, int joystickY);

/**
 * @brief Toggles the auto mode.
 */
void toggleAutoMode();

#endif