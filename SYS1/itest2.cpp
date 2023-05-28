#include "mbed.h"
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
#include <cstdio>

#define MESSAGE_MAX_SIZE 50

// Define constants for temperature conversion
#define ADC_MAX_VALUE 65535.0
#define ADC_VOLTAGE_REF 3.0
#define TEMP_COEFFICIENT 19.5
#define TEMP_OFFSET 400

int main()
{
    // Preamble
    board_init();
    u8g2_ClearBuffer(&oled);
    u8g2_SetFont(&oled, u8g2_font_6x12_mr);
    u8g2_SendBuffer(&oled);
    PwmOut heater_power(PTC2);
    DigitalOut green_led(PTB3, 0);
    DigitalOut red_led(PTB2, 0);

    heater_power = 1;

    // Ready a single reusable buffer for writing text to.
    char message[MESSAGE_MAX_SIZE + 1];
    message[MESSAGE_MAX_SIZE] = '\0';

    // Read analog and convert
    uint16_t analog_in_value = adc_read(0);

    // Updated conversion formula for more accurate temperature calculation
    float voltage = (analog_in_value / ADC_MAX_VALUE) * ADC_VOLTAGE_REF;
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
    snprintf(message, MESSAGE_MAX_SIZE, "Value is %-5d, temperature is %5.02f", analog_in_value, temperature);

    // Clear screen and write a message.
    u8g2_ClearBuffer(&oled);
    u8g2_DrawUTF8(&oled, 10, 10, message);
    u8g2_SendBuffer(&oled);
    
    // Also write the message over USB to the serial monitor
    printf("%s\n", message);

    return 0;
}
