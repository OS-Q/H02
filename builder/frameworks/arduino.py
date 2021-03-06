from os.path import isdir, join

from SCons.Script import DefaultEnvironment

env = DefaultEnvironment()
platform = env.PioPlatform()
board_config = env.BoardConfig()

FRAMEWORK_DIR = platform.get_package_dir("A02")
assert isdir(FRAMEWORK_DIR)

env.Append(
    CPPDEFINES=[
        "ARDUINO_ARCH_STM8",
        ("ARDUINO", 10802),
        ("double", "float"),
        "USE_STDINT",
        "__PROG_TYPES_COMPAT__"
    ],

    CPPPATH=[
        join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core")),
        join(FRAMEWORK_DIR, "STM8S_StdPeriph_Driver", "inc")
    ],

    LIBPATH=[
        join(FRAMEWORK_DIR, "STM8S_StdPeriph_Driver", "lib")
    ],

    LIBS=[board_config.get("build.mcu")[0:8].upper()],

    LIBSOURCE_DIRS=[
        join(FRAMEWORK_DIR, "libraries")
    ]
)

libs = []

if "build.variant" in env.BoardConfig():
    env.Append(
        CPPPATH=[
            join(FRAMEWORK_DIR, "variants",
                env.BoardConfig().get("build.variant"))
        ]
    )
    libs.append(env.BuildLibrary(
        join("$BUILD_DIR", "ArduinoVariant"),
        join(FRAMEWORK_DIR, "variants", env.BoardConfig().get("build.variant"))
    ))

libs.append(env.BuildLibrary(
    join("$BUILD_DIR", "Arduino"),
    join(FRAMEWORK_DIR, "cores", env.BoardConfig().get("build.core"))
))

env.Prepend(LIBS=libs)
