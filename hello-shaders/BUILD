load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-shaders",
    srcs = ["hello-shaders.cpp", "shader.hpp"],
    deps = [
        "//third_party/libglfw",
        "//third_party/glad",
    ]
)