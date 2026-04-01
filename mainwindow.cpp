#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
     ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    SetText("0");

    connect(ui->tb_zero, &QPushButton::clicked, this, [this]() {AddText("0");});
    connect(ui->tb_one, &QPushButton::clicked, this, [this]() {AddText("1");});
    connect(ui->tb_two, &QPushButton::clicked, this, [this]() {AddText("2");});
    connect(ui->tb_three, &QPushButton::clicked, this, [this]() {AddText("3");});
    connect(ui->tb_four, &QPushButton::clicked, this, [this]() {AddText("4");});
    connect(ui->tb_five, &QPushButton::clicked, this, [this]() {AddText("5");});
    connect(ui->tb_six, &QPushButton::clicked, this, [this]() {AddText("6");});
    connect(ui->tb_seven, &QPushButton::clicked, this, [this]() {AddText("7");});
    connect(ui->tb_eight, &QPushButton::clicked, this, [this]() {AddText("8");});
    connect(ui->tb_nine, &QPushButton::clicked, this, [this]() {AddText("9");});

    connect(ui->tb_comma, &QPushButton::clicked, this, [this]() {AddText(".");});
    connect(ui->tb_negate, &QPushButton::clicked, this, [this]() {Negate();});
    connect(ui->tb_backspace, &QPushButton::clicked, this, [this]() {Backspace();});

    connect(ui->tb_add, &QPushButton::clicked, this, [this]() {SetOperation(Operation::ADDITION);});
    connect(ui->tb_substract, &QPushButton::clicked, this, [this]() {SetOperation(Operation::SUBTRACTION);});
    connect(ui->tb_multiplicate, &QPushButton::clicked, this, [this]() {SetOperation(Operation::MULTIPLICATION);});
    connect(ui->tb_divide, &QPushButton::clicked, this, [this]() {SetOperation(Operation::DIVISION);});
    connect(ui->tb_power, &QPushButton::clicked, this, [this]() {SetOperation(Operation::POWER);});
    connect(ui->tb_equal, &QPushButton::clicked, this, [this]() {ShowRes();});
    connect(ui->tb_reset, &QPushButton::clicked, this, [this]() {Clear();});
    
    connect(ui->tb_ms, &QPushButton::clicked, this, [this]() {MemSave();});
    connect(ui->tb_mc, &QPushButton::clicked, this, [this]() {MemClear();});
    connect(ui->tb_mr, &QPushButton::clicked, this, [this]() {MemGet();});
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetText(const QString& text) {
    input_number_ = RemoveTrailingZeroes(text); //add
    input_number_ = NormalizeNumber(input_number_);//add
    ui->l_result->setText(input_number_);
    active_number_ = input_number_.toDouble();
}

void MainWindow::AddText(const QString& suffix) {
    // QString text = ui->l_result->text();
    // text += suffix;
    input_number_ += suffix;
    //input_number_ = NormalizeNumber(text);
    SetText(input_number_);
}

void MainWindow::Negate() {
    if (input_number_.startsWith("-")) {
        input_number_ = input_number_.mid(1); //add
    }
    else {
        input_number_ = "-" + input_number_;
    }
    //input_number_ = NormalizeNumber(input_number_);
    SetText(input_number_);
}

void MainWindow::Backspace() {
    if(input_number_.size()>0) {
        input_number_.chop(1);
    }
    //input_number_ = NormalizeNumber(input_number_);
    SetText(input_number_);
}

void MainWindow::SetOperation(Operation op) {
    if(current_operation_ == Operation::NO_OPERATION) { //current_operation вместо op
        calculator_.Set(active_number_);
    }
    current_operation_ = op;
    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + OpToString(current_operation_));
    input_number_ = "";
}

void MainWindow::ShowRes() {
    if(current_operation_ != Operation::NO_OPERATION) {
        ui->l_formula->setText(QString::number(calculator_.GetNumber()) + OpToString(current_operation_) + QString::number(active_number_) + " ="); //add пробел у =
        switch(current_operation_) {
        case Operation::ADDITION: calculator_.Add(active_number_); break; //add_break
        case Operation::DIVISION: calculator_.Div(active_number_); break; //add_break
        case Operation::MULTIPLICATION: calculator_.Mul(active_number_); break; //add_break
        case Operation::SUBTRACTION: calculator_.Sub(active_number_); break; //add_break
        case Operation::POWER: calculator_.Pow(active_number_); break; //add_break
        }
    }

    active_number_ = calculator_.GetNumber();
    ui->l_result->setText(QString::number(active_number_));
    input_number_ = "";
    //SetOperation(Operation::NO_OPERATION);
    current_operation_ = Operation::NO_OPERATION; //add
}

void MainWindow::Clear() {
    SetOperation(Operation::NO_OPERATION);
    ui->l_formula->setText("");
    SetText("0");
}

void MainWindow::MemSave() {
    memory_ = active_number_;
    has_mem_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::MemGet() {
    if(!has_mem_) {
        return;
    }
    
    active_number_ = memory_;
    ui->l_result->setText(QString::number(memory_));
    input_number_ = "";
}

void MainWindow::MemClear() {
    has_mem_ = false;
    ui->l_memory->setText("");
}
