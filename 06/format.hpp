#include <vector>
#include <sstream>

template<class T>
void getVectorData(std::vector<std::string>& data, T& value) {
    std::stringstream stream;
    stream << value;
    data.push_back(stream.str());
}

template<class T, class... Args>
void getVectorData(std::vector<std::string>& data, T& value, Args&&... args) {
    std::stringstream stream;
    stream << value;
    data.push_back(stream.str());
    getVectorData(data, std::forward<Args>(args)...);
}

template<class... Args>
std::string format(std::string source, Args&&... args) {


    struct formatVal{
        size_t start;
        size_t end;
        size_t value;
    };
    
    size_t len = source.size();
    std::vector<formatVal> formatingValues;
    formatVal t;
    bool isNumber = false;
    for(size_t i = 0, value = 0, count = 0; i < len; ++i){
        if(source[i] == '}'){
            t.end = i;
            t.value = value;
            if(t.end - t.start == 1)
                throw std::runtime_error("{_} must have number");
            isNumber = false;
            --count;
            formatingValues.push_back(t);
        }
        if(isNumber){
            value*= 10;
            size_t x = source[i] - '0';
            if(x > 9)
                throw std::runtime_error("Finding character in context isn't number");
            value+= x;
        }
        if(source[i] == '{'){
            t.start = i;
            value = 0;
            isNumber = true;
            ++count;
        }
        if(count > 1)
            throw std::runtime_error("} so much");
    }

    size_t maxValue = 0;

    for(size_t i = 0; i < formatingValues.size(); ++i){
        if(maxValue < formatingValues[i].value)
            maxValue = formatingValues[i].value;
    }

    std::vector<std::string> data;
    getVectorData(data, args...);
    size_t n = data.size();

    if(maxValue >= n)
        throw std::runtime_error("Format number very big");

    std::string res = "";
    for(size_t i = 0, j = 0; i < len; ++i){
        if(i == formatingValues[j].start){
            i = formatingValues[j].end;
            res += data[formatingValues[j].value];
            ++j;
        } else {
           res.push_back(source[i]); 
        }
    }
    return res;
}
