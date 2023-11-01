# Collect all source files from the current directory
file(GLOB available_expr_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.o")

# Create the executable
add_executable(available_expression ${available_expr_FILES})
