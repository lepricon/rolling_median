#include "../rollingmedian.h"
#include <iostream>
#include <iomanip>

namespace {
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
    int value;
};

Token getNextToken(std::istringstream& ss)
{
    while (ss.good() and ss.peek() == DELIM_TOKEN) {
        ss.get();
    }
    if (not ss.good()) {
        return {Token::END, 0};
    }
    char c = ss.peek();
    if (c == MEDIAN_TOKEN) {
        ss >> c;
        return {Token::MEDIAN, 0};
    }
    else if (c == END_TOKEN) {
        return {Token::END, 0};
    }
    int d;
    ss >> d;
    return {Token::NUMBER, d};
}
} // namespace

std::string RollingMedians::getMedians(const std::string& input) noexcept
{
    std::istringstream in(input);
    std::ostringstream out;
    try {
        for (Token token = getNextToken(in); token.type != Token::END; token = getNextToken(in)) {
            if (token.type == Token::NUMBER) {
                skipList.insert(token.value);
            }
            else if (token.type == Token::MEDIAN) {
                if (skipList.size() > 0) {
                    out << std::setprecision(10) << skipList.getMedian() << " ";
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: unable to calculate further: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Error: unknown error." << std::endl;
    }
    return out.str();
}
