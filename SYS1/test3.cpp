// test_main.cpp

#include "mbed.h"
#include "temperature_conversion.h"
#include <cstdio>
#include <cassert>
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
// stub function to simulate adc_read
uint16_t adc_read(int channel) {
    static int call_count = 0;
    uint16_t adc_values[3] = {
        static_cast<uint16_t>((736.1/ADC_VOLTAGE_REF) * ADC_MAX_VALUE),
        static_cast<uint16_t>((570.8/ADC_VOLTAGE_REF) * ADC_MAX_VALUE),
        static_cast<uint16_t>((643.6/ADC_VOLTAGE_REF) * ADC_MAX_VALUE)
    };
    return adc_values[call_count++ % 3];
}

int main() {
    PwmOut heater_power(PTC2);
    DigitalOut green_led(PTB3, 0);
    DigitalOut red_led(PTB2, 0);

    // simulate the main loop
    for (int i = 0; i < 3; i++) {
        uint16_t analog_in_value = adc_read(0);
        float voltage = (analog_in_value / ADC_MAX_VALUE) * ADC_VOLTAGE_REF;
        float temperature = (voltage * 1000 - TEMP_OFFSET) / TEMP_COEFFICIENT;

        if (temperature > 35) {
            assert(heater_power == 0);
            assert(green_led == 0);
        } else if (temperature < 30) {
            assert(heater_power == 1);
            assert(red_led == 1);
        } else {
            assert(red_led == 0);
            assert(green_led == 1);
        }
    }

    printf("Test Case 3 Passed: LED and Heater State Switching works as expected.\n");

    return 0;
}
