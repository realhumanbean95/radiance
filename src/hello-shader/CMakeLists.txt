
# Program that renders a triangle
add_executable(hello-shader main.cpp)

target_include_directories(hello-shader
        PRIVATE
            private/)

target_link_libraries(
  hello-shader            # target
  PRIVATE project_options   # items...
          glfw::glfw
          glad::glad)
