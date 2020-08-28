if(IDF_VERSION_MAJOR GREATER_EQUAL 4)
    string(APPEND CMAKE_C_FLAGS " -DRUUVI_ESP")
    idf_component_register(
        SRCS
            src/drv/terminal.c
            src/lib/api.c
            src/lib/parser.c
        INCLUDE_DIRS
            src
            src/drv
	    src/lib
        INCLUDE_DIRS
            ../../main/includes
            ../ruuvi.boards.c
            src/ruuvi.endpoints.c/src
        )
else()
    set(COMPONENT_SRCDIRS src)
    set(COMPONENT_ADD_INCLUDEDIRS src)
    register_component()
endif()
