/*
 * AnalyzeToDot.cpp
 *
 *  Created on: May 22, 2017
 *      Author: aya
 */

#include "DumpGraph.hpp"

static llvm::RegisterPass<dataflow::AnalyzeToDot> XD("dot-dataflow", "Export data-flow to .dot file");
static llvm::RegisterPass<dataflow::AnalyzeToPNet> XP("pnet-dataflow", "Export data-flow to .xml file used in PIPE 5");

namespace dataflow
{
    char AnalyzeToDot::ID = 0;
    char AnalyzeToPNet::ID = 1;
} /* namespace dataflow */

