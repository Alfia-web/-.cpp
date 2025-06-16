
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

double operations(char op, double a, double b, bool& error) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            cout << "Ошибка: деление на ноль\n";
            error = true;
            return 0;
        }
        return a / b;
    case '^': return pow(a, b);
    case '#':
        if (b < 0) {
            cout << "Ошибка: корень из отрицательного числа\n";
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


double firstAnalis(const string expression, int& i, bool& error)
{
    while (i < expression.length() && isspace(expression[i]))
        i++;

    if (i < expression.size() && expression[i] == '(')
    {
        i++;

        double value = 0;

        if (i >= expression.size() || expression[i] != ')')
        {
            error = true;
            return 0;
        }
        i++;
        return value;
    }

    else if (i < expression.size() && expression[i] == '#')
    {
        i++;
        double value = firstAnalis(expression, i, error);
        return operations('#', 0, value, error);
    }
    else if (isdigit(expression[i] || expression[i] == '.'))
    {
        return readNumber(expression, i);
    }
    else
    {
        error = true; 
        return 0;
    }
    if (error) {
        cout << "Ошибка в выражении" << endl;
    }
}

