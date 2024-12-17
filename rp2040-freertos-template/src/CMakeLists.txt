add_executable(${ProjectName}
    main.c
    led.c
    LCD.c
    ldr.c
    Rain_Sensor.c
    Thermistor.c
    Servo.c
    Temp.c
    adc_temperature.c
    ws2812.c
    light_ws2812_cortex.c
)

pico_generate_pio_header(${ProjectName} 
    ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
)

target_include_directories(${ProjectName} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)


pico_enable_stdio_uart(${ProjectName} 0)
pico_enable_stdio_usb(${ProjectName} 1)

target_link_libraries(${ProjectName} 
    pico_stdlib 
    FreeRTOS-Kernel-Heap4 
    hardware_adc
    hardware_pwm
    hardware_pio
    hardware_clocks
    )

pico_add_extra_outputs(${ProjectName})