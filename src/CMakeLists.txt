# Generate resources.rc with absolute paths so rc.exe finds the asset files
# regardless of build directory location.
configure_file(
    "${CMAKE_SOURCE_DIR}/resources.rc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/resources.rc"
)

add_executable(${CMAKE_PROJECT_NAME} WIN32
    main.cpp
    window.cpp
    renderer.cpp
    ui/theme.cpp
    ui/mini.cpp
    ui/session_view.cpp
    app.cpp
    timer.cpp
    session.cpp
    "${CMAKE_CURRENT_BINARY_DIR}/resources.rc"
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    imgui
    implot
)

if (MSVC)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()
