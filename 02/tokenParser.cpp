#include "tokenParser.hpp"

void TokenParser::StartParsing(const std::string s) {
    int n = s.size();
    bool isDigit = true;
    std::string token = "";
    if(startF)
		startF();
    for(int i = 0; i < n; ++i){
        if(spaceChar(s[i])){
	        tokenF(isDigit, token);
        isDigit = true;
        token = "";
        while(i + 1 < n && spaceChar(s[i + 1]))
	        ++i;
        } else {
            token.push_back(s[i]);
            if(isDigit && !(s[i] >= '0' && s[i] <= '9'))
                 isDigit = false;
            if(i == n - 1)
                 tokenF(isDigit, token);
        }
	}
    if(endF)
		endF();
}
