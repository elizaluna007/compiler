#include "front/lexical.h"

#include <map>
#include <cassert>
#include <string>

#define TODO assert(0 && "todo")

#define DEBUG_DFA
#define DEBUG_SCANNER

std::string frontend::toString(State s)
{
    switch (s)
    {
    case State::Empty:
        return "Empty";
    case State::Ident:
        return "Ident";
    case State::IntLiteral:
        return "IntLiteral";
    case State::FloatLiteral:
        return "FloatLiteral";
    case State::op:
        return "op";
    default:
        assert(0 && "invalid State");
    }
    return "";
}

std::set<std::string> frontend::keywords = {
    "const", "int", "float", "if", "else", "while", "continue", "break", "return", "void"};
bool isoperator(char c) // 判断这个是否是操作符的内容
{
    switch (c)
    {
    case '+':
        return true;
    case '-':
        return true;
    case '*':
        return true;
    case '/':
        return true;
    case '%':
        return true;
    case '<':
        return true;
    case '>':
        return true;
    case ':':
        return true;
    case '=':
        return true;
    case ';':
        return true;
    case ',':
        return true;
    case '(':
        return true;
    case ')':
        return true;
    case '[':
        return true;
    case ']':
        return true;
    case '{':
        return true;
    case '}':
        return true;
    case '!':
        return true;
    case '&':
        return true;
    case '|':
        return true;
    default:
        return false;
    }
}
bool isoperator_2(std::string s)
{
    if (s == "<=" || s == ">=" || s == "==" || s == "!=" || s == "&&" || s == "||")
        return true;
    else
        return false;
}
bool is_common_idnt(std::string s)
{
    if (s == "const" || s == "void" || s == "int" || s == "float" || s == "if" || s == "else" || s == "while" || s == "continue" || s == "break" || s == "return")
        return false;
    else
        return true;
}

frontend::TokenType get_op_type(std::string s) // 得到当前串的token类型
{
    if (s == "+")
    {
        return frontend::TokenType::PLUS;
    }
    else if (s == "-")
    {
        return frontend::TokenType::MINU;
    }
    else if (s == "*")
    {
        return frontend::TokenType::MULT;
    }
    else if (s == "/")
    {
        return frontend::TokenType::DIV;
    }
    else if (s == "%")
    {
        return frontend::TokenType::MOD;
    }
    else if (s == "<")
    {
        return frontend::TokenType::LSS;
    }
    else if (s == ">")
    {
        return frontend::TokenType::GTR;
    }
    else if (s == ":")
    {
        return frontend::TokenType::COLON;
    }
    else if (s == "=")
    {
        return frontend::TokenType::ASSIGN;
    }
    else if (s == ";")
    {
        return frontend::TokenType::SEMICN;
    }
    else if (s == ",")
    {
        return frontend::TokenType::COMMA;
    }
    else if (s == "(")
    {
        return frontend::TokenType::LPARENT;
    }
    else if (s == ")")
    {
        return frontend::TokenType::RPARENT;
    }
    else if (s == "[")
    {
        return frontend::TokenType::LBRACK;
    }
    else if (s == "]")
    {
        return frontend::TokenType::RBRACK;
    }
    else if (s == "{")
    {
        return frontend::TokenType::LBRACE;
    }
    else if (s == "}")
    {
        return frontend::TokenType::RBRACE;
    }
    else if (s == "!")
    {
        return frontend::TokenType::NOT;
    }
    else if (s == "<=")
    {
        return frontend::TokenType::LEQ;
    }
    else if (s == ">=")
    {
        return frontend::TokenType::GEQ;
    }
    else if (s == "==")
    {
        return frontend::TokenType::EQL;
    }
    else if (s == "!=")
    {
        return frontend::TokenType::NEQ;
    }
    else if (s == "&&")
    {
        return frontend::TokenType::AND;
    }
    else
    {
        return frontend::TokenType::OR;
    }
}
frontend::TokenType get_ident_type(std::string s)
{
    if (s == "const")
    {
        return frontend::TokenType::CONSTTK;
    }
    else if (s == "void")
    {
        return frontend::TokenType::VOIDTK;
    }
    else if (s == "int")
    {
        return frontend::TokenType::INTTK;
    }
    else if (s == "float")
    {
        return frontend::TokenType::FLOATTK;
    }
    else if (s == "if")
    {
        return frontend::TokenType::IFTK;
    }
    else if (s == "else")
    {
        return frontend::TokenType::ELSETK;
    }
    else if (s == "while")
    {
        return frontend::TokenType::WHILETK;
    }
    else if (s == "continue")
    {
        return frontend::TokenType::CONTINUETK;
    }
    else if (s == "break")
    {
        return frontend::TokenType::BREAKTK;
    }
    else if (s == "return")
    {
        return frontend::TokenType::RETURNTK;
    }
    else // 这里随便输出什么,因为肯定不存在其他token类型的标识符
    {
        return frontend::TokenType::IDENFR;
    }
}
frontend::DFA::DFA() : cur_state(frontend::State::Empty), cur_str() {}

