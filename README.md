# STM32F103 Bare-Metal Temperature and Humidity Monitoring

## Overview

This project implements a bare-metal temperature and humidity monitoring system using the STM32F103C8T6 microcontroller. It interfaces with an SHT11 sensor for data acquisition and displays the results on an HD44780-compatible 16×2 LCD.

The implementation is based entirely on CMSIS, with direct register-level control and no dependency on vendor HAL libraries.

---

## Features

- Bare-metal firmware using CMSIS (no HAL)
- SHT11 temperature and humidity sensor driver
- HD44780 16×2 LCD driver
- Support for 4-bit and 8-bit LCD interface modes
- Precise timing using SysTick (microsecond and millisecond delays)
- Low-level GPIO control for full hardware transparency

---

## Hardware Requirements

- STM32F103C8T6 (Blue Pill or equivalent)
- SHT11 temperature and humidity sensor
- 16×2 LCD (HD44780-compatible)
- Basic supporting components (resistors, wiring, power supply)

---

## Project Status

This project is currently under active development.  
The first release version **v0.1.0** is in progress.