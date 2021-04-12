# Generic test that uses conan libs

set(src 
        main.cpp 
	window_manager.cpp
    )
set(inc 
	engine.hpp
	window_manager.hpp
	error_manager.hpp
	game_config.hpp
    )
add_executable(intro ${src} ${inc})
target_link_libraries(
  intro
  PRIVATE project_options
          CONAN_PKG::fmt
          CONAN_PKG::spdlog
	  )
