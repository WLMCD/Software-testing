#include "mbed.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
#include <cstdio>
#include <cassert>
#include "board_freedom.h"
#define ADC_MAX_VALUE 65535.0
#define ADC_VOLTAGE_REF 3.0
#define TEMP_COEFFICIENT 19.5
#define TEMP_OFFSET 400

// main() runs in its own thread in the OS
int main()
{
    // Preamble
    u8g2_ClearBuffer(&oled);
    u8g2_SetFont(&oled, u8g2_font_6x12_mr);
    u8g2_SendBuffer(&oled);
    PwmOut heater_power(PTC2);
    DigitalOut green_led(PTB3, 0);
    DigitalOut red_led(PTB2, 0);

    heater_power = 1;

    // Values representing different temperature conditions
    uint16_t test_values[] = { 
        30000, // Temperature of -10°C
        35000  // Temperature of 45°C
    };

    char message[51];

    for(int i=0; i<2; i++) {
        float voltage = (test_values[i] / ADC_MAX_VALUE) * ADC_VOLTAGE_REF;
        float temperature = (voltage * 1000 - TEMP_OFFSET) / TEMP_COEFFICIENT;
        
        if (temperature > 35) {
            heater_power = 0;
            green_led = 0;
        } else if (temperature < 30) {
            heater_power = 1;
            red_led = 1;
        } else {
            red_led = 0;
            green_led = 1;
        }
        
        // Construct message
        snprintf(message, 50, "Value is %-5d, temperature is %5.02f", test_values[i], temperature);

        // Clear screen and write a message.
        u8g2_ClearBuffer(&oled);
        u8g2_DrawUTF8(&oled, 10, 10, message);
        u8g2_SendBuffer(&oled);
        
        // Also write the message over USB to the serial monitor
        printf("%s\n", message);

        // Wait a bit
        ThisThread::sleep_for(100ms);
    }

    return 0;
}
