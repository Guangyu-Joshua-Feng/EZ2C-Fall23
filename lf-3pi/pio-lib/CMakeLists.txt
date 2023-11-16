add_library(pio
  src/led.c
)

pico_generate_pio_header(pio
  ${CMAKE_CURRENT_LIST_DIR}/hello.pio
)

target_include_directories(pio PUBLIC src)
target_link_libraries(pio
  pico_stdlib
  hardware_pio
)
