#ifndef ZCC_COMPILE_H
#define ZCC_COMPILE_H

#include "zcc_errors.h"

class ZCCCompiler
{
public:
	ZCCCompiler(ZCC_AST &tree, DObject *outer, PSymbolTable &symbols);
	int Compile();

private:
	void CompileConstants();
	PSymbolConst *CompileConstant(ZCC_ConstantDef *def);

	TArray<ZCC_ConstantDef *> Constants;
	TArray<ZCC_Struct *> Structs;
	TArray<ZCC_Class *> Classes;
	TMap<FName, ZCC_TreeNode *> NamedNodes;

	bool AddNamedNode(FName name, ZCC_TreeNode *node);

	ZCC_Expression *Simplify(ZCC_Expression *root);
	ZCC_Expression *SimplifyUnary(ZCC_ExprUnary *unary);
	ZCC_Expression *SimplifyBinary(ZCC_ExprBinary *binary);
	ZCC_OpProto *PromoteUnary(EZCCExprType op, ZCC_Expression *&expr);
	ZCC_OpProto *PromoteBinary(EZCCExprType op, ZCC_Expression *&left, ZCC_Expression *&right);

	void PromoteToInt(ZCC_Expression *&expr);
	void PromoteToUInt(ZCC_Expression *&expr);
	void PromoteToDouble(ZCC_Expression *&expr);
	void PromoteToString(ZCC_Expression *&expr);

	ZCC_Expression *ApplyConversion(ZCC_Expression *expr, const PType::Conversion **route, int routelen);
	ZCC_Expression *AddCastNode(PType *type, ZCC_Expression *expr);

	ZCC_Expression *IdentifyIdentifier(ZCC_ExprID *idnode);
	ZCC_ExprConstant *NodeFromSymbolConst(PSymbolConst *sym, ZCC_ExprID *idnode);

	void Message(ZCC_TreeNode *node, EZCCError errnum, const char *msg, ...);

	DObject *Outer;
	PSymbolTable &Symbols;
	ZCC_AST &AST;
	int ErrorCount;
	int WarnCount;
};

void ZCC_InitConversions();

#endif
