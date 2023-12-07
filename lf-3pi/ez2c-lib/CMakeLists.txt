add_library(ez2c
  src/common.c
  src/ez2c_master.c
  src/rise_time.c
)

pico_generate_pio_header(ez2c
  ${CMAKE_CURRENT_LIST_DIR}/rise_time.pio
)

target_include_directories(ez2c PUBLIC src)

target_link_libraries(ez2c
  hardware_gpio
  hardware_i2c
  hardware_pio
  pico_i2c_slave
  pico_stdlib
  pico_unique_id
)
