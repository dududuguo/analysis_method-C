# Find LLVM and Clang packages
find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

# Add LLVM and Clang definitions
add_definitions(-DFILE_PATH="${CMAKE_SOURCE_DIR}/test/test.ll")


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
file(GLOB SRC_FILES "*.cpp")
