# Executable program configuration
add_executable(hello-drawable hello-drawable.cpp)

target_include_directories(hello-drawable PRIVATE include/)

target_link_libraries(
	hello-drawable 
	PRIVATE 
		project_options 
		glfw::glfw 
		glad::glad
		radiance::shader
		radiance::drawable
)