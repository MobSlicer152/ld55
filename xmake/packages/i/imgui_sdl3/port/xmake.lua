add_rules("mode.debug", "mode.release")
add_rules("utils.install.cmake_importfiles")
set_languages("cxx14")

option("sdl3",             {showmenu = true,  default = true})
option("sdl3_renderer",    {showmenu = true,  default = true})
option("freetype",         {showmenu = true,  default = true})
option("user_config",      {showmenu = true,  default = nil, type = "string"})

if has_config("sdl3_renderer") then
    add_requires("libsdl >=2.0.17")
elseif has_config("sdl3") then
    add_requires("libsdl")
end

if has_config("freetype") then
    add_requires("freetype")
end

target("imgui")
    set_kind("$(kind)")
    add_files("*.cpp", "misc/cpp/*.cpp")
    add_headerfiles("*.h", "(misc/cpp/*.h)")
    add_includedirs(".", "misc/cpp")

    if has_config("sdl3_renderer") then
        if os.exists("backends/imgui_impl_sdlrenderer2.cpp") then
            add_files("backends/imgui_impl_sdlrenderer2.cpp")
            add_headerfiles("(backends/imgui_impl_sdlrenderer2.h)")
        else
            add_files("backends/imgui_impl_sdlrenderer.cpp")
            add_headerfiles("(backends/imgui_impl_sdlrenderer.h)")
        end
        add_packages("libsdl3")
    end

    if has_config("freetype") then
        add_files("misc/freetype/imgui_freetype.cpp")
        add_headerfiles("misc/freetype/imgui_freetype.h")
        add_packages("freetype")
        add_defines("IMGUI_ENABLE_FREETYPE")
    end

    if has_config("user_config") then
        local user_config = get_config("user_config")
        add_defines("IMGUI_USER_CONFIG=\"".. user_config .."\"")
    end

    after_install(function (target)
        local config_file = path.join(target:installdir(), "include/imconfig.h")
        if has_config("freetype") then
            io.gsub(config_file, "//#define IMGUI_ENABLE_FREETYPE", "#define IMGUI_ENABLE_FREETYPE")
        end
    end)