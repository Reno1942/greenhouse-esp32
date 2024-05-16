/**
 * @file Display.h
*/

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include "PinsDefinitions.h"
#include "Relay.h"
#include "Sensors.h"

/**
 * @struct LCDValues
 * @brief Structure to hold the values related to the LCD display.
 * 
 * This structure holds the address, number of columns, and number of rows of the LCD display.
 */
struct LCDValues
{
    const int address = 0x27; /**< The I2C address of the LCD display. */
    const byte cols = 20; /**< The number of columns of the LCD display. */
    const byte rows = 4; /**< The number of rows of the LCD display. */    
};

/**
 * @enum Page
 * @brief Enumeration for different pages of the LCD display.
 * 
 * This enumeration defines the different pages that can be displayed on the LCD display.
 */
enum Page
{
    HOME_PAGE, /**< The home page of the LCD display. */
    RELAYS_PAGE, /**< The relays page of the LCD display. */
    SETTINGS_PAGE, /**< The settings page of the LCD display. */
    PAGE_COUNT /**< The total number of pages. */
};

extern int tankLevelPercentage; /**< External declaration of the percentage of tank level. */
extern bool autoMode; /**< External declaration of the auto mode status. */
extern RelayState relayState[4]; /**< External declaration of the state of the relays. */

extern int lightOnTime; /**< External declaration of the time when the lights turn on. */
extern int lightOffTime; /**< External declaration of the time when the lights turn off. */
extern int currentCursorY; /**< External declaration of the current cursor position on the LCD display. */

extern float currentTemp; /**< External declaration of the current temperature. */
extern float currentHumidity; /**< External declaration of the current humidity. */

/**
 * @brief Initializes the LCD display.
 */
void setupLCD();

/**
 * @brief Displays the home page on the LCD display.
 */
void displayHomePage();

/**
 * @brief Displays the current temperature and humidity on the LCD display.
 */
void displayTempAndHumidity();

/**
 * @brief Displays the current time on the LCD display.
 */
void displayTime();

/**
 * @brief Displays the tank level on the LCD display.
 */
void displayTankLevel();

/**
 * @brief Displays the current mode (auto/manual) on the LCD display.
 */
void displayMode();

/**
 * @brief Displays the relays page on the LCD display.
 */
void displayRelaysPage();

/**
 * @brief Displays the settings page on the LCD display.
 */
void displaySettingsPage();

/**
 * @brief Displays the light cycle settings on the LCD display.
 */
void displayLightCycle();

/**
 * @brief Displays the day duration settings on the LCD display.
 */
void displayDayDuration();

/**
 * @brief Clears a specific row on the LCD display.
 * @param row The row number to be cleared.
 */
void clearRow(int row);

/**
 * @brief Clears the entire screen of the LCD display.
 */
void clearScreen();

/**
 * @brief Updates the cursor position on the LCD display.
 */
void updateCursor();

#endif