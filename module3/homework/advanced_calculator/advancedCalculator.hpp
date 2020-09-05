#pragma once
#include <functional>
#include <map>
#include <regex>

const std::regex formatRegex("^(-?[0-9]+\\.?([0-9]+)?)(?:(?=!)(!)|(?!!)([\\+\\-\\*\\/\\^\\$%!#@&?\\[\\]]?(\\\\)?)(-?[0-9]+\\.?([0-9]+)?))$");

enum class ErrorCode {
    OK,
    BadCharacter,
    BadFormat,
    DivideBy0,
    RootOfNegativeNumber,
    ModuleOfNonIntegerValue
};

class Calculator {
private:
    static double add(double a, double b);
    static double substract(double a, double b);
    static double multiplicate(double a, double b);
    static double divide(double a, double b);
    static double modulo(double a, double b);
    static double factorial(double a, double b = 0);
    static double power(double a, double b);
    static double root(double a, double b);
    ErrorCode validateBadFormat();
    ErrorCode checkAndAssignOperation();
    ErrorCode validateValuesForOperation();
    void cleanInputAndExecuteRegex();
    void getValues();
    char getGroupChar(size_t index);
    double calculate();

    static std::map<char, std::function<double(double, double)>> possibleFunctions_;

    const std::vector<std::function<ErrorCode(Calculator*)>> validators_{
        &Calculator::validateBadFormat,
        &Calculator::checkAndAssignOperation,
        &Calculator::validateValuesForOperation};
    double firstValue_{};
    double secondValue_{};
    char operation_{};
    std::string input_{};
    std::smatch matchedInput_{};
    ErrorCode errorCode_{};

public:
    ErrorCode process(std::string& input, double* out);
};