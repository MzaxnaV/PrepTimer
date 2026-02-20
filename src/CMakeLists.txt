add_executable(${CMAKE_PROJECT_NAME} WIN32
    main.cpp
    window.cpp
    renderer.cpp
    ui/theme.cpp
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

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets
)