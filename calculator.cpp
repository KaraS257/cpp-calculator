#include "calculator.h"

void Calculator::Set(Number n) {
    number_ = n;
}

Number Calculator::GetNumber() const {
    return number_;
}

void Calculator::Add(Number n) {
    number_ += n;
}

void Calculator::Sub(Number n) {
    number_ -= n;
}

void Calculator::Div(Number n) {
    number_ /= n;
}

void Calculator::Mul(Number n) {
    number_ *= n;
}

void Calculator::Pow(Number n) {
    number_ = pow(number_, n);
}

void Calculator::Save() {
    mem_ = number_;
    has_mem_ = true;
}

void Calculator::Load() {
    number_ = mem_;
}

bool Calculator::HasMem() const {
    return has_mem_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}