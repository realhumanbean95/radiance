load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "glad",
    srcs = ["glad.c"],
    hdrs = ["glad.h"],
    include_prefix = "glad",
    visibility = ["//visibility:public"],
    deps = ["//third_party/khrplatform:khr"],
)