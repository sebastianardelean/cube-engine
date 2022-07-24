# Generic test that uses conan libs

set(src
        main.cpp
        graphics/engine.cpp
        utils/utils.cpp
        utils/logger_manager.cpp
        graphics/event_handler.cpp
        graphics/game_scene.cpp
        graphics/render_manager.cpp
        sprite.cpp
        text.cpp
        )
set(inc
        cube.hpp
        graphics/engine.hpp
        utils/utils.hpp
        utils/cube_exceptions.hpp
        utils/logger_manager.hpp
        graphics/event_handler.hpp
        graphics/game_scene.hpp
        graphics/render_manager.hpp
        sprite.hpp
        text.hpp
        )



add_executable(intro ${src} ${inc})
#target_include_directories(intro ${SDL2_INCLUDE_DIR})
target_link_libraries(
        intro
        PRIVATE project_options
        #		  SDL2::SDL2
        #		  SDL2::SDL2main
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::sdl
        CONAN_PKG::sdl_ttf
        CONAN_PKG::libffi
)
