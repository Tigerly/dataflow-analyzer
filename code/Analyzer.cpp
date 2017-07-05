///  Analyzer.cpp

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
    void Analyzer::Analyze (llvm::Function& F)
    {
        // ............................
        for (auto BB = F.begin(); BB != F.end(); ++BB)
        {
            llvm::TerminatorInst* TI = BB->getTerminator();
            for (unsigned int i = 0; i < TI->getNumSuccessors(); ++i)
            {
                llvm::BasicBlock* succ = TI->getSuccessor (i);
                llvm::Value* inst = &* (succ->begin());
                onBranch (inst, (i == 0 ? _cond_type::Common : _cond_type::Inhibit));
            }
        }
        // ............................
        // ............................
    }
} /* namespace dataflow */

namespace dataflow
{
    void Analyzer::onAlloca (llvm::Value* target)
    {
        __var_addr addr (target, 0);
        _var_synonyms syn;
        syn.push_back (addr);
        _var_name name = LLVMUtil::GetVarName (target);
        _var v (name, syn);
        vars.push_back (v);
    }

    void Analyzer::onLoad (llvm::Value* target, llvm::Value* operand)
    {
        for (auto && v : vars)
        {
            for (auto && a : v.second)
            {
                if (a.first == operand)
                {
                    v.second.push_back (__var_addr (target, (v.second.end() - 1)->second));
                    return;
                }
            }
        }
    }

    void Analyzer::onStore (llvm::Value* target, llvm::Value* operand)
    {
        for (auto && v : vars)
        {
            for (auto && a : v.second)
            {
                if (a.first == target)
                {
                    // it is saving modification, so __timeidx increases 1
                    v.second.push_back (__var_addr (operand, (v.second.end() - 1)->second + 1));
                    if (v.first.empty())
                    {
                        v.first = LLVMUtil::GetVarName (operand);
                    }
                    return;
                }
            }
        }
    }

    char* fake_addr = 0;

    void Analyzer::onBinary (llvm::Value* block, llvm::Value* target, llvm::Value* left, llvm::Value* right)
    {
        _cond_type type = _cond_type::Common; // default is 0
        for (auto b = blocks.begin(); b != blocks.end(); ++b)
        {
            if (b->first == block)
            {
                type = b->second;
                blocks.erase (b);
                break;
            }
        }

        __var_addr addr ((llvm::Value*)fake_addr, -1);
        _var_synonyms syn;
        syn.push_back (addr);
        _var_name name = LLVMUtil::GetVarDescript (target);
        _var v (name, syn);
        vars.push_back (v);

        __edge_link lnL (left, (llvm::Value*)fake_addr);
        __edge_link lnR (right, (llvm::Value*)fake_addr);
        __edge_type et (name, type);
        _edge L (lnL, et);
        _edge R (lnR, et);

        __edge_link lnT ((llvm::Value*)fake_addr, target);
        __edge_type etT (name, _cond_type::Common);
        _edge T (lnT, etT);

        edges.push_back (L);
        edges.push_back (R);
        edges.push_back (T);

        ++fake_addr;
    }

    void Analyzer::onCall (llvm::Value* block, llvm::Value* result, std::vector<llvm::Value*> args)
    {
        _cond_type type = _cond_type::Common; // default is 0
        for (auto b = blocks.begin(); b != blocks.end(); ++b)
        {
            if (b->first == block)
            {
                type = b->second;
                blocks.erase (b);
                break;
            }
        }

        __var_addr addr ((llvm::Value*) (fake_addr++), -1);
        _var_synonyms syn;
        syn.push_back (addr);
        _var_name name = LLVMUtil::GetVarDescript (result);
        _var v (name, syn);
        vars.push_back (v);

        __edge_type inType (name, type);
        for (auto && a : args)
        {
            __edge_link ln (a, (llvm::Value*)fake_addr);
            _edge L (ln, inType);
            edges.push_back (L);
        }

        __edge_type outType (name, _cond_type::Common);
        __edge_link lnT ((llvm::Value*)fake_addr, result);
        _edge T (lnT, outType);
        edges.push_back (T);

        ++fake_addr;
    }

    void Analyzer::onBranch (llvm::Value* block, _cond_type type)
    {
        blocks.push_back (__basic_block (block, type));
    }
} /* namespace dataflow */

