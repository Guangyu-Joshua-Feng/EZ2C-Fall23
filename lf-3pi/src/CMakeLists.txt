target_link_libraries(i2cmaster
  hardware_i2c
)
target_link_libraries(ic2slave
  hardware_i2c
  pico_i2c_slave
)