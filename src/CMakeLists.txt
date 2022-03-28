
find_package(glfw3 REQUIRED)
find_package(glad REQUIRED)
find_package(stb REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(radiance)
add_subdirectory(window)
add_subdirectory(drawable)
add_subdirectory(shader)
add_subdirectory(texture)
add_subdirectory(math)