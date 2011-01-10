#!/usr/bin/env ruby
#
# Assembly generator - generates the AssemblyBlock class with methods
# for all instructions in the instruction set.

ins_h = ARGV[0]
assembly_c = ARGV[1] #|| "assembly_block.c"
assembly_h = ARGV[2] #|| "assembly_block.h"

# Memoized cache so we don't generate duplicate methods
method_cache = {}

a_c = File.open( assembly_c, "w")
a_h = File.open( assembly_h, "w")

a_h.write '#ifndef __ASSEMBLY_BLOCK_H'
a_h.write "\n"
a_h.write '#define __ASSEMBLY_BLOCK_H'
a_h.write "\n"

a_h.write "\#include \"operand.h\"\n"
a_h.write "\#include \"assembler_item.h\"\n"
a_h.write "\#include \"instruction.h\"\n"
a_h.write "\#include \"segment_declaration.h\"\n"
a_c.write "\#include \"assembly_block.h\"\n\n"

a_h.write "class AssemblyBlock \{\n"
a_h.write "public:\n"

File.open( ins_h, "r" ).each_line do |l|
  next unless l[0..0] == '{'

  l.gsub!(/NO_OPERANDS/i, "{NOT_USED, NOT_USED, NOT_USED}")

  # Find the instruction name and operands
  /^\{"([A-Z][A-Z0-9_]*)", *\{([A-Z][A-Z_0-9]*), *([A-Z][A-Z_0-9]*), *([A-Z][A-Z_0-9]*)/i.match(l)        
  operand_name = $~[1]
  op1 = $~[2]
  op2 = $~[3]
  op3 = $~[4]

  num_operands = (op1 != "NOT_USED" ? 1 : 0) +
                 (op2 != "NOT_USED" ? 1 : 0) +
                 (op3 != "NOT_USED" ? 1 : 0)

  next if method_cache[[operand_name, num_operands]]
  method_cache[[operand_name, num_operands]] = true
  # Write the prototype
  a_h.write "  void "
  a_h.write operand_name + "("
  a_h.write " " unless num_operands == 0
  num_operands.times do |n|
    a_h.write "Operand&"
    a_h.write ", " unless n+1 == num_operands
  end
  a_h.write " " unless num_operands == 0
  a_h.write ");\n"

  # Write the method body
  a_c.write "void AssemblyBlock::"
  a_c.write operand_name + "("
  a_c.write " " unless num_operands == 0
  num_operands.times do |n|
    a_c.write "Operand &op" + (n+1).to_s
    a_c.write ", " unless n+1 == num_operands
  end
  a_c.write " " unless num_operands == 0
  a_c.write ") \{\n"
  a_c.write "  AppendInstruction( new Instruction(\""
  a_c.write operand_name
  a_c.write "\""
  a_c.write ", " unless num_operands == 0
  num_operands.times do |n|
    a_c.write "&op" + (n+1).to_s
    a_c.write ", " unless n+1 == num_operands
  end
  a_c.write ") );\n"
  a_c.write "\}\n\n"
end

a_h.write <<-PROTOTYPES
  AssemblyBlock();
  void AppendBlock( AssemblyBlock* );
  void AppendItem( AssemblerItem* );
  void AppendInstruction( Instruction* );
  AssemblerItemIterator Instructions() { return AssemblerItemIterator( first ); }
  void LabelFirstInstruction( std::string );
  void LabelLastInstruction( std::string );
  void CommentLastInstruction( std::string );
  void AddHangingLabel( std::string );
  void SetSegment( std::string );
 private:
  AssemblerItem *first;
  AssemblerItem *last;
PROTOTYPES

a_c.write <<-DEFINITIONS
AssemblyBlock::AssemblyBlock() {
  first = NULL;
  last = NULL;
}

void AssemblyBlock::AppendBlock( AssemblyBlock *ab ) {
  if( ab == NULL || ab->first == NULL || ab->last == NULL ) return; 

  if( last ) {
    last->next = ab->first;
    last = ab->last;
  } else {
    first = ab->first;
    last = ab->last;
  }

  delete ab;
}

void AssemblyBlock::AppendInstruction( Instruction *i ) {
  AppendItem(i);
}

void AssemblyBlock::AppendItem( AssemblerItem *i ) {  
  if(first == NULL ) {
    first = i;
  } else {
    last->next = i;
  }
  last = i;
}

void AssemblyBlock::LabelFirstInstruction( std::string _label ) {
  if( first ) {
    first->SetLabel( _label );
  }
}

void AssemblyBlock::LabelLastInstruction( std::string _label ) {
  if( last ) {
    last->SetLabel( _label );
  }
}

void AssemblyBlock::CommentLastInstruction( std::string _comment ) {
  if( last ) {
    last->SetComment( _comment );
  }
}

void AssemblyBlock::AddHangingLabel( std::string _label ) {
  // TODO: Add support for genuinely empty instructions, and remove the NOP
  NOP();
  last->SetLabel( _label );
}

void AssemblyBlock::SetSegment( std::string _segment ) {
  AppendItem( new SegmentDeclaration(_segment) );
}  

DEFINITIONS

a_h.write "};\n"
a_h.write '#endif'

a_h.close
a_c.close
