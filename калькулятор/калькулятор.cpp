
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>

using namespace std; 


bool isDigit(char ch) {
    if (ch >= '0' && ch <= '9') {
        return true;
    }
    return false;

}

bool simplIdentif(const string& currentString, int& position, bool& isError, vector<string>& identificator) {
    //проверка - строка не закончилась и проверяеый символ - буква
    if (position < currentString.size() && isDigit(currentString[position])) {
        identificator.push_back(string(1, currentString[position]));
        position++;
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

    cout << "Введите выражение для проверки" << endl;
    cin.ignore();
    getline(cin, currentString);
    if (Analis(currentString, position, isError, identificator, expression) && position == currentString.size()) {
        
    }
}



int main()
{
    setlocale(LC_ALL, "ru");

    cout << "Калькулятор";
    

}
