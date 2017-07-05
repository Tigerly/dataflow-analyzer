/// Analyzer.hpp


#ifndef ANALYZER_HPP_
#define ANALYZER_HPP_

#include <llvm/IR/Type.h>
#include <llvm/IR/Instruction.h>

#include <string>
#include <utility>
#include <vector>
#include <list>

namespace dataflow
{

    class Analyzer
    {
    protected:
        // Increase as soon as there is a `store' instruction
        // use -1 to treat as a transform
        typedef int __timeidx;

        typedef std::pair<llvm::Value*, __timeidx> __var_addr;
        typedef std::vector<__var_addr> _var_synonyms;
        typedef std::string _var_name;
        typedef std::pair<_var_name, _var_synonyms> _var;
        typedef std::vector<_var> _var_array;

        enum _cond_type : unsigned char { Common, Inhibit };

        typedef std::pair<llvm::Value*, llvm::Value*> __edge_link;
        typedef std::string _edge_name;
        typedef std::pair<_edge_name, _cond_type> __edge_type;
        typedef std::pair<__edge_link, __edge_type> _edge;
        typedef std::vector<_edge> _edge_array;

        typedef std::pair<llvm::Value*, _cond_type> __basic_block;
        typedef std::list<__basic_block> _basic_block_array;

    protected:
        _var_array vars;
        _edge_array edges;
        _basic_block_array blocks;

    private:
        void onAlloca (llvm::Value* target);
        void onLoad (llvm::Value* target, llvm::Value* operand);
        void onStore (llvm::Value* target, llvm::Value* operand);
        void onBinary (llvm::Value* block, llvm::Value* target, llvm::Value* left, llvm::Value* right);
        void onBranch (llvm::Value* block, _cond_type type);
        void onCall (llvm::Value* block, llvm::Value* result, std::vector<llvm::Value*> args);

    protected:
        void Analyze (llvm::Function& F);
    };

} /* namespace dataflow */

#endif /* ANALYZER_HPP_ */
