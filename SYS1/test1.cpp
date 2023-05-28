// test_main.cpp

#include "mbed.h"
#include "temperature_conversion.h"
#include <cstdio>
#include <cassert>
#include "board_freedom.h"
#include "adc.h"
#include "oled_ssd1322.h"
#include <cstdint>
// Test Case 1.1
void test_case_1_1() {
    float temperature = 38.0;
    float test_voltage = (temperature * TEMP_COEFFICIENT + TEMP_OFFSET) / 1000;
    uint16_t test_adc_value = test_voltage / ADC_VOLTAGE_REF * ADC_MAX_VALUE;
    float expected_temperature = temperature;
    float tolerance = 0.01;

    float calculated_temperature = voltage_to_temperature(test_voltage);

    assert((calculated_temperature >= (expected_temperature - tolerance)) && (calculated_temperature <= (expected_temperature + tolerance)));

    printf("Test Case 1.1 Passed: Temperature conversion works as expected for input %d.\n", test_adc_value);
}

// Test Case 1.2
void test_case_1_2() {
    float temperature = 29.0;
    float test_voltage = (temperature * TEMP_COEFFICIENT + TEMP_OFFSET) / 1000;
    uint16_t test_adc_value = test_voltage / ADC_VOLTAGE_REF * ADC_MAX_VALUE;
    float expected_temperature = temperature;
    float tolerance = 0.01;

    float calculated_temperature = voltage_to_temperature(test_voltage);

    assert((calculated_temperature >= (expected_temperature - tolerance)) && (calculated_temperature <= (expected_temperature + tolerance)));

    printf("Test Case 1.2 Passed: Temperature conversion works as expected for input %d.\n", test_adc_value);
}

// Test Case 1.3
void test_case_1_3() {
    float temperature = 33.0;
    float test_voltage = (temperature * TEMP_COEFFICIENT + TEMP_OFFSET) / 1000;
    uint16_t test_adc_value = test_voltage / ADC_VOLTAGE_REF * ADC_MAX_VALUE;
    float expected_temperature = temperature;
    float tolerance = 0.01;

    float calculated_temperature = voltage_to_temperature(test_voltage);

    assert((calculated_temperature >= (expected_temperature - tolerance)) && (calculated_temperature <= (expected_temperature + tolerance)));

    printf("Test Case 1.3 Passed: Temperature conversion works as expected for input %d.\n", test_adc_value);
}

int main() {
    test_case_1_1();
    test_case_1_2();
    test_case_1_3();
    return 0;
}
