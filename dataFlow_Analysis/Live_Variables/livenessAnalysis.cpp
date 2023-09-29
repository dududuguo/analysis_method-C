#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <cctype> // for std::isspace
#include <algorithm>
#include <stack>
#include "../../include/MyIRReader.hpp"

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
    auto module = MyIR::readFile();
    if (!module)
    {
        return 1;
    }

    for (auto &F : *module)
    {
        if (!F.isDeclaration())
        {
            livenessAnalysis(F);
        }
    }

    return 0;
}
