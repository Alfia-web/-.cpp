
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

double  resultAnalis(const string& expression, int& i, bool& error);


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

        double value = resultAnalis(expression, i, error);

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
    else if (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.'))

    {
        return readNumber(expression, i);
    }
    else
    {
        error = true; 
        return 0;
    }
    
}

double  resultAnalis(const string& expression, int& i, bool& error) {
    error = false;
    //
    double result = firstAnalis(expression, i, error);
    if (error)
        return 0;

    while (i < expression.length()) {
        while (i < expression.length() && isspace(expression[i])) 
            i++;

        if (i >= expression.length() || expression[i]==')')
            break;

        char op = expression[i++];

      
        while (i < expression.length() && isspace(expression[i]))
            i++;

        double nextNumber = firstAnalis(expression, i, error);
        if (error)
            return 0;

        result = operations(op, result, nextNumber, error);
        if (error)
            return 0;
    }

    return result;
}




void runAnalis(){
    string input;
    cout << "Введите выражение" << endl;
    getline(cin, input);
    
    bool error = false;
    int i = 0;
    double result = resultAnalis(input,i,  error);
    if (!error)
        cout << "Результат: " << result << endl;
    if (error) {
        cout << "Ошибка в выражении" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    cout << "Калькулятор" << endl;
    runAnalis();
}