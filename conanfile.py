from conans import ConanFile


class DeepProject(ConanFile):
    name = "deep"
    version = "0.1.0"
    requires = (
        "docopt.cpp/0.6.2",
        "glfw/3.3.6",
        "glad/0.1.34",
        "stb/cci.20210713"
    )
    generators = "cmake", "gcc", "txt", "cmake_find_package"

    def configure(self):
        self.options['glad'].shared = False
        # self.options['glad'].fPIC = True
        self.options['glad'].no_loader = False
        self.options['glad'].spec = 'gl'
        self.options['glad'].gl_profile = 'core'
        self.options['glad'].gl_version = '4.6'