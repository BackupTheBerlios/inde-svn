#include "SyntaxParser.h"

FXIMPLEMENT(SyntaxParser,FXObject,NULL,0)


// Constructor
SyntaxParser::SyntaxParser()
{
	line = new FXchar;
	tok = new FXchar;
	fp = NULL;
	number = 0;
}


// Destructor
SyntaxParser::~SyntaxParser()
{
	if (fp) fclose(fp);
	delete line;
	delete tok;
}


// Set file
void SyntaxParser::setFile(const FXString& filename)
{
	FXTRACE((1, "%s::%s(\"%s\")\n", getClassName(), "setFile", filename.text()));
	if (fp) fclose(fp);
	file = filename;
}


// Get file
const FXString& SyntaxParser::getFile()
{
	return file;
}


// Get next non-empty line
FXchar* SyntaxParser::getline()
{
	register FXchar *ptr;
	while ((ptr = fgets(buffer, sizeof(buffer), fp)) != NULL)
	{
		number++;
	    while(*ptr && isspace((FXuchar) *ptr)) 
	    {	
	    	ptr++;
		    if(*ptr != '\0' && *ptr != '\n' && *ptr != '\r' && *ptr != '#') 
		    {
		    	break;
		    }
	    }
	}
	return ptr;
}


// Get next token from file
const FXchar* SyntaxParser::token()
{
	line = tok = getline();
	if(!line) return NULL;
	while(*line && isalpha((FXuchar) *line)) line++;
	*line++ = '\0';
	return tok;
}


// Parse word from line
const FXchar* SyntaxParser::word()
{
	register FXchar *value;
	while(*line && isspace((FXuchar) *line)) line++;
	value = line;
	while(*line && !isspace((FXuchar) *line)) line++;
	*line++ = '\0';
	return value;
}


// Parse escaped string from line
const FXchar* SyntaxParser::string()
{
	register FXchar *value, *ptr;
	while(*line && *line != '"') line++;
	if(*line == '"')
	{
		line++;
		value = ptr=line;
		while(*line && *line != '\n' && *line != '\r' && *line != '"')
		{
			if(*line == '\\' && *(line+1) == '"') line++;
			*ptr++ = *line++;
		}
		*ptr='\0';
		return value;
	}
  	return "";
}


// Parse rules and sub rules
FXbool SyntaxParser::parserules(FXSyntax *syntax,FXint parent){
  FXString   name,brex,erex,srex;
  FXRex      expression;
  FXRexError error;
  FXint      index;

  FXTRACE((1,"parserules begin parent = %d\n",parent));

  // Parse the rules
  while(strcmp(tok,"rule")==0){

    // Parse name
    name=string();

    // Clear to empty
    brex=FXString::null;
    erex=FXString::null;
    srex=FXString::null;

    // Parse rule info
    while(token()){
      if(strcmp(tok,"pattern")==0){             // Simple pattern
        brex=string();
        if((error=expression.parse(brex,REX_SYNTAX))!=REGERR_OK){
          fxwarning("%s:%d: error: %s.\n",file.text(),number,FXRex::getError(error));
          return FALSE;
          }
        continue;
        }
      if(strcmp(tok,"openpattern")==0){         // Open pattern
        brex=string();
        if((error=expression.parse(brex,REX_SYNTAX))!=REGERR_OK){
          fxwarning("%s:%d: error: %s.\n",file.text(),number,FXRex::getError(error));
          return FALSE;
          }
        continue;
        }
      if(strcmp(tok,"closepattern")==0){        // Close pattern
        erex=string();
        if((error=expression.parse(erex,REX_SYNTAX))!=REGERR_OK){
          fxwarning("%s:%d: error: %s.\n",file.text(),number,FXRex::getError(error));
          return FALSE;
          }
        continue;
        }
      if(strcmp(tok,"stoppattern")==0){         // Stop pattern
        srex=string();
        if((error=expression.parse(srex,REX_SYNTAX))!=REGERR_OK){
          fxwarning("%s:%d: error: %s.\n",file.text(),number,FXRex::getError(error));
          return FALSE;
          }
        continue;
        }
      break;
      }

    // Premature end
    if(!tok){
      fxwarning("%s:%d: error: unexpected end of file.\n",file.text(),number);
      return FALSE;
      }

    FXTRACE((1,"brex = %s\n",brex.text()));
    FXTRACE((1,"erex = %s\n",erex.text()));
    FXTRACE((1,"srex = %s\n",srex.text()));

    // Validation
    if(brex.empty()) return FALSE;

    // Create rule
    if(erex.empty() && srex.empty()){
      index=syntax->append(name,brex,parent);
      }
    else if(srex.empty()){
      index=syntax->append(name,brex,erex,parent);
      }
    else{
      index=syntax->append(name,brex,erex,srex,parent);
      }

    // Parse subrules, if any
    if(!parserules(syntax,index)) return FALSE;

    // Check end
    if(strcmp(tok,"end")!=0){
      fxwarning("%s:%d: error: expected 'end'.\n",file.text(),number);
      return FALSE;
      }

    // Next token
    token();
    if(!tok) return FALSE;
    }
  FXTRACE((1,"parserules end parent = %d\n",parent));
  return TRUE;
  }


// Parse file
FXbool SyntaxParser::parse(FXSyntaxList& syntaxes){
  FXSyntax *syntax;
  FXString  name;

  FXTRACE((1,"SyntaxParser::parse: file = %s\n",file.text()));

  // Open file
  fp=fopen(file.text(),"r");
  if(!fp){
    fxwarning("error: unable to open file: %s.\n",file.text());
    return FALSE;
    }

  // Parse the languages
  while(token()){

    // Parse next language
    if(strcmp(tok,"language")!=0){
      fxwarning("%s:%d: error: expected 'language'.\n",file.text(),number);
      return FALSE;
      }

    // Parse language name
    name=string();

    // Make new language node
    syntax=new FXSyntax(name);

    // Add to list
    syntaxes.append(syntax);

    // Parse language info
    while(token()){
      if(strcmp(tok,"filesmatch")==0){          // File extensions
        syntax->setExtensions(string());
        continue;
        }
      if(strcmp(tok,"contentsmatch")==0){       // File contents
        syntax->setContents(string());
        continue;
        }
      if(strcmp(tok,"delimiters")==0){          // Word delimiters
        syntax->setDelimiters(string());
        continue;
        }
      if(strcmp(tok,"contextlines")==0){        // Context lines
        syntax->setContextLines(FXIntVal(word()));
        continue;
        }
      if(strcmp(tok,"contextchars")==0){        // Context chars
        syntax->setContextChars(FXIntVal(word()));
        continue;
        }
      break;
      }

    // Premature end
    if(!tok){
      fxwarning("%s:%d: error: unexpected end of file.\n",file.text(),number);
      return FALSE;
      }

    // Parse rules
    if(!parserules(syntax,0)) return FALSE;

    // Check end
    if(strcmp(tok,"end")!=0){
      fxwarning("%s:%d: error: expected 'end'.\n",file.text(),number);
      return FALSE;
      }
    }
  FXTRACE((1,"SyntaxParser::parse: OK\n"));
  return TRUE;
  }
