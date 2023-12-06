add_library(i2c
  src/i2c_circular.c
)

target_include_directories(i2c PUBLIC src)

target_link_libraries(i2c
  hardware_gpio
  hardware_i2c
  hardware_pio
  pico_i2c_slave
  pico_stdlib
  pico_unique_id
  pio
)
