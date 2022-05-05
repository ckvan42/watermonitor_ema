include(cmake/ArduinoBase.cmake)

if(WIN32)
	set(EXE_SUFFIX ".exe")
else()
	set(EXE_SUFFIX "")
endif()

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(GNU_BASE arm-none-eabi-)

set(CMAKE_C_COMPILER ${GNU_BASE}gcc${EXE_SUFFIX})
set(CMAKE_CXX_COMPILER ${GNU_BASE}g++${EXE_SUFFIX})

set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")
