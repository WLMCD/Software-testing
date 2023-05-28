// test_main.cpp

#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
#include <cstdio>
#include <cassert>

extern void handle_temperature(float temperature, PwmOut& heater_power, DigitalOut& green_led, DigitalOut& red_led);

int main() {
    // Test Case 2.1
    // Simulate a temperature of 38 degrees Celsius
    PwmOut heater_power(PTC2);
    DigitalOut green_led(PTB3, 0);
    DigitalOut red_led(PTB2, 0);
    handle_temperature(38.0, heater_power, green_led, red_led);
    assert(heater_power.read() == 0 && green_led.read() == 0 && red_led.read() == 1);

    printf("Test Case 2.1 Passed: The heater is off and the green LED is off when the temperature is 38 degrees Celsius.\n");

    // Test Case 2.2
    // Simulate a temperature of 29 degrees Celsius
    handle_temperature(29.0, heater_power, green_led, red_led);
    assert(heater_power.read() == 1 && green_led.read() == 1 && red_led.read() == 0);

    printf("Test Case 2.2 Passed: The heater is on and the green LED is on when the temperature is 29 degrees Celsius.\n");

    // Test Case 2.3
    // Simulate a temperature of 33 degrees Celsius
    handle_temperature(33.0, heater_power, green_led, red_led);
    assert(heater_power.read() == 1 && green_led.read() == 1 && red_led.read() == 0);

    printf("Test Case 2.3 Passed: The heater is on and the green LED is on when the temperature is 33 degrees Celsius.\n");

    return 0;
}
