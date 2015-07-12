/*  lexer.cpp  */

/*  ----------- 

 EOF_TOKEN: It states the end of file
 NUMERIC_TOKEN: The current token is of numeric type
 IDENTIFIER_TOKEN: The current token is an identifier
 PARAN_TOKEN: The current token is a paranthesis
 DEF_TOEKN: The current token "func" def that whatever follows is a function
 definition  

 -------------- */


enum Token_Type {

	EOF_TOKEN = 0,
	NUMERIC_TOKEN,
	IDENTIFIER_TOKEN,
	PARAN_TOKEN,
	DEF_TOKEN
};

static int Numeric_Val;
static std::string Identifier_string;

static int get_token() {

 static int LastChar = ' ';

 while(isspace(LastChar))
 LastChar = fgetc(file);

 if(isalpha(LastChar)) {
	Identifier_string = LastChar;

	while(isalnum(LastChar = fgetc(file)))
	Identifier_string += LastChar;

       if(Identifier_string == "func")
	return DEF_TOKEN;
	return IDENTIFIER_TOKEN;
 }

 if(isdigit(LastChar)) {
	std::string NumStr;
	do {
	  NumStr += LastChar;
	  LastChar = fgetc(file);
	} while (isdigit(LastChar));

   Numeric_Val = strtord(NumStr.c_str(), 0);
   return NUMERIC_TOKEN;
 }

 if(LastChar == '#') {
	do LastChar = fgetc(file);
	while(LastChar != EOF && LastChar != '\n' && LastChar != '\r');
   
   if(LastChar != EOF) return get_token();
 }
 
 if(LastChar == EOF) return EOF_TOKEN;
 
 int ThisChar = LastChar;
 LastChar = fgetc(file);
 return ThisChar;

} // end of get_token()

/* DEFINE AST STRUCTURE */

// Base class is defined by parsing an expression as follows:

class BaseAST {
		public:
		virtual ~BaseAST();
};

// Then several  derived classes are defined  for every type of expression to parse

class VariableAST : public BaseAST {
	std::string Var_Name;
	// string object to store name of the variable
public:
	VariableAST (std::string &name) : Var_Name(name) () 
	/* paramatized constructor of variable AST Class to be  initialized with
	 the string passed to the constructor */
};

class NumericAST : public BaseAST {
		int numeric_val;
		NumericASt (intval) : numeric_val(val) {}
};

class BinaryAST : public BaseAST {
	// string object to store binary operators
		std::string Bin_Operator;
    // Objects used to store LHS and RHS of binary Expressions
    // The LHS and RHS binary operations can be of any type, hence a 
	// BaseAST object is used to store them
	BaseAST *LHS, *RHS; 
public: 
	BinaryAST (std::string op, BaseAST *lhs, BaseAST *rhs) : 
	Bin_Operator(op), LHS(lhs), RHS(rhs) {} 
	// Constructor to initialize the binary operator, lhs & rhs of the binary
	// expression
};

// The AST Class for function declartions 
class FunctionDeclAST {
		std::string Func_Name;
		std::vector<std::string> Arguments;
	public:
		FunctionDeclAST(const std::string &name, const std::vector<std::string> &args) :
		Func_Name(name), Arguments(args) {} 
};

// The AST Class for function definition 

class FunctionDefnAST {
  FunctionDeclAST *Func_Decl;
  BaseAST* Body;
public:
	FunctionDefnAST(FunctionDeclAST *proto, BaseAST *body) :
	Func_Decl(proto), Body(body) {}
};

// The AST Class for function call

class FunctionCallAST : public BaseAST {
	std::string Function_Callee;
	std::vector<BaseAST* > Function_Arguments;
public:
	FunctionCallAST(const std::string &callee, std::vector<BaseAST*> &args):
	Function_Callee(callee), Function_Arguments(args) {}
};

