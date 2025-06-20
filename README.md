# AVR Register-Level Programming – LED Blink (ATmega328P)

This repository accompanies **register-level AVR microcontroller programming**. starting with the foundational LED blinking program using the **ATmega328P** microcontroller — the heart of the Arduino Uno.

**Why Choose 8-bit AVR for Register-Level Programming?**
-
- **Simplicity**: AVR microcontrollers have fewer peripherals and simpler architecture compared to 32-bit controllers, making it easier to understand how hardware really works.

- **Fewer abstraction layers**: You get direct access to registers with minimal complexity, which helps you grasp the fundamentals of embedded systems.

**How Learning 8-bit AVR Helps You Understand 32-bit like STM32**
-
- **Core Embedded Concepts Stay the Same
Digital I/O configuration**: Setting pin directions, writing high/low — using DDRx, PORTx, etc. on AVR translates to setting MODER, ODR, IDR on STM32.

- **Bitwise operations**: You learn |=, &=, ~, and shifting, which are critical for any register-level programming.

- **Interrupts, timers, ADC, UART, SPI, I2C**: all these peripherals exist on both platforms. Once you understand them on AVR, it's easier to pick up the richer versions on STM32.
---

##  1. What is AVR?

**AVR** is an 8-bit RISC-based microcontroller architecture developed by Atmel (now owned by Microchip Technology). It’s widely used in both hobby and industrial embedded systems.

### About ATmega328P:
- **Architecture**: 8-bit RISC, Modified Harvard
- **Memory**:
  - 32 KB Flash (Program memory)
  - 2 KB SRAM (Data memory)
  - 1 KB EEPROM
- **I/O**: 23 GPIO Pins (PORTB, PORTC, PORTD)
- **Peripherals**: Timers, PWM, ADC, UART, SPI, I2C

---

## 2. Why Register-Level Programming?

Register-level programming means working directly with the hardware registers of a microcontroller — without relying on vendor libraries or high-level APIs. This approach is fundamental for building deep embedded expertise.

- **Full Hardware Control**: Directly configure and control each peripheral, pin, and register — no hidden abstraction.

- **Maximum Performance**: Code runs faster and uses less memory by skipping unnecessary layers.

- **Deep Understanding**: Learn how microcontrollers truly operate — from GPIO toggling to timer registers, interrupt vectors, and memory maps.

- **Power Optimization**: Gain precise control over power modes, clock gating, and peripheral shutdown for energy-efficient systems.

- **Industry Alignment**: Most production-grade embedded systems (automotive, industrial, medical, aerospace) are developed at register-level or with minimal abstraction.

- **Better Debugging and Portability**: Understand exact behavior of peripherals — helps in debugging, and porting code across devices or families.

- **Strong Foundation**: Once you master register-level programming, using high-level APIs (like HAL, Arduino, MBED) becomes a choice, not a crutch.

 While Arduino provides high-level APIs.

---

## 3. Why main() Instead of Arduino’s setup() / loop()?
In Arduino, you use setup() and loop() because Arduino provides a framework that runs on top of the microcontroller’s native code. It hides the underlying execution model and handles startup routines for you.

But in bare-metal embedded C programming, especially at the register level, you’re directly writing code that runs on the microcontroller without any abstraction layer. That’s where main() comes in.

```c
int main(void) {
  // Initialization
  while (1) {
    // Infinite loop
  }
}
```
---
## 4. LED Blinking Program (Register-Level)
**Setup**
- **MCU**: ATmega328P

- **Pin**: PB5 (Digital pin 13 on Arduino Uno)

- **Circuit**: PB5 (Digital Pin 13) → On-board LED  
  *(No need for external LED or resistor on Arduino Uno)*

## ATmega168/328P-Arduino Pin Mapping
![ATmega168/328P-Arduino Pin Mapping](https://docs.arduino.cc/static/47180601da55c458736e09d26b8bfab5/d0d8c/Atmega168PinMap2.png)

![ATmega328P-Arduino Pin Mapping](https://images.prismic.io/circuito/8e3a980f0f964cc539b4cbbba2654bb660db6f52_arduino-uno-pinout-diagram.png?auto=compress,format)


## 5. Register & Bit-Level Explanation

- **Registers Involved**:

| **Register** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| **Function** &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;                                   |  
|--------------|----------------------------------------------------|  
| `DDRB` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| Data Direction Register (1 = output, 0 = input) |  
| `PORTB`  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;| Output Register (1 = HIGH, 0 = LOW)            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |  
| `PB5`       &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; | Bit 5 of Port B → connected to Digital Pin 13   &nbsp;&nbsp;&nbsp;|


![Register Diagram](assets/Screenshot_(106).png)


- **What is DDRB?**
DDRB is the Data Direction Register for Port B.
Each bit in DDRB controls the direction (input/output) of the corresponding pin on Port B. 
Bit = 1 → Output, Bit = 0 → Input



## 6. Bitwise Operation Breakdown
➤ Set PB5 as Output
DDRB |= (1 << PB5);

- **Initial**:   0b00000000    &nbsp;&nbsp; //DDRB
- **Mask**:      0b00100000    &nbsp;&nbsp; //(1<< PB5)
- **Result**:    0b00100000 → PB5 becomes OUTPUT    &nbsp;&nbsp; //Final DDRB


➤ Set PB5 HIGH (LED ON)
PORTB |= (1 << PB5);

- **Initial**:   0b00000000    &nbsp;&nbsp;//PORTB
- **Mask**:      0b00100000    &nbsp;&nbsp;//(1 << PB5)
- **Result**:    0b00100000 → PB5 HIGH    &nbsp;&nbsp;//Final PORTB



➤ Set PB5 LOW (LED OFF)
PORTB &= ~(1 << PB5);

- **Mask**:      0b00100000   &nbsp;&nbsp;//PORTB
- **Inverted**:  0b11011111   &nbsp;&nbsp;//~(1 << PB5)
- **Result**:    PORTB & 0b11011111 → PB5 cleared   &nbsp;&nbsp;//Final PORTB 


