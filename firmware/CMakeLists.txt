cmake_minimum_required(VERSION 3.16)
include(cmake/Toolchain.cmake)
project(capstone-water-monitor-comm)

option(CAPSTONE_BUILD_LORA OFF)
option(EMA_YVR_USE_PRINTF "Use printf" ON)

add_subdirectory(contrib/)
add_subdirectory(startup/)
add_subdirectory(src/)

set(CMAKE_BUILD_TYPE RELEASE)

set(SRCS
	${CONTRIB_SRCS}
	${SDT_SOURCE})
	
set(INCLUDES
	${CONTRIB_INCLUDES}
	${SDT_INCLUDE}
	${CMAKE_CURRENT_SOURCE_DIR}/startup
	${CMAKE_CURRENT_SOURCE_DIR}/Config)

add_executable(ema_yvr_comm.elf 
		${SRCS}
		${EMA_YVR_STARTUP_SRCS})

cmake_policy(SET CMP0065 NEW)

target_compile_options(ema_yvr_comm.elf PUBLIC
  -Wall 
  -g3 
  #-std=gnu99
  -Og
  -mthumb
  -mcpu=cortex-m0plus
  -mfloat-abi=soft
  -mlittle-endian
  -ffunction-sections 
  -fdata-sections
  -Werror 
  #-Wstrict-prototypes
  -Warray-bounds 
  -fno-strict-aliasing 
  -Wno-unused-const-variable 
  -specs=nano.specs 
  -specs=nosys.specs)

set_target_properties(
  ema_yvr_comm.elf
  PROPERTIES
  LINK_FLAGS
  "-T${EMA_YVR_LINK_SCRIPT} \
   -mthumb -mcpu=cortex-m0plus \
   -Wl,--gc-sections \
   -Wl,-Map=ema_yvr_comm.map")

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
if(${EMA_YVR_USE_PRINTF})
	target_compile_definitions(ema_yvr_comm.elf PUBLIC -DUSE_PRINTF)
endif()
endif()
target_compile_definitions(ema_yvr_comm.elf PUBLIC 
	__SAMD21G18A__ 
	-DBOARD_ID_arduino_zero
	-D REGION_US915
	-D SOFT_SE)

	
target_link_libraries(ema_yvr_comm.elf -lm)

target_include_directories(ema_yvr_comm.elf PUBLIC
	${MODULE_BASE}/source/CMSIS/4.5.0/CMSIS/Include
	${MODULE_BASE}/source/CMSIS-Atmel/1.2.0/CMSIS/Device/ATMEL
	${INCLUDES}
		)

find_library(ARDUINO_LIB NAMES Arduino)

add_custom_command(OUTPUT ema_yvr_comm.bin
	COMMAND ${GNU_BASE}objcopy ARGS -O binary ema_yvr_comm.elf ema_yvr_comm.bin
	DEPENDS ema_yvr_comm.elf)

add_custom_command(OUTPUT ema_yvr_comm.hex
	COMMAND ${GNU_BASE}objcopy ARGS -O ihex ema_yvr_comm.elf ema_yvr_comm.hex
	DEPENDS ema_yvr_comm.elf)

add_custom_target(extrafiles DEPENDS ema_yvr_comm.hex ema_yvr_comm.bin)

add_custom_target(flash ALL
	COMMAND openocd -d2 -f ${OPENOCD_CONFIG} -c \"init\; halt\; at91samd bootloader 0\; program {ema_yvr_comm.bin} reset\; shutdown\"
	DEPENDS extrafiles)
