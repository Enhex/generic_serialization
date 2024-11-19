import os
from conan import ConanFile
from conan.tools.files import copy

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
    generators = "PremakeDeps"
    exports_sources = "src/*", "premake5.lua"

    def build(self):
        self.run("premake5 gmake2")
        self.run('make -rj$(nproc)')

    def package(self):
        copy(self, "LICENSE.txt", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        copy(self, pattern="*.h", src=os.path.join(self.source_folder, "src"), dst=os.path.join(self.package_folder, "include"))
        copy(self, pattern="*.a", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, pattern="*.so", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, pattern="*.lib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)
        copy(self, pattern="*.dll", src=self.build_folder, dst=os.path.join(self.package_folder, "bin"), keep_path=False)
        copy(self, pattern="*.dylib", src=self.build_folder, dst=os.path.join(self.package_folder, "lib"), keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["generic_serialization"]