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

//// TODO: remove
//std::ostream& operator<<(std::ostream& out, const MedianSkipList& list)
//{
//    const Node* cur = list.getNext(list.getHead());
//    while (cur != nullptr) {
//        out << cur->key << " ";
//        cur = cur->forward[0];
//    }
//    out << "\n";
//    return out;
//}
} // namespace

std::string RollingMedians::getMedians(const std::string& input)
{
    std::istringstream in(input);
    std::ostringstream out;
    for (Token token = getNextToken(in); token.type != Token::END; token = getNextToken(in)) {
        if (token.type == Token::NUMBER) {
            skipList.insert(token.value);
        }
        else if (token.type == Token::MEDIAN) {
            out << skipList.getMedian() << " ";
        }
    }
    return out.str();
}
