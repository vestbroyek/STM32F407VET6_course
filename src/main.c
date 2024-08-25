#include "main.h"
#include <stdint.h>

void delay(volatile uint32_t count);

int main(void)
{
  // Create pointers for main addresses
  uint32_t* p_clk_ctrl_reg = (uint32_t*) 0x40023830;
  uint32_t* p_output_mode_reg = (uint32_t*) 0x40020000;
  uint32_t* p_output_data_reg = (uint32_t*) 0x40020014;

  // Enable clock by setting 0th bit at 0x40023830 to high
  *p_clk_ctrl_reg |= (1 << 0); // GPIOAEN = 1

  // Configure mode of 6th and 7th IO pins as output
  // 1. First clear it with bitwise AND
  *p_output_mode_reg &= ~((0b11 << 12) | (0b11 << 14)); // Clear bits 12-15
  // Then set 12th-13th and 14th-15th bits to 01
  *p_output_mode_reg |= ((0b01 << 12) | (0b01 << 14)); // Set bits 12-13 and 14-15 to 01

  while (1) {
    // Finally set the 6th and 7th bit of the output data register to high
    *p_output_data_reg |= (1 << 6) | (1 << 7); // Set bits 6 and 7 to high
    delay(1000000);
    *p_output_data_reg &= ~((1 << 6) | (1 << 7)); // Turn LEDs off
    delay(1000000);
  };

}

void delay(volatile uint32_t count) {
    while (count--) {
        // Just wasting cycles
    }
}