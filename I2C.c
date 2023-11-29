#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

const char *i2cDevice = "/dev/i2c-1";  // Use /dev/i2c-1 for Raspberry Pi 4
int file;

if ((file = open(i2cDevice, O_RDWR)) < 0) {
    perror("Failed to open the I2C bus");
    exit(1);
}

int addr = 0x55;  // Replace with your I2C device address
if (ioctl(file, I2C_SLAVE, addr) < 0) {
    perror("Failed to acquire bus access and/or talk to slave");
    exit(1);
}

// Example: Write data to a register
unsigned char buffer[2] = {0x01, 0xFF};
if (write(file, buffer, 2) != 2) {
    perror("Failed to write to the I2C bus");
}

// Example: Read data from a register
unsigned char data;
if (read(file, &data, 1) != 1) {
    perror("Failed to read from the I2C bus");
}

printf("Data from register: 0x%02X\n", data);

close(file);

// Compile: gcc -o i2c_example i2c_example.c
// Run: ./i2c_example
