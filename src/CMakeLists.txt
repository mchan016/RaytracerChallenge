set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_run
    main.cpp
    Tuple.h Tuple.cpp
    RaytracerUtils.h RaytracerUtils.cpp
)

add_library(${BINARY}_lib
    main.cpp
    Tuple.h Tuple.cpp
    RaytracerUtils.h RaytracerUtils.cpp
)