frontend::DFA::~DFA() {}

bool frontend::DFA::next(char input, Token &buf)
{
#ifdef DEBUG_DFA
#include <iostream>
    std::cout << "in state [" << toString(cur_state) << "], input = \'" << input << "\', str = " << cur_str << "\n";
#endif
    if (isoperator(input)) // 假如新加入的字符是一个op的内容，前面的直接输出
    {
        switch (cur_state)
        {
        case State::Empty:
        {
            reset();
            cur_str = cur_str + input;
            cur_state = State::op;
            return false;
        }
        case State::Ident:
        {
            buf.value = cur_str;
            buf.type = get_ident_type(cur_str);
            reset();
            cur_str = cur_str + input;
            cur_state = State::op;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::IntLiteral:
        {
            buf.value = cur_str;
            buf.type = frontend::TokenType::INTLTR;
            reset();
            cur_str = cur_str + input;
            cur_state = State::op;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::FloatLiteral:
        {
            buf.value = cur_str;
            buf.type = frontend::TokenType::FLOATLTR;
            reset();
            cur_str = cur_str + input;
            cur_state = State::op;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::op: // 操作数的前一个是操作数的一部分,则继续观察
        {
            if (isoperator_2(cur_str + input))
            {
                cur_str = cur_str + input;
                cur_state = State::op;
                buf.value = cur_str;
                buf.type = get_op_type(cur_str);
                reset();
#ifdef DEBUG_DFA
                // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
                std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
                return true;
            }
            else
            {
                buf.value = cur_str;
                buf.type = get_op_type(cur_str);
                reset();
                cur_str = cur_str + input;
                cur_state = State::op;
#ifdef DEBUG_DFA
                // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
                std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
                return true;
            }
        }
        }
    }
    else if (input == ' ' || input == '\n' || input == '\r' || input == '\t') // 假如新加入的字符是一个Empty的开头，前面的直接输出
    {
        switch (cur_state)
        {
        case State::Empty:
        {
            reset();
            return false;
        }
        case State::Ident:
        {
            buf.value = cur_str;
            buf.type = get_ident_type(cur_str);
            reset();
            cur_str = cur_str + input;
            cur_state = State::Empty;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::IntLiteral:
        {
            buf.value = cur_str;
            buf.type = frontend::TokenType::INTLTR;
            reset();
            cur_str = cur_str + input;
            cur_state = State::Empty;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::FloatLiteral:
        {
            buf.value = cur_str;
            buf.type = frontend::TokenType::FLOATLTR;
            reset();
            cur_str = cur_str + input;
            cur_state = State::Empty;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        case State::op:
        {
            buf.value = cur_str;
            buf.type = get_op_type(cur_str);
            reset();
            cur_str = cur_str + input;
            cur_state = State::Empty;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        }
    }
    else if (input >= '0' && input <= '9') // 当前输入的是数值
    {
        switch (cur_state)
        {
        case State::Empty:
        {
            reset();
            cur_str = cur_str + input;
            cur_state = State::IntLiteral;
            return false;
        }
        case State::Ident:
        {
            cur_str = cur_str + input;
            cur_state = State::Ident;
            return false;
        }
        case State::IntLiteral:
        {
            cur_str = cur_str + input;
            cur_state = State::IntLiteral;
            return false;
        }
        case State::FloatLiteral:
        {
            cur_str = cur_str + input;
            cur_state = State::FloatLiteral;
            return false;
        }
        case State::op:
        {
            buf.value = cur_str;
            buf.type = get_op_type(cur_str);
            reset();
            cur_str = cur_str + input;
            cur_state = State::IntLiteral;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        }
    }
    else // 当前输入的是字母
    {
        switch (cur_state)
        {
        case State::Empty:
        {
            cur_str = input;
            cur_state = State::Ident;
            return false;
        }
        case State::Ident:
        {
            cur_str = cur_str + input;
            cur_state = State::Ident;
            return false;
        }
        case State::IntLiteral:
        {
            if (input == '.')
            {
                cur_str = cur_str + input;
                cur_state = State::FloatLiteral;
                return false;
            }
            else{
                cur_str = cur_str + input;
                cur_state = State::IntLiteral;
                return false;
            }
        }
        case State::FloatLiteral:
        {
        }
        case State::op:
        {
            buf.value = cur_str;
            buf.type = get_op_type(cur_str);
            reset();
            cur_str = cur_str + input;
            cur_state = State::Ident;
#ifdef DEBUG_DFA
            // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
            std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
            return true;
        }
        }
    }
#ifdef DEBUG_DFA
    // std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t, ret = " << ret << std::endl;
    std::cout << "next state is [" << toString(cur_state) << "], next str = " << cur_str << "\t" << std::endl;
#endif
}

void frontend::DFA::reset()
{
    cur_state = State::Empty;
    cur_str = "";
}

frontend::Scanner::Scanner(std::string filename) : fin(filename)
{
    if (!fin.is_open())
    {
        assert(0 && "in Scanner constructor, input file cannot open");
    }
}

frontend::Scanner::~Scanner()
{
    fin.close();
}

std::vector<frontend::Token> frontend::Scanner::run()
{
    std::string line;        // 读取文件中的每一行
    std::string content;     // 存储去除注释后的所有信息
    bool in_comment = false; // 当前是否在注释中

    while (std::getline(fin, line)) // 按行读取文件
    {
        std::string newline = ""; // 存储去除注释后的当前行信息
        for (int i = 0; i < line.length(); i++)
        {
            if (!in_comment && line[i] == '/') // 如果不在注释中且当前字符为'/'，判断是否为注释
            {
                if (i + 1 < line.length() && line[i + 1] == '/') // 如果后面一个字符也为'/'，则为单行注释
                {
                    break; // 跳过本行
                }
                else if (i + 1 < line.length() && line[i + 1] == '*') // 如果后面一个字符为'*'，则为多行注释的开始
                {
                    in_comment = true; // 标记当前在注释中
                    i++;               // 跳过'*' 
                }
                else // 其他情况为正常字符，将其加入当前行中
                {
                    newline += line[i];
                }
            }
            else if (in_comment && line[i] == '*') // 如果当前在注释中，判断是否为多行注释的结束
            {
                if (i + 1 < line.length() && line[i + 1] == '/') // 如果后面一个字符为'/'，则多行注释结束
                {
                    in_comment = false; // 标记当前不在注释中
                    i++;                // 跳过'/'
                }
            }
            else if(!in_comment)// 其他情况为正常字符，将其加入当前行中
            {
                newline += line[i];
            }
        }
        content += newline; // 将去除注释后的当前行加入总字符串中
    }
    content += "\n";
    std::vector<Token> ret;
    Token tk;
    DFA dfa;
    for (auto c : content)
    {
        if (dfa.next(c, tk))
        {
            ret.push_back(tk);
#ifdef DEBUG_SCANNER
#include <iostream>
            std::cout << "token: " << toString(tk.type) << "\t" << tk.value << std::endl;
#endif
        }
    }
    return ret;
}