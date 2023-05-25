#include"front/lexical.h"

#include<map>
#include<cassert>
#include<string>

#define TODO assert(0 && "todo")

// #define DEBUG_DFA
// #define DEBUG_SCANNER

std::string frontend::toString(State s) {
    switch (s) {
    case State::Empty: return "Empty";
    case State::Ident: return "Ident";
    case State::IntLiteral: return "IntLiteral";
    case State::FloatLiteral: return "FloatLiteral";
    case State::op: return "op";
    default:
        assert(0 && "invalid State");
    }
    return "";
}

std::set<std::string> frontend::keywords= {
    "const", "int", "float", "if", "else", "while", "continue", "break", "return", "void"
};

frontend::DFA::DFA(): cur_state(frontend::State::Empty), cur_str() {}

frontend::DFA::~DFA() {}



bool frontend::DFA::next(char input, Token& buf) {
#ifdef DEBUG_DFA
#include<iostream>
    std::cout << "in state [" << toString(cur_state) << "], input = \'" << input << "\', str = " << cur_str << "\t";
#endif

    switch (cur_state){
        case State::Empty:{
            // std::cout<<"empty"<<std::endl;
            switch (input){
                case ' ':case '\n':case '\t':case '\r':{
                    return false;
                }

                case '+':case '-':case '*':case '/':case '%':case '&':case '|':
                case '=':case '!':case '>':case '<':case ';':case ':':case ',':
                case '[':case ']':case '(':case ')':case '{':case '}':{
                    cur_state = State::op;
                    cur_str = cur_str + input;
                    return false;
                }

                case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
                case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':
                case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':
                case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':case 'A':
                case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
                case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':
                case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':
                case 'W':case 'X':case 'Y':case 'Z':{
                    cur_state = State::Ident;
                    cur_str = cur_str + input;
                    return false;
                }

                case '0':case '1':case '2':case '3':case '4':case '5':case '6':
                case '7':case '8':case '9':{
                    cur_state = State::IntLiteral;
                    cur_str = cur_str + input;
                    return false;
                }

                default: assert(0);
            }
            
        }

        case State::Ident:{
            // std::cout<<"ident"<<std::endl;
            switch (input){

                case '0':case '1':case '2':case '3':case '4':case '5':case '6':
                case '7':case '8':case '9':case '_':case 'a':case 'b':case 'c':
                case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':case 'j':
                case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':
                case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':
                case 'y':case 'z':case 'A':case 'B':case 'C':case 'D':case 'E':
                case 'F':case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':
                case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':case 'S':
                case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':{
                    cur_str = cur_str + input;
                    return false;
                }

                default:{
                    buf.type = parseIndent(cur_str);
                    buf.value = cur_str;
                    switch (input){
                        case ' ':case '\n':case '\t':case '\r':{
                            cur_state = State::Empty;
                            cur_str = "";
                            return true;
                        }

                        case '+':case '-':case '*':case '/':case '%':case '&':case '|':
                        case '=':case '!':case '>':case '<':case ';':case ':':case ',':
                        case '[':case ']':case '(':case ')':case '{':case '}':{
                            cur_state = State::op;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        default: assert(0);
                    }
                }
            }
        }

        case State::IntLiteral:{
            // std::cout<<"int"<<std::endl;
            switch (input){

                case '0':case '1':{
                    cur_str = cur_str + input;
                    return false;
                }

                case '2':case '3':case '4':case '5':case '6':case '7':{
                    if ( !(cur_str.length() >= 2 && cur_str[0] == '0' && cur_str[1] == 'b') ){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }

                case '8':case '9':{
                    if (cur_str[0] != '0' || (cur_str.length() >= 2 && cur_str[1] == 'x')){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }

                case 'A':case 'C':case 'D':case 'E':case 'F':case 'a':
                case 'c':case 'd':case 'e':case 'f':{
                    if (cur_str.length() >= 2 && cur_str[1] == 'x'){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }

                case 'b':case 'B':{
                    if(cur_str == "0" || cur_str.length() >= 2 && cur_str[1] == 'x'){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }


                case 'x':case 'X':{
                    if (cur_str == "0"){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }

                case '.':{
                    if(cur_str[0] != 0){
                        cur_state = State::FloatLiteral;
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag0;
                }

                default:{
                    default_tag0:
                    buf.type = TokenType::INTLTR;
                    buf.value = cur_str;
                    switch (input){
                        case ' ':case '\n':case '\t':case '\r':{
                            cur_state = State::Empty;
                            cur_str = "";
                            return true;
                        }

                        case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
                        case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':
                        case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':
                        case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':case 'A':
                        case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
                        case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':
                        case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':
                        case 'W':case 'X':case 'Y':case 'Z':{
                            cur_state = State::Ident;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '0':case '1':case '2':case '3':case '4':case '5':case '6':
                        case '7':case '8':case '9':{
                            cur_state = State::IntLiteral;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '+':case '-':case '*':case '/':case '%':case '&':case '|':
                        case '=':case '!':case '>':case '<':case ';':case ':':case ',':
                        case '[':case ']':case '(':case ')':case '{':case '}':{
                            cur_state = State::op;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        default: assert(0);
                    }
                }
            }
        }

        case State::FloatLiteral:{
            // std::cout<<"float"<<std::endl;
            switch (input){

                case '0':case '1':case '2':case '3':case '4':case '5':case '6':
                case '7':case '8':case '9':{
                    cur_str = cur_str + input;
                    return false;
                }

                default:{
                    buf.type = TokenType::FLOATLTR;
                    buf.value = cur_str;
                    switch (input){
                        case ' ':case '\n':case '\t':case '\r':{
                            cur_state = State::Empty;
                            cur_str = "";
                            return true;
                        }

                        case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
                        case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':
                        case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':
                        case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':case 'A':
                        case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
                        case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':
                        case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':
                        case 'W':case 'X':case 'Y':case 'Z':{
                            cur_state = State::Ident;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '+':case '-':case '*':case '/':case '%':case '&':case '|':
                        case '=':case '!':case '>':case '<':case ';':case ':':case ',':
                        case '[':case ']':case '(':case ')':case '{':case '}':{
                            cur_state = State::op;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }
                        
                        default: assert(0);
                    }
                }
            }
        }

        case State::op:{
            // std::cout<<"op"<<std::endl;
            switch (input){
                case '=':{
                    if (cur_str == "<" || cur_str == ">" || cur_str == "!" || cur_str == "=" ){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag1;
                }

                case '&':{
                    if (cur_str == "&"){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag1;
                }

                case '|':{
                    if (cur_str == "|"){
                        cur_str = cur_str + input;
                        return false;
                    }
                    // else assert(0);
                    else goto default_tag1;
                }

                default:{
                    default_tag1:
                    buf.type = parseOp(cur_str);
                    buf.value = cur_str;
                    switch (input){
                        case ' ':case '\n':case '\t':case '\r':{
                            cur_state = State::Empty;
                            cur_str = "";
                            return true;
                        }

                        case '_':case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':
                        case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':
                        case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':
                        case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':case 'A':
                        case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':
                        case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':
                        case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':
                        case 'W':case 'X':case 'Y':case 'Z':{
                            cur_state = State::Ident;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '0':case '1':case '2':case '3':case '4':case '5':case '6':
                        case '7':case '8':case '9':{
                            cur_state = State::IntLiteral;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '+':case '-':case '*':case '/':case '%':case '&':case '|':
                        case '=':case '!':case '>':case '<':case ';':case ':':case ',':
                        case '[':case ']':case '(':case ')':case '{':case '}':{
                            cur_state = State::op;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        case '.':{
                            cur_state = State::FloatLiteral;
                            cur_str = "";
                            cur_str = cur_str + input;
                            return true;
                        }

                        default:assert(0);
                    }
                }
            }
            break;
        }
    
    }



#ifdef DEBUG_DFA
    std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
#endif
}

void frontend::DFA::reset() {
    cur_state = State::Empty;
    cur_str = "";
}

frontend::Scanner::Scanner(std::string filename): fin(filename) {
    if(!fin.is_open()) {
        assert(0 && "in Scanner constructor, input file cannot open");
    }
}

frontend::Scanner::~Scanner() {
    fin.close();
}

std::vector<frontend::Token> frontend::Scanner::run() {
    std::vector<Token> ret;
    Token tk;

    DFA dfa;
    dfa.reset();

    std::string s = preprocess(fin);

    for(auto c: s){
        if(dfa.next(c, tk)) ret.push_back(tk);

    }

    

#ifdef DEBUG_SCANNER
#include<iostream>
            std::cout << "token: " << toString(tk.type) << "\t" << tk.value << std::endl;
#endif

    return ret;
}

frontend::TokenType frontend::parseIndent(std::string indent){

    if(keywords.find(indent) != keywords.end()){
        if(indent == "const") return TokenType::CONSTTK;
        else if(indent == "int") return TokenType::INTTK;
        else if(indent == "float") return TokenType::FLOATTK;
        else if(indent == "if") return TokenType::IFTK;
        else if(indent == "else") return TokenType::ELSETK;
        else if(indent == "while") return TokenType::WHILETK;
        else if(indent == "continue") return TokenType::CONTINUETK;
        else if(indent == "break") return TokenType::BREAKTK;
        else if(indent == "return") return TokenType::RETURNTK;
        else if(indent == "void") return TokenType::VOIDTK;
        else assert(0);
    }
    else return TokenType::IDENFR;
}

frontend::TokenType frontend::parseOp(std::string op){

    if(op == "+") return TokenType::PLUS;
    else if(op == "-") return TokenType::MINU;
    else if(op == "*") return TokenType::MULT;
    else if(op == "/") return TokenType::DIV;
    else if(op == "%") return TokenType::MOD;
    else if(op == "<") return TokenType::LSS;
    else if(op == ">") return TokenType::GTR;
    else if(op == ":") return TokenType::COLON;
    else if(op == "=") return TokenType::ASSIGN;
    else if(op == ";") return TokenType::SEMICN;
    else if(op == ",") return TokenType::COMMA;
    else if(op == "(") return TokenType::LPARENT;
    else if(op == ")") return TokenType::RPARENT;
    else if(op == "[") return TokenType::LBRACK;
    else if(op == "]") return TokenType::RBRACK;
    else if(op == "{") return TokenType::LBRACE;
    else if(op == "}") return TokenType::RBRACE;
    else if(op == "!") return TokenType::NOT;
    else if(op == "<=") return TokenType::LEQ;
    else if(op == ">=") return TokenType::GEQ;
    else if(op == "==") return TokenType::EQL;
    else if(op == "!=") return TokenType::NEQ;
    else if(op == "&&") return TokenType::AND;
    else if(op == "||") return TokenType::OR;
    else assert(0);
}

std::string frontend::preprocess(std::ifstream& fin){
    enum CMTType {STM0, STM1, STM2, STM3, STM4};

    CMTType state = CMTType::STM0;

    std::string res;
    char c;

    while(! fin.eof()){
        fin.get(c);

        switch (state){
            case CMTType::STM0:{
                res = res + c;
                if (c == '/')state = CMTType::STM1;
                break;
            }
            case CMTType::STM1:{
                if (c == '/'){
                    state = CMTType::STM2;
                    res = res.substr(0,res.length()-1);
                }
                else if(c == '*'){
                    state = CMTType::STM3;
                    res = res.substr(0,res.length()-1);
                }
                else {
                    state = CMTType::STM0;
                    res = res + c;
                }
                break;
            }
            case CMTType::STM2:{
                if (c == '\n')state = CMTType::STM0;
                break;
            }
            case CMTType::STM3:{
                if (c == '*')state = CMTType::STM4;
                break;
            }
            case CMTType::STM4:{
                if (c == '/')state = CMTType::STM0;
                else state = CMTType::STM3;
                break;
            }
            default: assert(0);
        }
       
    }

    return res;
}