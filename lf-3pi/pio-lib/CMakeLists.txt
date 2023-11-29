add_library(pio
  src/led.c
  src/rise_time.c
  src/pio_lib_utils.c
  src/intr_test.c
)

pico_generate_pio_header(pio
  ${CMAKE_CURRENT_LIST_DIR}/hello.pio
)

pico_generate_pio_header(pio
  ${CMAKE_CURRENT_LIST_DIR}/intr.pio
)

pico_generate_pio_header(pio
  ${CMAKE_CURRENT_LIST_DIR}/rise_time.pio
)

target_include_directories(pio PUBLIC src)
target_link_libraries(pio
  pico_stdlib
  hardware_gpio
  hardware_pio
)
