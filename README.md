# STM32F030-Bare-Metal

This repo contains two distinct sets of example code, with each set giving an example of an LED being blinked by a timer interrupt set to 1 second. The difference between each set is in how the peripheral registers are defined:
  - ST_device_headers
  This code uses device headers as supplied by STMicro, these headers use macros to define the registers and their respective bit offsets
  - custom_device_headers
  This code uses device headers that are written by me, these headers use \_\_attribute\_\_((packed)) structs to define the registers and their internal bits. This ties you to using GCC but has the benefit of not requiring bit shifts as well as resulting in far more readable code.

This repo aims to serve as a comparison between each method of describing the peripheral registers.
