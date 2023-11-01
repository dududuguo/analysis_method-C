#include "MyIRReader.hpp"
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Value.h>
#include <llvm/ADT/iterator_range.h>

#include <set>
#include <map>
#include <filesystem>
#include <iostream>

namespace MyIR
{
    std::unique_ptr<llvm::Module, std::default_delete<llvm::Module>> readFile()
    {   
        std::filesystem::path currentPath = std::filesystem::current_path();
        std::cout << "Current path: " << currentPath << std::endl;

        // Make it static here
        // Make sure that llvm::LLVMContext is at least as old as the llvm::Module you're using.
        static llvm::LLVMContext context; 
        llvm::SMDiagnostic error;
        auto buffer = llvm::MemoryBuffer::getFile("../../test/test.ll");

        if (!buffer) {
            llvm::errs() << "Failed to load IR file.\n";
            return nullptr;
        }
        auto module = llvm::parseIR(*buffer.get(), error, context);

        if (!module)
        {
            error.print("Error reading IR", llvm::errs());
            return nullptr;
        }
        return std::unique_ptr<llvm::Module>(module.release());
    }


    void computeGenKill(llvm::Function &F, LivenessMap &livenessMap)
    {
        for (auto &BB : F)
        {
            LivenessInfo &info = livenessMap[&BB];

            for (auto &I : BB)
            {
                if (llvm::isa<llvm::AllocaInst>(&I))
                {
                    continue; // Ignore alloca instructions for simplicity
                }

                // Use
                for (auto &op : I.operands())
                {
                    if (llvm::isa<llvm::Instruction>(op) || llvm::isa<llvm::Argument>(op))
                    {
                        if (info.kill.find(op) == info.kill.end())
                        {
                            info.gen.insert(op);
                        }
                    }
                }

                // Def
                if (!I.getType()->isVoidTy())
                {
                    info.kill.insert(&I);
                    info.gen.erase(&I);
                }
            }
        }
    }

    bool computeLiveness(llvm::Function &F, LivenessMap &livenessMap)
    {
        bool changed = false;

        for (auto &BB : F)
        {
            LivenessInfo &info = livenessMap[&BB];

            std::set<llvm::Value *> newIn;
            for (auto *predBB : llvm::predecessors(&BB))
            {
                LivenessInfo &predInfo = livenessMap[predBB];
                newIn.insert(predInfo.out.begin(), predInfo.out.end());
            }

            std::set<llvm::Value *> newOut;
            std::set_difference(newIn.begin(), newIn.end(),
                                info.kill.begin(), info.kill.end(),
                                std::inserter(newOut, newOut.end()));
            newOut.insert(info.gen.begin(), info.gen.end());

            if (newIn != info.in || newOut != info.out)
            {
                changed = true;
                info.in = std::move(newIn);
                info.out = std::move(newOut);
            }
        }
        return changed;
    }
}
