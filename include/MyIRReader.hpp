#ifndef MY_IR_READER_H
#define MY_IR_READER_H

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <memory>
#include <set>
#include <map>

namespace MyIR
{
    struct LivenessInfo
    {
        std::set<llvm::Value *> gen;
        std::set<llvm::Value *> kill;
        std::set<llvm::Value *> in;
        std::set<llvm::Value *> out;
    };
    using LivenessMap = std::map<llvm::BasicBlock *, LivenessInfo>;

    std::unique_ptr<llvm::Module, std::default_delete<llvm::Module>> readFile();
    void computeGenKill(llvm::Function &F, LivenessMap &livenessMap);
    bool computeLiveness(llvm::Function &F, LivenessMap &livenessMap);

}

#endif // MY_IR_READER_H
