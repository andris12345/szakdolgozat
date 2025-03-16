cmake_minimum_required(VERSION 3.16)
project(szakdolgozat)

set(CMAKE_CXX_STANDARD 20)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
        GIT_REPOSITORY  ${gitURL}
            GIT_TAG     ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.2)
endif ()

# Create your game executable target as usual
add_executable(szakdolgozat main.cpp)

target_include_directories(szakdolgozat PUBLIC ${SDL3_INCLUDE_DIRS})

target_compile_definitions(szakdolgozat PRIVATE SDL_MAIN_USE_CALLBACKS)


# Link to the actual SDL3 library.
target_link_libraries(szakdolgozat PRIVATE SDL3::SDL3)