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

    // Values representing different temperature conditions
    uint16_t test_values[] = { 
        30000, // Temperature of 38°C
        20000, // Temperature of 29°C
        25000  // Temperature of 33°C
    };

    char message[51];

    for(int i=0; i<3; i++) {
        float voltage = (test_values[i] / ADC_MAX_VALUE) * ADC_VOLTAGE_REF;
        float temperature = (voltage * 1000 - TEMP_OFFSET) / TEMP_COEFFICIENT;
        
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
