# Executable program configuration
add_executable(radiance radiance.cpp)

target_include_directories(radiance PRIVATE include/)

target_link_libraries(
	radiance 
	PRIVATE 
		project_options 
		radiance::window
		radiance::shader
		radiance::drawable
		radiance::texture
		radiance::math
)