#include "goat.h"
#include "ast_node.h"

ASTNode::ASTNode()
{
	firstChild = NULL;
	parent = NULL;
	nextSibling = NULL;
	prevSibling = NULL;
}

ASTNode::~ASTNode() {
  ASTNode *childNode = NULL, *tempNode = NULL;

  childNode = firstChild;

  while (childNode != NULL) {
    tempNode = childNode->nextSibling;
    delete childNode;
    childNode = tempNode;
  }
}

void ASTNode::Analyse( Scope* _scope) {
  ASTIterator end(NULL);
  scope = _scope;

  for( ASTIterator i = ChildNodes(); i != end; i++)
    i->Analyse(_scope);
}

AssemblyBlock* ASTNode::GetAuxiliaryCode() {
  ASTIterator end(NULL);
  AssemblyBlock *a = new AssemblyBlock;

  for( ASTIterator i = ChildNodes(); i != end; i++) {
    a->AppendBlock( i->GetAuxiliaryCode() );
  }

  return a;
}

void ASTNode::AppendChild( ASTNode *child ) {
  ASTNode *lastSibling = this->firstChild;
  ASTNode *lastChildNode = child;

  if(!child) return;

  while(lastChildNode) {
	  lastChildNode->parent = this;
	  lastChildNode = lastChildNode->nextSibling;
  }

  if( !this->firstChild ) {
    firstChild = child;
    return;
  }

  // Find the last existing child node
  while( lastSibling ) {
    if( lastSibling->nextSibling ) {
      lastSibling = lastSibling->nextSibling;
    } else {
      break;
    }
  }

  lastSibling->nextSibling = child;
  child->prevSibling = lastSibling;
  return;
}

// Insert a new AST-Node as the first child, rather than
// the last one.
void ASTNode::InsertFirstChild( ASTNode *child ) {
  ASTNode *secondChild;

  if (!child) return;

  child->parent = this;

  if( !firstChild) {
    firstChild = child;
    return;
  }

  secondChild = firstChild;
  firstChild = child;
  secondChild->prevSibling = child;
  child->nextSibling = secondChild;
  return;
}

// Replaces a child node with a new one
void ASTNode::ReplaceChild( ASTNode *childToReplace, ASTNode *newChild ) {
  ASTNode *currentChild = firstChild;
  if( childToReplace == NULL || newChild == NULL ) return;

  // Ensure that the childToReplace exists as a child node.
  while( currentChild ) {
    if( currentChild == childToReplace ) break;
    currentChild = currentChild->nextSibling;
  }

  // We may have got to here with currentChild == NULL
  if( currentChild ) {
    newChild->parent = this;

    if( currentChild->prevSibling) {
      currentChild->prevSibling->nextSibling = newChild;
      newChild->prevSibling = currentChild->prevSibling;
    }

    if( currentChild->nextSibling ) {
      currentChild->nextSibling->prevSibling = newChild;
      newChild->nextSibling = currentChild->nextSibling;
    }

    // Modify the first node pointer if we're replacing that.
    if( firstChild == currentChild ) {
      firstChild = newChild;
    }
  }

  return;
}

void ASTNode::DetachChild( ASTNode *childNode )
{
	ASTNode *currentChild = firstChild, *prevChild = NULL;

	while (currentChild) {
		if (currentChild == childNode) {
			if (prevChild)
				prevChild->nextSibling = currentChild->nextSibling;

			if (currentChild->parent->firstChild == currentChild)
				currentChild->parent->firstChild = currentChild->nextSibling;

			if (currentChild->nextSibling)
				currentChild->nextSibling->prevSibling = prevChild;

			currentChild->nextSibling = NULL;
			currentChild->prevSibling = NULL;
			currentChild->parent = NULL;

			return;
		}

		prevChild = currentChild;
		currentChild = currentChild->nextSibling;
	}

}

ASTNode *ASTNode::MoveNodeTo( ASTNode *newParent ) {
  ASTNode *nextNode = nextSibling;
  parent->DetachChild(this);
  newParent->AppendChild(this);
  return nextNode;
}

ASTIterator ASTNode::ChildNodes() {
  return ASTIterator(firstChild);
}


ASTNode *ASTNode::MutableFindEnclosingNode(const std::string &typeToFind)
{
	if (typeid(*this).name() == typeToFind)
		return this;
	if (parent == NULL)
		return NULL;
	return parent->MutableFindEnclosingNode(typeToFind);
}

const ASTNode *ASTNode::FindEnclosingNode(const std::string &typeToFind) const
{
	if (typeid(*this).name() == typeToFind)
		return this;
	if (parent == NULL)
		return NULL;
	return parent->FindEnclosingNode(typeToFind);
}


std::ostream& operator<<(std::ostream &stream, const ASTNode &node)
{
	stream << node.Print() << std::flush;

	return stream;
}

// Recursive function to print a tree of the AST
void ASTNode::print(int depth, int skip, char *prev_cols) {
  ASTIterator end(NULL);

  std::cout << *this;
  std::cout << "\n";

  for( ASTIterator i = ChildNodes(); i != end; i++) {

    for(int j=0; j < (depth); j++) {
      std::cout << ( prev_cols[j] ? "\u2502" : " ");
    }

    if (i->nextSibling == NULL) {
      std::cout << "\u2514";
      prev_cols[depth] = 0;
      i->print(depth+1, skip+1, prev_cols);
    } else {
      std::cout << "\u251c";
      prev_cols[depth] = 1;
      i->print(depth+1, skip, prev_cols);
    }
  }
}
