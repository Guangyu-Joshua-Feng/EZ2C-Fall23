#include "ez2c_slave.h"

#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <pico/i2c_slave.h>
#include <pico/stdlib.h>
#include <pico/unique_id.h>

#include "ez2c_common.h"

static uint led_pin;

static struct {
    uint8_t mem[256];
    uint8_t mem_address;
} context;

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event);
static void process_command();

uint ez2c_slave_init(i2c_inst_t *i2c, uint baudrate, uint sda_pin, uint scl_pin,
                     uint _led_pin, bool internal_pullup) {
    led_pin = _led_pin;
    gpio_init(sda_pin);
    gpio_init(scl_pin);
    gpio_init(led_pin);
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_set_dir(led_pin, GPIO_OUT);

    if (internal_pullup) {
        gpio_pull_up(sda_pin);
        gpio_pull_up(scl_pin);
    } else {
        gpio_disable_pulls(sda_pin);
        gpio_disable_pulls(scl_pin);
    }

    uint actual_baudrate = i2c_init(i2c, baudrate);
    i2c_slave_init(i2c, I2C_DEFAULT_SLAVE_ADDR, &i2c_slave_handler);

    return actual_baudrate;
}

static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    static bool slave_signal = false;
    static bool recvd = false;
    switch (event) {
        case I2C_SLAVE_RECEIVE:  // master has written some data
            // save into memory
            recvd = true;
            context.mem[context.mem_address] = i2c_read_byte_raw(i2c);
            context.mem_address++;
            slave_signal = !slave_signal;
            gpio_put(led_pin, !slave_signal);
            break;

        case I2C_SLAVE_REQUEST:  // master is requesting data
            // load from memory
            i2c_write_byte_raw(i2c, context.mem[context.mem_address]);
            context.mem_address++;
            break;

        case I2C_SLAVE_FINISH:  // master has signalled Stop / Restart
            context.mem_address = 0;
            if (recvd) {
                recvd = false;
                process_command();
            }
            break;

        default:
            break;
    }
}

static void process_command() {
    if (context.mem[0] == COMMAND_DISCOVER) {
        // get id ready for master to read
        pico_get_unique_board_id(context.mem);
    } else if (context.mem[0] == COMMAND_ASSIGN) {
        pico_unique_board_id_t my_id;
        pico_get_unique_board_id(&my_id);
        // if id doesn't match, ignore and terminate procedure.
        if (memcmp(&my_id, context.mem + 1, sizeof(my_id)) != 0) return;

        // reassign my address
        uint8_t addr = context.mem[1 + sizeof(my_id)];
        i2c_slave_init(i2c0, addr, &i2c_slave_handler);
    } else if (context.mem[0] == COMMAND_ECHO) {
        // move data to the beginning of mem for master to read
        memmove(context.mem, context.mem + 1, strlen(context.mem + 1));
    }
}
