#include "frontend.h"

#include <sstream>
#include <iostream>

#include "program_context.h"
#include "error.h"
#include "parser/scanner.h"
#include "parser/parser.h"
#include "scanner.h"
#include "parser.h"

using namespace simit::internal;

// Frontend
int Frontend::parseStream(std::istream &programStream, ProgramContext *ctx,
                          std::vector<ParseError> *errors) {
  //std::cout << ScannerNew::lex(programStream);
  TokenList tokens = ScannerNew::lex(programStream);
  ParserNew().parse(tokens, ctx, errors);
  return 0;
  //Scanner scanner(&programStream);
  //Parser parser(&scanner, ctx, errors);
  //return parser.parse();
}

int Frontend::parseString(const std::string &programString, ProgramContext *ctx,
                          std::vector<ParseError> *errors) {
  std::istringstream programStream(programString);
  return parseStream(programStream, ctx, errors);
}

int Frontend::parseFile(const std::string &filename, ProgramContext *ctx,
                        std::vector<ParseError> *errors) {
  std::ifstream programStream(filename);
  if (!programStream.good()) {
    return 2;
  }
  return parseStream(programStream, ctx, errors);
}
