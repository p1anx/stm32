cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME stm32f103c8t_cmake_test)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    # BSP/*.c 
    BSP/mymain.c
    BSP/led/led.c
    BSP/usart/usart_mx.c
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    BSP 
    BSP/led
    BSP/usart
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    -u_printf_float  # For printf support in STM32
    -u_scanf_float   # For scanf support in STM32
    # -specs=nano.specs
    # -specs=nosys.specs  # For minimal system support
)

set(UPLOAD_TOOL "jlink") #options: jlink, cmsis-dap
set(SWD_JTAG_PORT "swd") #options: swd, jtag
set(TARGET_MCU "stm32f1x") #options: stm32f1x, stm32f4x, stm32f7x, stm32h7x, and so on

# Set upload command based on the selected tool
if(UPLOAD_TOOL STREQUAL "jlink")
    set(INTERFACE_CFG "interface/jlink.cfg")
elseif(UPLOAD_TOOL STREQUAL "cmsis-dap")
    set(INTERFACE_CFG "interface/cmsis-dap.cfg")
endif()

add_custom_target(flash
  COMMAND /usr/bin/openocd 
    -f ${INTERFACE_CFG}
    -c "transport select ${SWD_JTAG_PORT}"
    -f target/${TARGET_MCU}.cfg
    -c "program ${CMAKE_PROJECT_NAME}.elf verify reset exit"
  DEPENDS ${CMAKE_PROJECT_NAME}.elf  # 依赖目标文件，确保先编译
  COMMENT "Flashing ${CMAKE_PROJECT_NAME}.elf with OpenOCD"
)