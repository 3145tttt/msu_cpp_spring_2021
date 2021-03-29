#pragma once

#include<string>
#include<functional>

class TokenParser
{
private:
    bool spaceChar(char c){
        return c == ' ' || c == '\t' || c == '\n';
    }

    void tokenF(bool isDigit, std::string s) {
        if(isDigit && digitF)
            digitF(s);
        else if(stringF)
            stringF(s);
    }

    std::function<void()> startF;

    std::function<void()> endF;

    std::function<void(std::string)> digitF;

    std::function<void(std::string)> stringF;

public:
    TokenParser() = default;

	void SetStartCallback(std::function<void()> t = nullptr){
        startF =  t;
    }

    void SetEndCallback(std::function<void()> t = nullptr){
        endF =  t;
    }

    void SetDigitTokenCallback(std::function<void(std::string)> t = nullptr){
        digitF =  t;
    }

    void SetStringTokenCallback(std::function<void(std::string)> t = nullptr){
        stringF =  t;
    }	
	
	void StartParsing(const std::string s);
};
