# Generic test that uses conan libs

set(src 
        main.cpp 
    	window_manager.cpp
	render_manager.cpp
	error_manager.cpp
    )
set(inc 
	engine.hpp
	window_manager.hpp
	error_manager.hpp
	input_manager.hpp
	game_config.hpp
	pixel.hpp
	canvas.hpp
	sprite.hpp
	render_manager.hpp
	input_manager_events.hpp
	scene_manager.hpp
	vector2d.hpp
	draw.hpp
    )



add_executable(intro ${src} ${inc})
#target_include_directories(intro ${SDL2_INCLUDE_DIR})
target_link_libraries(
  intro
  PRIVATE project_options
	  SDL2::SDL2
	  SDL2::SDL2main
          CONAN_PKG::fmt
          CONAN_PKG::spdlog 
	  )
