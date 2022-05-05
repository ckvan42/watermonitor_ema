set(LoRaMac_SRCS
	#c files
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic_channelshuffle.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic_compliance.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic_us_like.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic_us915.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic_util.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/lmic.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/oslmic.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic/radio.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/aes/lmic.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/aes/other.c
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/aes/ideetron/AES-128_V10.c
	
)
set (LoRaMac_INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src/lmic
	${CMAKE_CURRENT_SOURCE_DIR}/contrib/arduino-lmic/src
)

set(LORA_SRCS
	${LoRaMac_SRCS}
	${CMAKE_CURRENT_SOURCE_DIR}/lora.c
	${CMAKE_CURRENT_SOURCE_DIR}/hal/hal.c
	${CMAKE_CURRENT_SOURCE_DIR}/hal/lora_eic.c
	${CMAKE_CURRENT_SOURCE_DIR}/hal/lora_spi.c
	PARENT_SCOPE)
	
set(LORA_INCLUDES
	${LoRaMac_INCLUDES}
	${CMAKE_CURRENT_SOURCE_DIR}
	PARENT_SCOPE)
	