add_subdirectory(sensor)
add_subdirectory(hal)
add_subdirectory(comm)
add_subdirectory(json)

set(SDT_SOURCE
        ${SDT_SENSOR_SOURCE}
        ${HAL_SOURCE}
        ${COMM_SOURCE}
        ${JSON_SOURCE}
        ${CMAKE_CURRENT_SOURCE_DIR}/watermonitor.c
        PARENT_SCOPE)

set(SDT_INCLUDE
        ${SDT_SENSOR_INCLUDE}
        ${HAL_INCLUDE}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${COMM_INCLUDE}
        ${JSON_INCLUDE}
        PARENT_SCOPE)
