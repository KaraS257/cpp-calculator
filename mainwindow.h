#pragma once

#include "calculator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    enum Operation {
        NO_OPERATION,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER
    };

    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetText(const QString& text);
    void AddText(const QString& suffix);
    void Negate();
    void Backspace();
    void SetOperation(Operation op);
    void ShowRes();
    void Clear();
    
    void MemSave();
    void MemGet();
    void MemClear();

    QString RemoveTrailingZeroes(const QString &text) {
        for (qsizetype i = 0; i < text.size(); ++i) {
            if (text[i] != '0') {
                return text.mid(i);
            }
        }
        return "";
    }

    QString NormalizeNumber(const QString &text) {
        if (text.isEmpty()) {
            return "0";
        }
        if (text.startsWith('.')) {
            // Рекурсивный вызов.
            return NormalizeNumber("0" + text);
        }
        if (text.startsWith('-')) {
            // Рекурсивный вызов.
            return "-" + NormalizeNumber(text.mid(1));
        }
        if (text.startsWith('0') && !text.startsWith("0.")) {
            return NormalizeNumber(RemoveTrailingZeroes(text));
        }
        return text;
    }

    QString OpToString(Operation op) {
        switch(op) {
        case Operation::NO_OPERATION: return "";
        case Operation::ADDITION: return " + "; //add " "
        case Operation::DIVISION: return " ÷ "; //add " "
        case Operation::MULTIPLICATION: return " × "; //add " "
        case Operation::SUBTRACTION: return " − "; //add " "
        case Operation::POWER: return " ^ "; //add " "
        }
    }

private slots:

private:
    Ui::MainWindow* ui;

private:
    Calculator calculator_;
    QString input_number_;
    Number active_number_ = 0;
    Operation current_operation_ = Operation::NO_OPERATION;
    double memory_ = 0;
    bool has_mem_ = false;
};
