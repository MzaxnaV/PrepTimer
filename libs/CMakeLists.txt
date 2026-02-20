# ---- ImGui ----
add_library(imgui STATIC
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp

    imgui/backends/imgui_impl_win32.cpp
    imgui/backends/imgui_impl_dx11.cpp
)

target_include_directories(imgui PUBLIC
    imgui/
    imgui/backends/
)

target_link_libraries(imgui PUBLIC
    d3d11
    d3dcompiler
    dwmapi
)

# ---- ImPlot ----
add_library(implot STATIC
    implot/implot.cpp
    implot/implot_items.cpp
    implot/implot_demo.cpp
)

target_include_directories(implot PUBLIC
    implot/
)

target_link_libraries(implot PUBLIC imgui)