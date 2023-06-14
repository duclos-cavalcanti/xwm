function (find_xephyr)
    execute_process(COMMAND whereis Xephyr 
                    OUTPUT_QUIET
                    RESULT_VARIABLE RUNCODE)

    if (${RUNCODE} EQUAL 0)
        set(XEPHYR_FOUND 1 PARENT_SCOPE)
        message(STATUS "Xephyr executable found")
    else()
        set(XEPHYR_FOUND 0 PARENT_SCOPE)
    endif()
endfunction()

