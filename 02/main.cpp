#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <functional>
#include "tokenParser.hpp"

void Test1(){
    std::string str;
	std::vector<uint64_t> Digits;
	std::vector<std::string> Strings;

	TokenParser TokenParser;
	TokenParser.SetStartCallback([&str](){str += "S";});
	TokenParser.SetEndCallback([&str](){str += "E";});
	TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
	    Digits.push_back(digitToken);
	});
	TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
	    Strings.push_back(stringToken);
	});

	TokenParser.StartParsing("I love 899 apples and 9213 banans   \
			2+2=5     \
			oh -1231");

	std::vector<uint64_t> DigitAns = {899, 9213};
	std::vector<std::string> StrAns = { "I", "love", "apples", "and", "banans", "2+2=5", "oh", "-1231" };
	assert(str == "SE");

    for(size_t i = 0; i < Digits.size(); ++i)
        assert(Digits[i] == DigitAns[i]);
    
    for(size_t i = 0; i < Strings.size(); ++i)
        assert(Strings[i] == StrAns[i]);
    assert(Digits.size() == DigitAns.size());
    assert(Strings.size() == StrAns.size());
}


void Test2(){
    std::string str;
	std::vector<uint64_t> Digits;
	std::vector<std::string> Strings;

	TokenParser TokenParser;
	TokenParser.SetEndCallback([&str](){str += "E";});
	TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
	    Digits.push_back(digitToken);
	});
	TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
	    Strings.push_back(stringToken);
	});

	TokenParser.StartParsing("I love 43 \t \t \t \n         apples -1231");

    assert(str == "E");
	std::vector<uint64_t> DigitAns = {43};
	std::vector<std::string> StrAns = { "I", "love", "apples", "-1231" };
	
    for(size_t i = 0; i < Digits.size(); ++i)
        assert(Digits[i] == DigitAns[i]);
    
    for(size_t i = 0; i < Strings.size(); ++i)
        assert(Strings[i] == StrAns[i]);

    assert(Digits.size() == DigitAns.size());
    assert(Strings.size() == StrAns.size());
}

void Test3(){
	std::vector<uint64_t> Digits;
	std::vector<std::string> Strings;

	TokenParser TokenParser;
	TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
	    Digits.push_back(digitToken);
	});
	TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
	    Strings.push_back(stringToken);
	});

	TokenParser.StartParsing("99123");
	std::vector<uint64_t> DigitAns = {99123};
	std::vector<std::string> StrAns = { };
	
    for(size_t i = 0; i < Digits.size(); ++i)
        assert(Digits[i] == DigitAns[i]);
    
    for(size_t i = 0; i < Strings.size(); ++i)
        assert(Strings[i] == StrAns[i]);

    assert(Digits.size() == DigitAns.size());
    assert(Strings.size() == StrAns.size());
}

void Test4(){
	std::vector<uint64_t> Digits;
	std::vector<std::string> Strings;

	TokenParser TokenParser;
	TokenParser.SetDigitTokenCallback([&Digits](uint64_t digitToken) {
	    Digits.push_back(digitToken);
	});
	TokenParser.SetStringTokenCallback([&Strings](std::string stringToken) {
	    Strings.push_back(stringToken);
	});

	TokenParser.StartParsing("9999999999999999999123");
	std::vector<uint64_t> DigitAns = {};
	std::vector<std::string> StrAns = {"9999999999999999999123"};

    for(size_t i = 0; i < Digits.size(); ++i)
        assert(Digits[i] == DigitAns[i]);
    for(size_t i = 0; i < Strings.size(); ++i)
        assert(Strings[i] == StrAns[i]);

    assert(Digits.size() == DigitAns.size());
    assert(Strings.size() == StrAns.size());
}

int main(){
    
	Test1();	
    Test2();
    Test3();
    Test4();

	return 0;
}	
