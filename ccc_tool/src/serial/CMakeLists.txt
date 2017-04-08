SET(FPAG_SERIAL_EXE         jikong_test_serial)
aux_source_directory(. FPAG_SERIAL_SRC_LIST)

add_executable(${FPAG_SERIAL_EXE}  ${FPAG_SERIAL_SRC_LIST})
target_link_libraries(${FPAG_SERIAL_EXE}   -ldl; -lpthread)

# ------------ install ------------
install(TARGETS ${FPAG_SERIAL_EXE} RUNTIME DESTINATION release)
#install(TARGETS ccc_server ccc_server_monitor RUNTIME DESTINATION release)
