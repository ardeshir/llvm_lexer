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

	while(isalpha(LastChar = fgetc(file)))
	Identifier_string += LastChar;

       if(Identifier_string == "func")
	return DEF_TOEKN;
	return IDENTIFIER_TOKEN;
 }

 if(isdigit(LastChar)) {
	std::string NumStr;
	do {
	  NumStr += LastChar;
	  LastChar = fgetc(file);
	} while (isdigit(LastChar)):
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
