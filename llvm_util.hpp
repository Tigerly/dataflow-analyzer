#ifndef _LLVM_UTILS_H
#define _LLVM_UTILS_H

#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

namespace LLVMUtil
{
    /// The implementation of LLVMTypeAsString:
    /// https://github.com/eliben/llvm-clang-samples/blob/master/src_llvm/simple_module_pass.cpp
    std::string TypeToStr(const llvm::Type* T);

    std::string InstToStr(const llvm::Instruction* I);

    /// CXXNameDemangle copied from:
    /// https://stackoverflow.com/questions/281818
    std::string DemangleName(const std::string& name);

    std::string GetVarName(llvm::Value* val);
    std::string GetVarNameOrAddr(llvm::Value* val);
    std::string GetVarDescript(llvm::Value* val);
}

#endif
