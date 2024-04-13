package("imgui_sdl3")
    set_homepage("https://github.com/ocornut/imgui")
    set_description("Bloat-free Immediate Mode Graphical User interface for C++ with minimal dependencies")
    set_license("MIT")

    add_urls("https://github.com/ocornut/imgui/archive/refs/tags/$(version).tar.gz",
             "https://github.com/ocornut/imgui.git")

    add_versions("v1.90.4-docking", "v1.90.4-docking")

    add_configs("sdl3_renderer",    {description = "Enable the sdl3 renderer backend", default = true, type = "boolean"})
    add_configs("user_config",      {description = "Use user config (disables test!)", default = nil, type = "string"})
    add_configs("freetype",         {description = "Use FreeType to build and rasterize the font atlas", default = true, type = "boolean"})

    add_includedirs("include", "include/imgui", "include/backends", "include/misc/cpp")

    if is_plat("windows", "mingw") then
        add_syslinks("imm32")
    end

    on_load("macosx", "linux", "windows", "mingw", "android", "iphoneos", function (package)
        if package:config("sdl3_renderer") then
            package:add("deps", "libsdl3")
        end
        if package:config("freetype") then
            package:add("deps", "freetype")
        end
        if package:version_str():find("-docking", 1, true) then
            package:set("urls", {"https://github.com/ocornut/imgui.git"})
        end
    end)

    on_install("macosx", "linux", "windows", "mingw", "android", "iphoneos", function (package)
        local configs = {
            sdl3_renderer    = package:config("sdl3_renderer"),
        }

        os.cp(path.join(package:scriptdir(), "port", "xmake.lua"), "xmake.lua")
        import("package.tools.xmake").install(package, configs)
    end)

    on_test(function (package)
        if package:config("user_config") ~= nil then return end
        local includes = {"imgui.h"}
        local defines
        if package:config("sdl3_renderer") or package:config("sdl3_no_renderer") then
            table.insert(includes, "SDL.h")
        end
        assert(package:check_cxxsnippets({test = [[
            void test() {
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                ImGui::NewFrame();
                ImGui::Text("Hello, world!");
                ImGui::ShowDemoWindow(NULL);
                ImGui::Render();
                ImGui::DestroyContext();
            }
        ]]}, {configs = {languages = "c++14", defines = defines}, includes = includes}))
    end)