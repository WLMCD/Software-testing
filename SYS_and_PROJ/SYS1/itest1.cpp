#include "mbed.h"
#include "adc.h"
#include <cstdint>
#include <cstdio>

#define ADC_MAX_VALUE 65535.0
#define ADC_VOLTAGE_REF 3.0
#define TEMP_COEFFICIENT 19.5
#define TEMP_OFFSET 400
int main() {
    // Read sensor value
    uint16_t analog_in_value = adc_read(0);
    
    // Convert to voltage and then to temperature
    float voltage = (analog_in_value / ADC_MAX_VALUE) * ADC_VOLTAGE_REF;
    float temperature = (voltage * 1000 - TEMP_OFFSET) / TEMP_COEFFICIENT;

    // Print results for validation
    printf("Read sensor value: %d\n", analog_in_value);
    printf("Converted voltage: %f\n", voltage);
    printf("Converted temperature: %f\n", temperature);

    return 0;
}
