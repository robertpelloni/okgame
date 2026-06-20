project(GWEN)
cmake_minimum_required(VERSION 3.10)

set(USE_ALLEGRO false)

# Creates C resources file from files in given directory
function(create_resources dir output)
    # Create empty output file
    file(WRITE ${output} "")
    # Collect input files
    file(GLOB bins ${dir}/*)
    # Iterate through input files
    foreach(bin ${bins})
        # Get short filename
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        # Replace filename spaces & extension separator for C compatibility
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        # Read hex data from file
        file(READ ${bin} filedata HEX)
        # Convert hex data for C compatibility
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        # Append data to output file
        file(APPEND ${output} "const unsigned char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()

create_resources(resources resources.h)

if(USE_ALLEGRO)
set(GWEN_platform_sources src/Platforms/AllegroPlatform.cpp)
else()
if(WIN32)
set(GWEN_platform_sources src/Platforms/Windows.cpp)
else()
set(GWEN_platform_sources src/Platforms/X11.cpp)
endif()
endif()
file(GLOB GWEN_sources src/**.cpp)
file(GLOB GWEN_dialog_sources src/Controls/Dialog/**.cpp)
file(GLOB GWEN_control_sources src/Controls/**.cpp)
add_library(GWEN_static STATIC
  ${GWEN_sources}
  ${GWEN_control_sources}
  ${GWEN_dialog_sources}
  ${GWEN_platform_sources}
)
target_include_directories(GWEN_static PUBLIC include)
if(USE_ALLEGRO)
target_link_libraries(GWEN_static allegro)
else()
if(WIN32)
#target_link_libraries(GWEN_static system32)
else()
target_link_libraries(GWEN_static X11)
target_compile_definitions(GWEN_static PUBLIC GWEN_X11_PLATFORM)
endif()
endif()

add_library(GWEN_opengl STATIC
  Renderers/OpenGL/glew.c
  Renderers/OpenGL/OpenGL.cpp
  Renderers/OpenGL/DebugFont/OpenGL_DebugFont.cpp
)
target_include_directories(GWEN_opengl PUBLIC include)
if (WIN32)
target_link_libraries(GWEN_opengl opengl32)
else()
target_link_libraries(GWEN_opengl GL)
endif()

if(0)
add_library(GWEN_dx9
  Renderers/DirectX9/DirectX9.cpp)
target_include_directories(GWEN_dx9 PUBLIC include)
target_link_libraries(GWEN_dx9 d3d)

add_library(GWEN_dx10
  Renderers/DirectX10/DirectX10.cpp)
target_include_directories(GWEN_dx10 PUBLIC include)
target_link_libraries(GWEN_dx10 d3d)

add_library(GWEN_dx11
  Renderers/DirectX11/DirectX11.cpp)
target_include_directories(GWEN_dx11 PUBLIC include)
target_link_libraries(GWEN_dx11 d3d)
endif()

# Samples
#add_executable(GWEN_cross_platform_sample Samples/CrossPlatform/CrossPlatform.cpp)
#target_include_directories(GWEN_cross_platform_sample PUBLIC include)
#target_link_libraries(GWEN_cross_platform_sample GWEN_opengl GWEN_static GWEN_unit_test)

# Samples
#add_executable(GWEN_application_sample Samples/Application/Application.cpp)
#target_include_directories(GWEN_application_sample PUBLIC include)
#target_link_libraries(GWEN_application_sample GWEN_opengl GWEN_static GWEN_unit_test)


function(my_export_target _target _include_dir)
    file(
        WRITE "${CMAKE_CURRENT_BINARY_DIR}/${_target}Config.cmake"
        "
            include(\"\$\{CMAKE_CURRENT_LIST_DIR\}/${_target}Targets.cmake\")
            set_property(
                TARGET ${_target}
                APPEND PROPERTY
                    INTERFACE_INCLUDE_DIRECTORIES \"${_include_dir}\"
            )
        "
    )

    export(TARGETS ${_target} GWEN_static FILE "${CMAKE_CURRENT_BINARY_DIR}/${_target}Targets.cmake")
    export(PACKAGE ${_target})
endfunction(my_export_target)

my_export_target(GWEN_opengl "${CMAKE_CURRENT_SOURCE_DIR}")
