/*
 * AnalyzeToDot.h
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#ifndef DUMPGRAPH_HPP_
#define DUMPGRAPH_HPP_

#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include "Analyzer.hpp"

namespace dataflow
{
    
    class AnalyzeToDot : public Analyzer, public llvm::ModulePass
    {
    public:
        AnalyzeToDot() : llvm::ModulePass(ID){};
        static char ID;
        bool runOnModule(llvm::Module& M);
    };

    class AnalyzeToPNet : public Analyzer, public llvm::ModulePass
    {
    public:
        AnalyzeToPNet() : llvm::ModulePass(ID){};
        static char ID;
        bool runOnModule(llvm::Module& M);
    };

} /* namespace dataflow */

#endif /* DUMPGRAPH_HPP_ */
