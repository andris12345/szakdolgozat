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

# SDL_ttf
find_package(SDL3_ttf QUIET)
if (NOT SDL3_ttf_FOUND)
    set(SDLTTF_VENDORED ON CACHE BOOL "" FORCE)
    set(SDLTTF_HARFBUZZ OFF CACHE BOOL "" FORCE)
    set(SDLTTF_FREETYPE TRUE CACHE BOOL "" FORCE)

    include_dependency(SDL_ttf https://github.com/libsdl-org/SDL_ttf.git release-3.2.2)
endif ()

# Create your game executable target as usual
add_executable(szakdolgozat main.cpp
        source/gui/gomb/Gomb.cpp
        source/unit/create/CreateMan.cpp
        source/variables/Variables.h
        source/gui/gomb/Gomb.h
        source/unit/create/CreateMan.h
        source/variables/Variables.cpp
        source/unit/move/MoveMan.h
        source/unit/move/MoveMan.cpp
        source/unit/fighter/Fighter.cpp
        source/unit/fighter/Fighter.h
        source/unit/ranged/Ranged.cpp
        source/unit/ranged/Ranged.h
        source/unit/tank/Tank.cpp
        source/unit/tank/Tank.h
        source/unit/gameUnit/GameUnit.cpp
        source/unit/gameUnit/GameUnit.h
        source/gui/felirat/Felirat.cpp
        source/gui/felirat/Felirat.h
        source/variables/AiVariables.cpp
        source/variables/AiVariables.h
        source/ai/easy/easyAi.cpp
        source/ai/easy/easyAi.h
        source/ai/medium/mediumAi.cpp
        source/ai/medium/mediumAi.h
        source/ai/hard/hardAi.cpp
        source/ai/hard/hardAi.h
        source/unit/attack/Attack.cpp
        source/unit/attack/Attack.h
        source/tower/tower.cpp
        source/tower/tower.h
        source/tower/TowerAttack.cpp
        source/tower/TowerAttack.h)

target_include_directories(szakdolgozat PUBLIC ${SDL3_INCLUDE_DIRS})

target_compile_definitions(szakdolgozat PRIVATE SDL_MAIN_USE_CALLBACKS)


# Link to the actual SDL3 library.
target_link_libraries(szakdolgozat PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)
