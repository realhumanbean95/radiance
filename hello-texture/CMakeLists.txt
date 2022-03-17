
# Program that renders a triangle
add_executable(hello-texture hello-texture.cpp)

target_include_directories(hello-texture
        PRIVATE
            private/)

target_link_libraries(
  hello-texture            # target
  PRIVATE project_options   # items...
          glfw::glfw
          glad::glad)
