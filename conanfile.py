from conans import ConanFile, tools
import os


class GenericserializationConan(ConanFile):
    name = "generic_serialization"
    version = "master"
    license = "MIT"
    url = "https://github.com/Enhex/generic_serialization"
    description = "Lightweight and extensible generic serialization library"
    homepage = "https://github.com/Enhex/generic_serialization"
    exports_sources = "include/*"

    def package(self):
        self.copy("*.h")

    def package_id(self):
        self.info.header_only()
