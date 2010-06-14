#ifndef __ASSEMBLY_LEXER_HPP
#define __ASSEMBLY_LEXER_HPP

class AssemblyLexer : public Lexer {
public:
  AssemblyLexer( int _baseIndent, char *_st, char *_end, SourceFile *_sf ):
    Lexer( _st, _end, _sf), baseIndent( _baseIndent ) {
  }
  void Lex();
  void SetCurrentLine( int _currLine ) { currentLine = _currLine; }
  int GetCurrentLine() { return currentLine; }
  char *GetCurrentPosition() { return sourceNext; }
  int GetIndent() { return indent; };
  void AssemblyStateTransitions( CodePoint& );
private:
  int baseIndent;
};

#endif
