add_rules("plugin.vsxmake.autoupdate")

set_project("ld55")
set_version("0.0.0", {build = "%Y%m%d%H%M"})

set_allowedmodes("debug", "release")

if is_mode("debug") then
    add_defines("GAME_DEBUG=1", "GAME_BUILD_TYPE=\"Debug\"")
    set_optimize("none")
    set_symbols("debug")
else
    add_defines("GAME_RELEASE=1", "GAME_BUILD_TYPE=\"Release\"")
    set_optimize("fastest")
    set_symbols("hidden")
end
set_strip("all")

set_languages("clatest", "cxxlatest")
set_exceptions("cxx")

if not is_plat("wasm") then
    add_defines("USE_MIMALLOC=1")
end

add_repositories("local-repo xmake")
add_requires(
    "box2d-wasm",
    "flecs",
    "libsdl3",
    "qoi",
    "rapidjson",
    "stb"
)

if not is_plat("wasm") then
    add_requires("mimalloc")
end

add_includedirs(
    "$(scriptdir)",
    path.absolute(path.join("$(buildir)", "config")),
    path.join("deps", "discord-rpc", "include")
)

target("discord")
    set_kind("static")
    add_headerfiles(path.join("deps", "discord-rpc", "include", "*.h"), path.join("deps", "discord-rpc", "src", "*.h"))
    add_files(
        path.join("deps", "discord-rpc", "src", "discord_rpc.cpp"),
        path.join("deps", "discord-rpc", "src", "rpc_connection.cpp"),
        path.join("deps", "discord-rpc", "src", "serialization.cpp")
    )

    if is_plat("gdk", "gdkx", "windows") then
        add_files(path.join("deps", "discord-rpc", "src", "*_win.cpp"))
    elseif is_plat("linux", "freebsd") then
        add_files(path.join("deps", "discord-rpc", "src", "*_linux.cpp"), path.join("deps", "discord-rpc", "src", "*_unix.cpp"))
    end

    add_packages("rapidjson")

    set_warnings("none")
target_end()

target("game")
    set_kind("binary")
    add_headerfiles(path.join("game", "**.h*"))
    add_files(path.join("game", "**.c"), path.join("game", "**.cpp"))

    set_configdir(path.join("$(buildir)", "config"))
    add_configfiles("game/config.h.in")

    add_deps("discord")
    add_packages(
        "box2d-wasm",
        "flecs",
        "libsdl3",
	"libsdl3-main",
        "mimalloc",
        "qoi",
        "stb"
    )
target_end()
