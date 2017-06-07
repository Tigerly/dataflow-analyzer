/*
 * AnalyzeToDot.h
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#ifndef DUMPGRAPH_HPP_
#define DUMPGRAPH_HPP_

#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include "Analyzer.hpp"

namespace dataflow
{
    
    class AnalyzeToDot : public Analyzer, public llvm::FunctionPass
    {
        std::ofstream out;
    public:
        AnalyzeToDot() : llvm::FunctionPass(ID){};
        static char ID;
        bool runOnFunction(llvm::Function& F);
    };

    class AnalyzeToPNet : public Analyzer, public llvm::FunctionPass
    {
    public:
        AnalyzeToPNet() : llvm::FunctionPass(ID){};
        static char ID;
        bool runOnFunction(llvm::Function& F);
    };

} /* namespace dataflow */

#endif /* DUMPGRAPH_HPP_ */
