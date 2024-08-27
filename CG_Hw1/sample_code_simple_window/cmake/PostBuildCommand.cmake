function(copy_file FROM)
    set(TO ${ARGV1})

    add_custom_command(
        TARGET
            ${${PROJECT_NAME}_EXECUTABLE_NAME}
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_if_different
            ${FROM}
            $<TARGET_FILE_DIR:${${PROJECT_NAME}_EXECUTABLE_NAME}>${TO}
    )
endfunction()

function(copy_directory_content FROM)
    set(TO ${ARGV1})

    add_custom_command(
        TARGET
            ${${PROJECT_NAME}_EXECUTABLE_NAME}
        POST_BUILD
        COMMAND
            ${CMAKE_COMMAND} -E copy_directory
            ${FROM}
            $<TARGET_FILE_DIR:${${PROJECT_NAME}_EXECUTABLE_NAME}>${TO}
    )
endfunction()

if (WIN32)
    copy_file(${glfw3_DIR}/../../../bin/glfw3.dll)
endif()
