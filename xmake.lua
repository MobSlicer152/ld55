add_rules("plugin.vsxmake.autoupdate")

set_project("ld55")
set_version("0.0.0", {build = "%Y%m%d%H%M"})

set_allowedmodes("debug", "release")

if is_mode("debug") then
    add_defines("GAME_DEBUG=1")
    set_optimize("none")
    set_symbols("debug")
else
    add_defines("GAME_RELEASE=1")
    set_optimize("fastest")
    set_symbols("hidden")
end
set_strip("all")

set_languages("clatest")

add_defines("USE_MIMALLOC=1")

add_repositories("local-repo xmake")
add_requires(
    "flecs",
    "libsdl3",
    "mimalloc",
    "qoi",
    "stb"
)

add_includedirs(
    "$(scriptdir)",
    path.absolute(path.join("$(buildir)", "config")),
    path.join("deps", "nova-physics", "include")
)

target("nova-physics")
    set_kind("static")
    add_headerfiles(path.join("deps", "nova-physics", "include", "**.h"))
    add_files(path.join("deps", "nova-physics", "src", "**.c"))
target_end()

target("game")
    set_kind("binary")
    add_headerfiles(path.join("game", "**.h*"))
    add_files(path.join("game", "**.c"))

    set_configdir(path.join("$(buildir)", "config"))
    add_configfiles("game/config.h.in")

    add_deps("nova-physics")
    add_packages(
        "flecs",
        "libsdl3",
        "mimalloc",
        "qoi",
        "stb"
    )
target_end()
