add_subdirectory(src/)
add_subdirectory(include/)

SET(SDT_SENSOR_SOURCE
        ${SENSOR_SOURCE}
        PARENT_SCOPE)

SET(SDT_SENSOR_INCLUDE
        ${SENSOR_INCLUDE}
        PARENT_SCOPE)