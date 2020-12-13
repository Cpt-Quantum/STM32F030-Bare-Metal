# STM32F030-Bare-Metal

This repo contains an assortment of code that aims to allow full control over a STM32F030 based chip without using any libraries or code from STMicro. The registers are mapped out by hand a little differently than how they would normally be supplied by STMicro. Instead of being mapped out with #defines, I've used \_\_attribute\_\_((packed)) in GCC to allow for typed register maps. It ties you to GCC but it does result in cleaner code. 
