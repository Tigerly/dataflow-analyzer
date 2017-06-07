/*
 * Analyzer.cpp
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#include <llvm/IR/Instruction.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/raw_ostream.h>

#include "Analyzer.hpp"
#include "llvm_util.hpp"

namespace dataflow
{
    void Analyzer::Analyze(llvm::Function& F)
    {
        llvm::errs() << "$$$ begin function " << LLVMUtil::DemangleName(F.getName().str()) << " $$$\n";

        // set type of basic blocks
        for (auto BB = F.begin(); BB != F.end(); ++BB)
        {
            llvm::TerminatorInst* TI = BB->getTerminator();
            for(unsigned int i = 0; i < TI->getNumSuccessors(); ++i)
            {
                llvm::BasicBlock* succ = TI->getSuccessor(i);
                llvm::Value* inst = &*(succ->begin());
                onBranch(inst, (i == 0 ? _cond_type::Common : _cond_type::Inhibit));
            }
        }

        // make graph
        for (auto BB = F.begin(); BB != F.end(); ++BB)
        {
//            llvm::errs() << "bblc: " << LLVMUtil::GetVarName(&*BB);
//            BB->printAsOperand(llvm::errs(), false);
//            llvm::errs() << "\n";
            for (auto II = BB->begin(); II != BB->end(); ++II)
            {
                {
                    llvm::AllocaInst* i = llvm::dyn_cast<llvm::AllocaInst>(II);
                    if(i != 0)
                    {
                        onAlloca(i);
                        continue;
                    }
                }

                {
                    llvm::LoadInst* i = llvm::dyn_cast<llvm::LoadInst>(II);
                    if(i != 0)
                    {
                        onLoad(&*i, i->getPointerOperand());
                        continue;
                    }
                }

                {
                    llvm::StoreInst* i = llvm::dyn_cast<llvm::StoreInst>(II);
                    if(i != 0)
                    {
                        onStore(i->getPointerOperand(), i->getValueOperand());
                        continue;
                    }
                }

                {
                    llvm::BinaryOperator* i = llvm::dyn_cast<llvm::BinaryOperator>(II);
                    if(i != 0)
                    {
                        onBinary(&*(BB->begin()), &*i, i->getOperand(0), i->getOperand(1));
                        continue;
                    }
                }

//                if(llvm::isa<llvm::BinaryOperator>(II))
//                {
//                    auto i = llvm::dyn_cast<llvm::BinaryOperator>(II);
//                    llvm::errs() << LLVMUtil::GetVarName(&*II)
//                            << " " << i->getNumOperands()
//                            << ": ";
//                    llvm::errs() << LLVMUtil::GetVarName(II->getOperand(0)) << " - "
//                            << LLVMUtil::GetVarName(II->getOperand(1)) << "\n";
//                }
                //llvm::errs() << LLVMUtil::GetVarDescript(&*II) << "\n";
//                if(II->getOpcode() == llvm::Instruction::Load)
//                {
//                    //auto vpVal = llvm::dyn_cast<llvm::LoadInst>(II)->getPointerOperand();
//                    //llvm::errs() << "   >> oper >> " << LLVMUtil::GetVarDescript(vpVal) << "\n";
//                }
            }
        }

        llvm::errs() << "$$$ end of function $$$\n";
    }

} /* namespace dataflow */

namespace dataflow
{
    void Analyzer::onAlloca(llvm::Value* target)
    {
        llvm::errs() << "# alloca # target: " << LLVMUtil::GetVarDescript(target)
        << "\n";
    }

    void Analyzer::onLoad(llvm::Value* target, llvm::Value* operand)
    {
        llvm::errs() << "# load   # from  : " << LLVMUtil::GetVarDescript(operand)
        << "\n"
        << "           to    : " << LLVMUtil::GetVarDescript(target)
        << "\n";
    }

    void Analyzer::onStore(llvm::Value* target, llvm::Value* operand)
    {
        llvm::errs() << "# store  # from  : " << LLVMUtil::GetVarDescript(operand)
        << "\n"
        << "           to    : " << LLVMUtil::GetVarDescript(target)
        << "\n";
    }

    void Analyzer::onBinary(llvm::Value* block, llvm::Value* target, llvm::Value* left, llvm::Value* right)
    {
        llvm::errs() << "# binary # left  : " << LLVMUtil::GetVarDescript(left)
        << "\n"
        << "           right : " << LLVMUtil::GetVarDescript(right)
        << "\n"
        << "           target: " << LLVMUtil::GetVarDescript(target)
        << "\n"
        << "           block : " << LLVMUtil::GetVarDescript(block)
        << "\n";
    }

    void Analyzer::onBranch(llvm::Value* block, _cond_type type)
    {
        blocks.push_back(__basic_block(block, type));
    }
} /* namespace dataflow */
