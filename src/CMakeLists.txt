add_library(comp_flags INTERFACE)


set(gcc_like "$<C_COMPILER_ID:ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_c "$<C_COMPILER_ID:MSVC>")

add_executable (${PROJECT_NAME} CHIP-8.c instructions.c main.c  )

target_compile_features(comp_flags INTERFACE c_std_11)

target_compile_options(comp_flags INTERFACE
    "$<${gcc_like}:$<BUILD_INTERFACE:-Wall;-Wextra>>"
    "$<${msvc_c}:$<BUILD_INTERFACE:-W4;-WX>>")

target_link_libraries(${PROJECT_NAME} raylib comp_flags)

if(MSVC)
    target_link_libraries(${PROJECT_NAME} gdi32.lib winmm.lib)
endif()
