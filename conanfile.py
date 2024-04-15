from conans import ConanFile

class GenericserializationConan(ConanFile):
    name = "generic_serialization"
    version = "master"
    license = "MIT"
    url = "https://github.com/Enhex/generic_serialization"
    description = "Lightweight and extensible generic serialization library"
    homepage = "https://github.com/Enhex/generic_serialization"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    generators = "premake"
    exports = "premake5.lua"
    exports_sources = "src/*"

    def build(self):
        self.run("premake5 gmake2")
        self.run('make -rj$(nproc)')

    def package(self):
        self.copy("*.h", dst="include", src="src")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["generic_serialization"]
