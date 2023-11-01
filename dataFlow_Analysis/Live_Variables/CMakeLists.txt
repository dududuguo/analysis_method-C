# Find LLVM and Clang packages
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Include LLVM, Clang, and our own include directory

# Add LLVM and Clang definitions
# add_definitions(${LLVM_DEFINITIONS})

# Set required LLVM libraries
if(LLVM_LINK_LLVM_DYLIB)
    set(llvm_libs LLVM)
else()
    llvm_map_components_to_libnames(
            llvm_libs
            analysis
            bitwriter
            core
            instcombine
            instrumentation
            ipo
            irreader
            linker
            scalaropts
            support
            target
            transformutils
    )
endif()

# Set required Clang libraries
set(clang_libs
        clangFrontend
        clangSerialization
        clangDriver
        clangParse
        clangSema
        clangAnalysis
        clangAST
        clangBasic
        clangCodeGen
        clangEdit
        clangTooling
        clangLex
        clangASTMatchers
        clangRewrite
        clangRewriteFrontend
        clangStaticAnalyzerFrontend
        clangStaticAnalyzerCheckers
        clangStaticAnalyzerCore
)

# Collect all source files from the current directory
file(GLOB Live_Variables_FILES "*.cpp")

# Create the executable
add_executable(Live_Variables ${Live_Variables_FILES}
        ../../src/readFile.cpp)

# Link against LLVM and Clang libraries
target_link_libraries(Live_Variables PRIVATE ${llvm_libs} ${clang_libs})
