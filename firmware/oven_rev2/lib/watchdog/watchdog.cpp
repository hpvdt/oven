#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <Arduino.h>

#include "watchdog.hpp"

const uint8_t TIMEOUT = WDTO_8S; // Timeout period for watchdog timer

/**
 * \brief Configures watchdog timer for system
 * 
 * \note Timeout period is a constant set in `watchdog.cpp`, currently 500 ms.
 */
void enableWatchdog() {
    wdt_enable(TIMEOUT); // Setup the watchdog to reset every 
}

/**
 * \brief Function to reset watchdog timer
 * 
 * \note Needs to be called regularly to prevent unintentional watchdog timeouts
 */
void resetWatchdog() {
    wdt_reset();
}

/**
 * \brief Disables the watchdog timer
 * 
 * \note Useful for sections of known long code or on boot to prevent repeated restarts.
 */
void disableWatchdog() {
    wdt_disable();
}

/**
 * \brief Interrupt to execute before restarting
 * 
 */
ISR(WDT_vect) {
    delayMicroseconds(5000); // Wait a bit so instructions finish on I2C
}