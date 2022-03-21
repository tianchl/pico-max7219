aux_source_directory(./ SRC)

add_executable(max7219
        ${SRC}
        )

# pull in common dependencies
target_link_libraries(max7219 pico_stdlib hardware_rtc)

# create map/bin/hex file etc.
pico_add_extra_outputs(max7219)
