make clean
make MCU=atmega8 LIBFILE=asuro
avr-size --mcu=atmega8 -C tg13-4-robotic-project.elf
pause

