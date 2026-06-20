
            include("${CMAKE_CURRENT_LIST_DIR}/GWEN_openglTargets.cmake")
            set_property(
                TARGET GWEN_opengl
                APPEND PROPERTY
                    INTERFACE_INCLUDE_DIRECTORIES "C:/Users/hyper/workspace/bg/okgame/lib/GWEN-master/gwen"
            )
        