#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype> // for std::isspace
#include <algorithm>
#include <stack>
#include "MyIRReader.hpp"

void livenessAnalysis(llvm::Function &F)
{
    MyIR::LivenessMap livenessMap;
    MyIR::computeGenKill(F, livenessMap);

    bool changed;
    do
    {
        changed = MyIR::computeLiveness(F, livenessMap);
    } while (changed);

    // Print results (optional)
    for (auto &[BB, info] : livenessMap)
    {
        llvm::errs() << "BasicBlock: " << BB->getName() << "\n";
    }
}

int main()
{
    std::cout << "Before reading file" << std::endl;
    auto module = MyIR::readFile();
    std::cout << "After reading file" << std::endl;

    if (module)
    {
        std::cout << "Before iterating through functions" << std::endl;
        for (auto &F : *module)
        {
            std::cout << "Function: " << F.getName().str() << std::endl;
            if (!F.isDeclaration())
            {
                std::cout << "Before liveness analysis of function: " << F.getName().str() << std::endl;
                livenessAnalysis(F);
                std::cout << "After liveness analysis of function: " << F.getName().str() << std::endl;
            }
        }
        std::cout << "After iterating through functions" << std::endl;
    }
    return 0;
}