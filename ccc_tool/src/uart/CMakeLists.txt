add_executable(jikong_test_uart  jikong_test_uart.c)
#target_link_libraries(ccc_server   -ldl; -lpthread)

#ADD_EXECUTABLE(ccc_server_monitor ccc_monitor.c)

# ------------ install ------------
install(TARGETS jikong_test_uart RUNTIME DESTINATION release)
#install(TARGETS ccc_server ccc_server_monitor RUNTIME DESTINATION release)
