
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>

using namespace std; 

double applyOp(char op, double b, double a, bool& error) {
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


bool isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;

}

bool simplIdentif(const string& currentString, int& position, bool& isError, vector<string>& identificator) {
    string number;

    //проверка - строка не закончилась и проверяеый символ - буква
    while (position < currentString.size() && isDigit(currentString[position])) {
        number += currentString[position];
        position++;
    }
    if (!number.empty())
    {
        identificator.push_back(number);
        return true;
    }
    //обработка ошибок
    isError = true;
    position++;
    return false;
}

bool operatorSign(const string& currentString, int& position, bool& isError)
{
    //проверка - строка не закончилась и проверяеый символ - оператор
    if (position < currentString.size() && (currentString[position] == '+' || currentString[position] == '-' || currentString[position] == '*' || currentString[position] == '/' || currentString[position] == '#' || currentString[position] == ' '))
    {
        position++;
        return true;
    }
    //обработка ошибок
    isError = true;
    position++;
    return false;
}

bool simplExpression(const string& currentString, int& position, bool& isError, vector<string>& identificator, vector<string>& expression) {
    //проверка на пустую строку
    if (currentString.empty()) {
        cout << "Ошибка: у вас пустая строка" << endl;
        isError = true;
        return false;
    }

    bool result = simplIdentif(currentString, position, isError, identificator);
    bool flag = true;
    string currentExpression;

    while (position < currentString.size()) {
        //проверка ожидания и корректности оператора
        if (flag) {
            result &= operatorSign(currentString, position, isError);
            flag = false;
        }
        else {
            //проверка ожидания и корректности простого идентификатора
            result &= simplIdentif(currentString, position, isError, identificator);
            flag = true;

            //формирование простых выражений
            if (identificator.size() >= 2) {
                currentExpression = identificator[identificator.size() - 2] + currentString[position - 2] + identificator[identificator.size() - 1];
                expression.push_back(currentExpression);
            }
        }
    }
    return result;
}

bool Analis(const string& currentString, int& position, bool& isError, vector<string>& identificator, vector<string>& expression) {
    return simplExpression(currentString, position, isError, identificator, expression);
}

void runAnalis() {
    int position = 0;
    bool isError = true;
    string currentString;
    vector<string> identificator;
    vector<string> expression;

    cout << "Введите выражение:" << endl;

    getline(cin, currentString);

    if (Analis(currentString, position, isError, identificator, expression) && position == currentString.size()) {

        bool error = false;
        double result = 0;

        if (identificator.size() > 0)
            result = stod(identificator[0]);

        for (int i = 1, j = 0; i < identificator.size(); i++, j++)
        {
            char op = currentString[j * 2 + 1];
            double nextOperand = stod(identificator[i]);
            result = applyOp(op, nextOperand, result, error);
            
            if (error)
                break;
        }

        if (!error)
            cout << "Ответ:" << " " << result << endl;
    }
    else {
        cout << "Ошибка в выражении";
    }
}


int main()
{
    setlocale(LC_ALL, "ru");

    cout << "Калькулятор" << endl;
    runAnalis();
}




