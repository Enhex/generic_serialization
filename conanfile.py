from conans import ConanFile, tools
import os


class GenericserializationConan(ConanFile):
    name = "generic_serialization"
    version = "master"
    license = "MIT"
    url = "https://github.com/Enhex/generic_serialization"
    description = "Lightweight and extensible generic serialization library"
    # No settings/options are necessary, this is header only

    def source(self):
        self.run("git clone https://github.com/Enhex/generic_serialization.git")

    def package(self):
        self.copy("*.h", "include", src="generic_serialization/include")
