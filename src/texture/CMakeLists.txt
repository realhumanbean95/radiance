# Executable program configuration
add_executable(texture texture.cpp)

#target_include_directories(texture PRIVATE include/)

target_link_libraries(
	texture 
	PRIVATE 
		project_options
		stb::stb
		radiance::window
		radiance::shader
		radiance::drawable
)