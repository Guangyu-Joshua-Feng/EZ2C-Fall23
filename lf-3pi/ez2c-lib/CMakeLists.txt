add_library(ez2c
  src/circular_buffer.c
  src/ez2c_common.c
  src/ez2c_master.c
  src/ez2c_slave.c
  src/rise_time.c
  src/pio_utils.c
  src/rise_time.c
  src/rise_time_noblock.c
  src/uint32_array.c
)

pico_generate_pio_header(ez2c
  ${CMAKE_CURRENT_LIST_DIR}/rise_time.pio
)

pico_generate_pio_header(ez2c
  ${CMAKE_CURRENT_LIST_DIR}/rise_time_noblock.pio
)

target_include_directories(ez2c PUBLIC src)

target_link_libraries(ez2c
  hardware_gpio
  hardware_i2c
  hardware_irq
  hardware_pio
  pico_i2c_slave
  pico_stdlib
  pico_unique_id
)
