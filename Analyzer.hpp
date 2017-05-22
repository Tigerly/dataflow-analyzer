/*
 * Analyzer.h
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#ifndef ANALYZER_HPP_
#define ANALYZER_HPP_

#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

namespace dataflow
{
    
    class Analyzer
    {
    protected:
        void Analyze(llvm::Module& M);
    };

} /* namespace dataflow */

#endif /* ANALYZER_HPP_ */
