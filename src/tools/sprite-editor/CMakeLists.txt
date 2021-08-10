# Generic test that uses conan libs

set(src 
        app.cpp 
	main.cpp
    )
set(inc 
	app.hpp
    )

find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
# set_target_properties( helloQt PROPERTIES CMAKE_AUTOMOC ON )


#add_subdirectory(../../../Lib/wxWidgets-3.1.5/ build)
add_executable(sprite-editor ${src} ${inc})
#target_include_directories(intro ${SDL2_INCLUDE_DIR})
target_link_libraries(
  sprite-editor
  PRIVATE project_options
	  Qt5::Widgets
          CONAN_PKG::fmt
          CONAN_PKG::spdlog 
	  SDL2::SDL2
	  SDL2::SDL2main
	  )
target_compile_features(sprite-editor PUBLIC cxx_nullptr cxx_lambdas)
