#include "tokenParser.hpp"

void TokenParser::StartParsing(const std::string s) {
    int n = s.size();
	unsigned long long value = 0;
	const unsigned long long max = 0xFFFFFFFFFFFFFFFF;
    bool isDigit = true;
    std::string token = "";
    if(startF)
		startF();
    for(int i = 0; i < n; ++i){
        if(spaceChar(s[i])){
	        tokenF(isDigit, token, value);
			isDigit = true;
			token = "";
			value = 0;
			while(i + 1 < n && spaceChar(s[i + 1]))
				++i;
        } else {
            token.push_back(s[i]);
            if(isDigit && !(s[i] >= '0' && s[i] <= '9'))
                 isDigit = false;
			if(isDigit){ 
				if(value > max/10)
					isDigit = false;
				value *= 10;
				if(value > max - s[i] + '0')
					isDigit = false;	
				value += s[i] - '0';
			}	
            if(i == n - 1)
                 tokenF(isDigit, token, value);
        }
	}
    if(endF)
		endF();
}
