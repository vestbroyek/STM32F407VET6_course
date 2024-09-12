#include "main.h"
#include <stdint.h>

void delay(volatile uint32_t count);

int main(void)
{
  // Create pointers for main addresses
  RCC_AHB1ENR_t volatile *const p_clk_ctrl_reg = (RCC_AHB1ENR_t*) 0x40023830;
  GPIOx_MODE_t volatile *const p_output_mode_reg = (GPIOx_MODE_t*) 0x40020000;
  GPIOx_ODR_t volatile *const p_output_data_reg = (GPIOx_ODR_t*) 0x40020014;

  // Enable clock by setting 0th bit at 0x40023830 to high
  p_clk_ctrl_reg->gpioa_en = 1; // GPIOAEN = 1

  // Configure mode of 6th and 7th IO pins as output
  p_output_mode_reg->pin_6 = 1;
  p_output_mode_reg->pin_7 = 1;

  while (1) {
    // Finally set the 6th and 7th bit of the output data register to high
    p_output_data_reg->pin_6 = 1;
    delay(1000000);
    p_output_data_reg->pin_6 = 0;
    delay(1000000);
    p_output_data_reg->pin_7 = 1;
    delay(1000000);
    p_output_data_reg->pin_7 = 0;
    delay(1000000);
  };

}

void delay(volatile uint32_t count) {
    while (count--) {
        // Just wasting cycles
    }
}