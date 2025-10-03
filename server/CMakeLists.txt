set(SERVER_SOURCES
    main.cpp
    server.cpp
    server.h
)
add_executable(server ${SERVER_SOURCES})

target_link_libraries(server
    Qt5::Core
    Qt5::Network
)
