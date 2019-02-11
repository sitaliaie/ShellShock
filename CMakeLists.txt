CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/testing.cpp
    src/connector.cpp
    src/command.cpp
    src/and.cpp
    src/or.cpp
    src/semicolon.cpp
    src/exit.cpp
)

ADD_EXECUTABLE(test
    tests/test.cpp
    src/testing.cpp
    src/connector.cpp
    src/command.cpp
    src/and.cpp
    src/or.cpp
    src/semicolon.cpp
    src/exit.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
