# analysis_method
Just For learning

## Usage

### Pre-requirements

```bash
LLVM 14.0.0
clang 14.0.0
C++17
```

### Build

#### using LLVM to analysis

```bash
cmake .
make
```

#### Example

```bash
cd test
clang -emit-llvm -S -c test.cpp   // generate .ll files
cd ../dataFlow_Analysis
cd available_expression
./available_expression 
```
