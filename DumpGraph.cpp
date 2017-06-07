/*
 * AnalyzeToDot.cpp
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#include <llvm/Pass.h>
#include <fstream>
#include "DumpGraph.hpp"
#include "str_util.hpp"
#include "llvm_util.hpp"

static llvm::RegisterPass<dataflow::AnalyzeToDot> XD("dot-dataflow", "Export data-flow to .dot file");
static llvm::RegisterPass<dataflow::AnalyzeToPNet> XP("pnet-dataflow", "Export data-flow to .xml file used in PIPE 5");

namespace dataflow
{
    char AnalyzeToDot::ID = 0;
    char AnalyzeToPNet::ID = 1;
} /* namespace dataflow */

namespace dataflow
{
    bool AnalyzeToDot::runOnFunction(llvm::Function& F)
    {
        Analyze(F);

        auto filename = str_util::adler32_str(F.getName().str()) + ".dot";
        out = std::ofstream(filename);

        out << "digraph G { \n";


        for(auto&& v : vars)
        {
            std::string shape = "ellipse";
            if(v.second[0].second == -1)
            {
                shape = "box";
            }
            std::string label_raw = v.first;
            for(auto&& a : v.second)
            {
                std::string label = label_raw;
                if(a.second != -1)
                {
                    label += "_" + str_util::to_string(a.second);
                }
                out << "\"" << label << "\" "
                        << "[shape=\"" << shape << "\"]; \n";
            }
        }

//        for(auto&& v : vars)
//        {
//            for(auto i = v.second.begin(); i != v.second.end(); ++i)
//            {
//                if(i+1 != v.second.end() && i->second == (i+1)->second)
//                {
//                    out << "N" << i->first << " -> " << "N" << (i+1)->first
//                            << " [shape=\"none\" style=\"dashed\"]; \n";
//                }
//            }
//        }

        for(auto&& e : edges)
        {
            std::string shape = "";
            if(                    e.second.second == _cond_type::Common)
            {
                shape = "vee";
            }
            else if(e.second.second == _cond_type::Inhibit)
            {
                shape = "odot";
            }

            std::string left = "";
            std::string right = "";

            for(auto&& v : vars)
            {
                for(auto&& a : v.second)
                {
                    if(e.first.first == a.first)
                    {
                        left = v.first;
                        if(a.second != -1)
                         {
                            if(left.empty())
                            {
                                left = LLVMUtil::GetVarNameOrAddr(e.first.first);
                            }
                            left += "_" + str_util::to_string(a.second);
                        }
                    }
                    if(e.first.second == a.first)
                    {
                        right = v.first;
                        if(a.second != -1)
                         {
                            if(right.empty())
                            {
                                right = LLVMUtil::GetVarNameOrAddr(e.first.second);
                            }
                            right += "_" + str_util::to_string(a.second);
                        }
                    }
                }
            }

            out << "\"" << left << "\" -> \"" << right << "\""
                    << " [arrowhead=\"" << shape << "\"]; \n";
        }

        out << "}";

        return false;
    }

    bool AnalyzeToPNet::runOnFunction(llvm::Function& F)
    {
        Analyze(F);
        return false;
    }
}
