#ifndef MY_IR_READER_H
#define MY_IR_READER_H

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
