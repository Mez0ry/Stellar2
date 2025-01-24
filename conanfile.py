import os, shutil
from conan import ConanFile
from conan.tools.cmake.cmake import CMake
from conan.tools.cmake import CMakeToolchain
from conan.tools.build import check_max_cppstd, check_min_cppstd, default_cppstd
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy, save, load

class StellarLibrary(ConanFile):
    name = "StellarLibrary"
    version = "1.0"
    settings = "os", "compiler", "arch", "build_type"
    generators = "AutotoolsDeps","VirtualRunEnv", "VirtualBuildEnv","CMakeDeps", "CMakeToolchain"

    def validate(self):
        default_cppstd(self,any,"-std=c++17")

    def requirements(self):
        self.requires("spdlog/1.15.0")
        self.requires("sdl/2.30.9", override=True)
        self.requires("sdl_image/2.8.2")
        self.requires("sdl_ttf/2.22.0")
        self.requires("sdl_mixer/2.8.0")
        self.requires("fmt/11.0.2")
        
    def build_requirements(self):
        self.tool_requires("cmake/3.31.3")
        
    def package_info(self):
        self.cpp_info.cxxflags = ["-std=c++17"]
        self.cpp_info.builddirs = ["pkg/cmake"]
        self.cpp_info.set_property("cmake_find_mode", "none")
    
    def package(self):
        copy(self, "*.so", self.build_folder, os.path.join(self.package_folder, "lib"))
        copy(self, "*.a", self.build_folder, os.path.join(self.package_folder, "lib"))
        copy(self, "*.dll", self.build_folder, os.path.join(self.package_folder, "lib"))
        copy(self, "*.lib", self.build_folder, os.path.join(self.package_folder, "lib"))

    def layout(self):
        cmake_layout(self)
        self.folders.source = "src"
        build_type = str(self.settings.build_type).lower()
        self.folders.build = "build".format(build_type)
        self.folders.generators = os.path.join(self.folders.build, "conan_gens")

    def source(self):
        self.source_folder = "build"