cmake_minimum_required(VERSION 3.10)
project(GameboyEmulator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

include_directories(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2_TTF_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/cartridge
  ${PROJECT_SOURCE_DIR}/cpu
  ${PROJECT_SOURCE_DIR}/lib
  ${PROJECT_SOURCE_DIR}/main
  ${PROJECT_SOURCE_DIR}/utils
  ${PROJECT_SOURCE_DIR}/video
  ${PROJECT_SOURCE_DIR}/mem
  ${PROJECT_SOURCE_DIR}/peripheral
)

######################## Source/Header files for each components ########################
file(GLOB MAIN_SOURCES "${PROJECT_SOURCE_DIR}/main/*.cpp")
file(GLOB MAIN_HEADERS "${PROJECT_SOURCE_DIR}/main/*.hpp")

file(GLOB CARTRIDGE_SOURCES "${PROJECT_SOURCE_DIR}/cartridge/*.cpp")
file(GLOB CARTRIDGE_HEADERS "${PROJECT_SOURCE_DIR}/cartridge/*.hpp")

file(GLOB CPU_SOURCES "${PROJECT_SOURCE_DIR}/cpu/*.cpp")
file(GLOB CPU_HEADERS "${PROJECT_SOURCE_DIR}/cpu/*.hpp")

file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/lib/*.cpp")
file(GLOB LIB_HEADERS "${PROJECT_SOURCE_DIR}/lib/*.hpp")

file(GLOB UTILS_SOURCES "${PROJECT_SOURCE_DIR}/utils/*.cpp")
file(GLOB UTILS_HEADERS "${PROJECT_SOURCE_DIR}/utils/*.hpp")

file(GLOB VIDEO_SOURCES "${PROJECT_SOURCE_DIR}/video/*.cpp")
file(GLOB VIDEO_HEADERS "${PROJECT_SOURCE_DIR}/video/*.hpp")

file(GLOB MEM_SOURCES "${PROJECT_SOURCE_DIR}/mem/*.cpp")
file(GLOB MEM_HEADERS "${PROJECT_SOURCE_DIR}/mem/*.hpp")

file(GLOB PERIPHERAL_SOURCES "${PROJECT_SOURCE_DIR}/peripheral/*.cpp")
file(GLOB PERIPHERAL_HEADERS "${PROJECT_SOURCE_DIR}/peripheral/*.hpp")

################################## Combine all sources ##################################
set(SOURCES
    ${MAIN_SOURCES}
    ${CARTRIDGE_SOURCES}
    ${CPU_SOURCES}
    ${LIB_SOURCES}
    ${UTILS_SOURCES}
    ${VIDEO_SOURCES}
    ${MEM_SOURCES}
    ${PERIPHERAL_SOURCES}
)

set(HEADERS
    ${MAIN_HEADERS}
    ${CARTRIDGE_HEADERS}
    ${CPU_HEADERS}
    ${LIB_HEADERS}
    ${UTILS_HEADERS}
    ${VIDEO_HEADERS}
    ${MEM_HEADERS}
    ${PERIPHERAL_HEADERS}
)

add_executable(gameboy_emulator ${SOURCES} ${HEADERS})
target_link_libraries(gameboy_emulator PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_compile_options(gameboy_emulator PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS gameboy_emulator
    RUNTIME DESTINATION bin
)

############################### Custom targets ###############################
add_custom_target(format
    COMMAND find .. -type f -name "*.cpp" -exec clang-format -i -style=file {} +
    COMMAND find .. -type f -name "*.hpp" -exec clang-format -i -style=file {} +
    COMMENT "Formatting source files..."
)

################################## Testing ###################################
enable_testing()

set(BLARGG_TEST_ROM_DIR "${CMAKE_SOURCE_DIR}/ROM/blargg_tests")
file(GLOB BLARGG_TEST_ROMS "${BLARGG_TEST_ROM_DIR}/*")

foreach(TEST_ROM ${BLARGG_TEST_ROMS})
    get_filename_component(TEST_NAME "${TEST_ROM}" NAME_WE)

    add_test(
        NAME "blargg_${TEST_NAME}"
        COMMAND gameboy_emulator
                "${TEST_ROM}"
                --headless
                --print-serial-output
                --exit-on-infinite-jr
    )

    set_tests_properties(blargg_${TEST_NAME} PROPERTIES
        PASS_REGULAR_EXPRESSION "Passed"
        FAIL_REGULAR_EXPRESSION "Failed"
    )
endforeach()
