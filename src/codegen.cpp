#include "parser.hpp"
#include <memory>
#include <vector>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/BasicBlock.h"

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<IRBuilder<>> Builder;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<std::string, Value *> NamedValue;

Value *ExprAST::codegen() {
		return ConstantFP::get(*TheContext, APFloat(Val));
}

Function *FunctionAST::codegen() {
		/* this creates a vector which represents the type of the arguments
		   the size of the vector equates to the number of arguments */
		std::vector<Type*> Doubles(0, Type::getDoubleTy(*TheContext));
		
		/*this defines the return tpye of the function right now i can maybe just 
		hardcode it to be integer type*/
		FunctionType *FT = 
				FunctionType::get(
						Type::getInt64Ty(*TheContext),
						Doubles,
						false
				);
		Function *F = Function::Create(FT, Function::ExternalLinkage, "main", TheModule.get());

		BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", F);
		Builder->SetInsertPoint(BB);
		Builder->CreateRet(ConstantInt::get(Type::getInt32Ty(*TheContext), 0));

		return F;
}

static void InitializeModule() {
		TheContext = std::make_unique<LLVMContext>();
		TheModule = std::make_unique<>
}




