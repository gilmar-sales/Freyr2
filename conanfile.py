from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout


class FreyrConan(ConanFile):
    name = "freyr"
    version = "0.8"

    # Optional metadata
    license = "MIT"
    author = "Gilmar Custodio gilmar_custodio_@hotmail.com"
    url = "https://github.com/gilmar-sales/freyr"
    description = "Compile-Time and Header-Only Entity Component System"
    topics = ("ecs", "gamedev", "entity", "component", "system")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*"

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["freyr"]
