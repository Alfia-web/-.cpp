
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <clocale>
using namespace std;

bool exc = false;

double  resultAnalis(const string& expression, int& i, bool& error);

double operations(char op, double a, double b, bool& error) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            cout << "Ошибка: деление на ноль\n";
            exc = true;
            error = true;
            return 0;
        }
        return a / b;
    case '^': return pow(a, b);
    case '#':
        if (b < 0) {
            cout << "Ошибка: корень из отрицательного числа\n";
            exc = true;
            error = true;
            return 0;
        }
        return sqrt(b);
    default:
        cout << "Ошибка: неизвестный оператор\n";
        error = true;
        return 0;
    }
}

double readNumber(const string& expression, int& i) {
    string value;
    while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
        value += expression[i++];
    }
    return stod(value);
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '#';
}

bool isValidSimbol(char c) {
    return isdigit(c) || c == '.' || c == '#' || isOperator(c) || c == '(' || c == ')' || isspace(c);
}

double mulDiv(const string& expression, int& i, bool& error);

double stepen(const string& expression, int& i, bool& error);

double firstAnalis(const string& expression, int& i, bool& error)
{
    while (i < expression.length() && isspace(expression[i]))
        i++;

    bool negative = false;

    if (i < expression.size() && expression[i] == '-' &&
        (i == 0 || expression[i - 1] == '(' || isOperator(expression[i - 1])))
    {
        negative = true;
        i++;
        while (i < expression.length() && isspace(expression[i]))
            i++;
    }
    if (i < expression.size() && expression[i] == '(')
    {
        i++; 
        double value = resultAnalis(expression, i, error);
        if (i >= expression.size() || expression[i] != ')')
        {
            error = true; 
            return 0;
        }
        i++;
        return negative ? -value : value;
    }
    else if (i < expression.size() && expression[i] == '#')
    {
        i++;
        double value = firstAnalis(expression, i, error);
        double result = operations('#', 0, value, error);
        return negative ? -result : result;
    }
    else if (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.'))
    {
        bool hasPoint = false;
        int start = i;

        if (expression[i] == '.' && (i + 1 >= expression.size() || !isdigit(expression[i + 1])))
        {
            error = true;
            return 0;
        }

        while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.'))
        {
            if (expression[i] == '.')
            {
                if (hasPoint) 
                {
                    error = true;
                    return 0;
                }
                hasPoint = true;
            }
            i++;
        }

        if (i > start && expression[i - 1] == '.')
        {
            error = true;
            return 0;
        }

        i = start;
        double number = readNumber(expression, i);
        return negative ? -number : number;
    }
    else
    {
        error = true;
        return 0;
    }
}

double stepen(const string& expression, int& i, bool& error) {
    double left = firstAnalis(expression, i, error);

    if (error)
        return 0;

    while (i < expression.length())
    {
        while (i < expression.length() && isspace(expression[i]))
            i++;

        if (i < expression.length() && expression[i] == '^')
        {
            i++;
            double right = stepen(expression, i, error);
            if (error)
                return 0;
            left = operations('^', left, right, error);
            if (error)
                return 0;
        }
        else break;
    }
    return left;
}

double mulDiv(const string& expression, int& i, bool& error) {
    double left = stepen(expression, i, error);

    if (error)
        return 0;

    while (i < expression.length())
    {
        while (i < expression.length() && isspace(expression[i]))
            i++;
        if (i < expression.length() && (expression[i] == '*' || expression[i]=='/'))
        {
            char op = expression[i++];
            double right = stepen(expression, i, error);
            if (error)
                return 0;
            left = operations(op, left, right, error);
            if (error)
                return 0;
        }
        else break;
    }
    return left;
}

string replaceMulti(const string& expression) {
    string result;
    for (size_t i = 0; i < expression.length(); ++i) {
        if (i > 0 && expression[i] == '(' &&
            (isdigit(expression[i - 1]) || expression[i - 1] == ')')) {
            result += '*';
        }
        else if (i > 0 && isdigit(expression[i - 1]) && expression[i] == '(') {
            result += '*';
        }
        else if (i > 0 && expression[i - 1] == ')' &&
            (isdigit(expression[i]) || expression[i] == '.')) {
            result += '*';
        }

        result += expression[i];
    }
    return result;
}

bool validateExpression(const string& expression) {
    for (char c : expression) {
        if (!isValidSimbol (c)) {
            return false;
        }
    }
    return true;
}

double resultAnalis(const string& expression, int& i, bool& error) {
    double left = mulDiv(expression, i, error);

    if (error)
        return 0;

    while (i < expression.length())
    {
        while (i < expression.length() && isspace(expression[i]))
            i++;

        if (i < expression.length() && (expression[i] == '+' || expression[i] == '-'))
        {
            
            char op = expression[i++];
            double right = mulDiv(expression, i, error);
            if (error)
                return 0;
            left = operations(op, left, right, error);
            if (error)
                return 0;
        }
        else break;
    }
    return left;
}

void runAnalis() {
    while (true) {
        string input;
        cout << "Введите выражение" << endl;
        getline(cin, input);
        if (input == "exit")
            break;

        if (!validateExpression(input)) {
            continue;
        }
        string processedInput = replaceMulti(input);

        bool error = false;
        int i = 0;
        double result = resultAnalis(processedInput, i, error);
        if (!error)
            cout << "Результат: " << result << endl;
        if (error) {
            if (!exc)
              cout << "Ошибка в выражении" << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    setlocale(LC_NUMERIC, "C");
    cout << "Калькулятор" << endl;
    runAnalis();
}