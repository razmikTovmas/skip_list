add_executable(Basic Basic.cxx)
target_link_libraries(Basic PRIVATE skip_list::skip_list)

add_executable(SLExample SLExample.cxx)
target_link_libraries(SLExample PRIVATE skip_list::skip_list)
