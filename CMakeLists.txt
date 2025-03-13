cmake_minimum_required(VERSION 3.30)
project(szakdolgozat)

set(CMAKE_CXX_STANDARD 20)

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


add_executable(szakdolgozat main.cpp)

target_include_directories(szakdolgozat PUBLIC ${SDL3_INCLUDE_DIRS})

target_compile_definitions(szakdolgozat PRIVATE SDL_MAIN_USE_CALLBACKS)

target_link_libraries(szakdolgozat PRIVATE SDL3::SDL3)


