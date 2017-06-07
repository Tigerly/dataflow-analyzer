#include <llvm/IR/Constants.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>
#include <cxxabi.h>

#include "llvm_util.hpp"

namespace LLVMUtil
{
    //TODO: introduce a template kinda thing to do this auto matically
    std::string TypeToStr(const llvm::Type* T)
    {
        std::string typeName;
        llvm::raw_string_ostream N(typeName);
        T->print(N);
        return N.str();
    }

    std::string InstToStr(const llvm::Instruction* I)
    {
        std::string instString;
        llvm::raw_string_ostream N(instString);
        I->print(N);
        return N.str();
    }

    // https://stackoverflow.com/a/4541470
    std::string DemangleName(const std::string& name)
    {
        int status = -4; // some arbitrary value to eliminate the compiler warning

        // enable c++11 by passing the flag -std=c++11 to g++
        std::unique_ptr<char, void (*)(void*)> res
        { __cxxabiv1::__cxa_demangle(name.c_str(), 0, 0, &status), std::free };

        return (status == 0) ? res.get() : name;
    }

    std::string GetVarName(llvm::Value* val)
    {
        std::string raw;
        llvm::raw_string_ostream O(raw);

        O << val->getName();
        if(O.str().empty())
        {
            if(llvm::isa<llvm::ConstantInt>(val))
            {
                O << llvm::cast<llvm::ConstantInt>(val)->getSExtValue();
            }
        }

        return O.str();
    }

    std::string GetVarNameOrAddr(llvm::Value* val)
    {
        std::string raw;
        llvm::raw_string_ostream O(raw);

        O << GetVarName(val);

        if(O.str().empty())
        {
            O << val;
        }

        return O.str();
    }

    std::string GetVarDescript(llvm::Value* val)
    {
        std::string ret = GetVarNameOrAddr(val);

        if(llvm::isa<llvm::Instruction>(val))
        {
            ret += ": ";
            ret += InstToStr(llvm::cast<llvm::Instruction>(val));
        }

        return ret;
    }
}
