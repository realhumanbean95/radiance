# Executable program configuration
add_executable(radiance radiance.cpp)

target_include_directories(radiance PRIVATE include/)

target_link_libraries(
	radiance 
	PRIVATE 
		project_options 
		glfw::glfw 
		glad::glad
		radiance::shader
		radiance::drawable
)