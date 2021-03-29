#include <iostream>
#include "tokenParser.hpp"
#include <cassert>

std::string testStr = "", testDigit = "";
int startCounter = 0;
int endCounter = 0;

void printS(){
	static int i = 1;
	startCounter = i++;
}

void printF(){
	static int i = 1;
	endCounter = i++;
}

void printStr(std::string s){
	static int i = 1;
	testStr = s + std::to_string(i++);
}

void printDigit(std::string s){
	static int i = 1;
    testDigit = s + std::to_string(i++);
}

void reset(){
	testStr = "";
	testDigit = "";
	startCounter = 0;
	endCounter = 0;
	
}

void standartTest(){
	std::string s = "hello 67friend i like 9 apple\n";
	TokenParser my_parser;
    my_parser.SetStartCallback(printS);
    my_parser.SetEndCallback(printF);
    my_parser.SetDigitTokenCallback(printDigit);
    my_parser.SetStringTokenCallback(printStr);
    my_parser.StartParsing(s);
	
	assert(startCounter == 1 && endCounter == 1);
	assert(testStr == "apple5" && testDigit == "91");

	reset();
}

void withoutCallbackTest1(){
    std::string s = "hello 67friend i like 9 apple\n";
    TokenParser my_parser;
    my_parser.SetDigitTokenCallback(printDigit);
    my_parser.SetStringTokenCallback(printStr);
    my_parser.StartParsing(s);

    assert(startCounter == 0 && endCounter == 0);
    assert(testStr == "apple10" && testDigit == "92");

    reset();
}

void withoutCallbackTest2(){
    std::string s = "hello 67friend i like 9 apple\n";
    TokenParser my_parser;
    my_parser.SetStartCallback(printS);
    my_parser.SetEndCallback(printF);
    my_parser.StartParsing(s);

    assert(startCounter == 2 && endCounter == 2);
    assert(testStr == "" && testDigit == "");

    reset();
}

void repeatTest(){
    std::string s = "hello 67friend i like 9 apple\n";
    TokenParser my_parser;
    my_parser.SetStartCallback(printS);
    my_parser.SetEndCallback(printF);
    my_parser.StartParsing(s);
	my_parser.StartParsing(s);
    assert(startCounter == 4 && endCounter == 4);
    assert(testStr == "" && testDigit == "");

    reset();
}

void spaceTest(){
    std::string s = "hello   \t \t\n 67friend    i   like \t\n9 apple\n";
    TokenParser my_parser;
    my_parser.SetStartCallback(printS);
    my_parser.SetEndCallback(printF);
    my_parser.SetDigitTokenCallback(printDigit);
    my_parser.SetStringTokenCallback(printStr);
    my_parser.StartParsing(s);

    assert(startCounter == 5 && endCounter == 5);
    assert(testStr == "apple15" && testDigit == "93");

    reset();
}

int main()
{
    
	standartTest();
	withoutCallbackTest1();
	withoutCallbackTest2();
	repeatTest();
	spaceTest();
	
	return 0;
}	
