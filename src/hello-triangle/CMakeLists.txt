# Program that renders a triangle
add_executable(hello-triangle hello-triangle.cpp)

target_link_libraries(
  hello-triangle            # target
  PRIVATE project_options   # items...
          glfw::glfw
          glad::glad)
