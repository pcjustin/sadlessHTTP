add_executable(client_test client_test.c client_socket.c)
target_link_libraries(client_test PaxHTTP)