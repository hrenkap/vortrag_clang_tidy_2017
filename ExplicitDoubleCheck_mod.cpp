//===--- ExplicitDoubleCheck.cpp - clang-tidy------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ExplicitDoubleCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Lex/Lexer.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void ExplicitDoubleCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(floatLiteral().bind("floatLit"), this);
}

void ExplicitDoubleCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedFloat = Result.Nodes.getNodeAs<FloatingLiteral>("floatLit");

  // ignore non double literals
  if (MatchedFloat->getType()->isSpecificBuiltinType(clang::BuiltinType::Double) == false) {
    diag(MatchedFloat->getLocation(), " found non-double float literal");
    return;
  }
  
  SourceLocation EndLoc = Lexer::getLocForEndOfToken( MatchedFloat->getLocEnd(),
						      0, *Result.SourceManager,
						      getLangOpts());

  diag(EndLoc, " found double literal")
    << FixItHint::CreateInsertion(MatchedFloat->getLocation(),"static_cast<double>(")
    << FixItHint::CreateInsertion(EndLoc, ")");
}

} // namespace misc
} // namespace tidy
} // namespace clang
