project(ae2f_BmpCL_Test_0)

add_executable(
    ${PROJECT_NAME}
    "main.cpp"
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})