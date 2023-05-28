#include "temperature_conversion.h"

float voltage_to_temperature(float voltage) {
    const float ADC_MAX_VALUE = 65535.0;
    const float ADC_VOLTAGE_REF = 3.0;
    const float TEMP_COEFFICIENT = 19.5;
    const float TEMP_OFFSET = 400;

    return (voltage * 1000 - TEMP_OFFSET) / TEMP_COEFFICIENT;
}