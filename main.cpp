#include <iostream>
#include <sstream>
#include <string>

using namespace std;

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

Token getNextToken(istringstream& ss)
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
    cout << "getMedian()" << endl;
    return 0.0;
}

void addNumber(double d)
{
    cout << "addNumber(" << d << ")" << endl;
}

string rollingMedians(string input)
{
    istringstream sin(input);
    ostringstream sout;
    for (Token token = getNextToken(sin); token.type != Token::END; token = getNextToken(sin)) {
        if (token.type == Token::NUMBER) {
            addNumber(token.value);
        }
        else if (token.type == Token::MEDIAN) {
            sout << getMedian() << " ";
        }
    }
    return sout.str();
}

int main()
{
    string input;
    getline(cin, input);
    cout << rollingMedians(input);
    return 0;
}
