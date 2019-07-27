#include "../rollingmedian.h"
#include <sstream>
#include <iostream>

namespace  {

const char DELIM_TOKEN{' '};
const char MEDIAN_TOKEN{'m'};
const char END_TOKEN{'q'};

struct Token
{
    enum {
        NUMBER,
        MEDIAN,
        END
    } type;
    double value;
};

Token getNextToken(std::istringstream& ss)
{
    while (ss.peek() == DELIM_TOKEN) {
        ss.get();
    }
    char c = ss.peek();
    if (c == MEDIAN_TOKEN) {
        ss >> c;
        return {Token::MEDIAN, 0};
    }
    else if (c == END_TOKEN) {
        return {Token::END, 0};
    }
    double d;
    ss >> d;
    return {Token::NUMBER, d};
}

double getMedian()
{
    std::cout << "getMedian()" << std::endl;
    return 0.0;
}

void addNumber(double d)
{
    std::cout << "addNumber(" << d << ")" << std::endl;
}

} // namespace

std::string RollingMedians::getMedians(const std::string& input)
{
    std::istringstream in(input);
    std::ostringstream out;
    for (Token token = getNextToken(in); token.type != Token::END; token = getNextToken(in)) {
        if (token.type == Token::NUMBER) {
            addNumber(token.value);
        }
        else if (token.type == Token::MEDIAN) {
            out << getMedian() << " ";
        }
    }
    return out.str();
}
