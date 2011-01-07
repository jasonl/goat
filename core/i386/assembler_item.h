#ifndef __ASSEMBLER_ITEM_H
#define __ASSEMBLER_ITEM_H

#include <string>
#include <iostream>
#include "asm_label.h"

class AssemblerItem {
  friend class AssemblyBlock;
  friend class AssemblerItemIterator;
 public:
  AssemblerItem() { label = NULL; }
  void SetLabel( std::string _label) { label = new AsmLabel(_label); }
  void SetComment( std::string _comment) { comment = _comment; }
  friend std::ostream& operator<<( std::ostream&, const AssemblerItem& );
  virtual void Print( std::ostream& ) const = 0;
  ~AssemblerItem() { if(label) delete label; }
 private:
  AsmLabel *label;
  AssemblerItem *next;
  std::string comment;
};

class AssemblerItemIterator {
  AssemblerItem *p;
public:
  AssemblerItemIterator( AssemblerItem* start) : p(start) {}
  AssemblerItemIterator( const AssemblerItemIterator& asti ) : p(asti.p) {}
  AssemblerItemIterator operator++() {p = p->next; return *this;}
  AssemblerItemIterator operator++(int) { p = p->next; return *this;}
  bool operator==( const AssemblerItemIterator& asti ) { return asti.p == p; }
  bool operator!=( const AssemblerItemIterator& asti ) { return asti.p != p; }
  AssemblerItem& operator*() { return *p; }
  AssemblerItem* operator->() { return p; }
};

#endif
