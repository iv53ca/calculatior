#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map"
#include "Qtime"
#include "Qtimer"

std::string input;
std::vector<std::string> vars;
std::vector<std::string> varn;
bool bigger_prior(std::string one, std::string two) {
    int fir = 0;
    int sec = 0;
    if (one == "*"||one == "/") {
        fir = 1;
    }
    if (one == "^") {
        fir = 2;
    }
    if (two == "*"||two == "/") {
        sec = 1;
    }
    if (two == "^") {
        sec = 2;
    }
    if (one == "sin"||one == "cos"||one == "tg"||one == "ctg"||one == "log") {
        fir = 3;
    }
    if (two == "sin"||two == "cos"||two == "tg"||two == "ctg"||two == "log") {
        sec = 3;
    }
    if (two == "(") {
        sec = -1;
    }
    if (one == "(") {
        fir = -1;
    }
    if (two == "[") {
        sec = -1;
    }
    if (one == "]") {
        fir = -1;
    }
    return (fir <= sec);
}

bool is_double(std::string str) {
    for (int i =0;i < str.length();++i) {
        if (str[i] == '.') {
            return true;
        }
    }
    return false;
}

double str_to_double(std::string str) {
    double ans = 0;
    int i = 0;
    if (str[0] == '-') {
        ++i;
    }
    while (str[i] != '.' && str.length() > i) {
        ans = ans * 10 + str[i] - '0';
        ++i;
    }
    if (str[i] == '.') {
        ++i;
    }
    double t = 10;
    while (str.length() > i) {
        ans += (str[i] - '0') / t;
        t *= 10;
        ++i;
    }
    if (str[0] == '-') {
        return -ans;
    }
    return ans;
}

std::string double_to_str(double d) {
    std::ostringstream strm;
    strm << d;
    return strm.str();
}

std::string count_everything(std::string str) {
    int c = 0;
    std::stack<std::string> stack;
    std::string number;
    std::stack<std::string> ans;
    while (c < str.length()) {
        if (str[c] == '+') {
            c++;
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            while (!stack.empty()&&bigger_prior("+", stack.top())) {
                ans.push(stack.top());
                stack.pop();
            }
            stack.push("+");
        } else if (str[c] == '-') {
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            while (!stack.empty()&&bigger_prior("-", stack.top())) {
                ans.push(stack.top());
                stack.pop();
            }
            stack.push("-");

            c++;
        } else if (str[c] == '*') {
            c++;
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            while (!stack.empty()&&bigger_prior("*", stack.top())) {
                ans.push(stack.top());
                stack.pop();
            }
            stack.push("*");

        } else if (str[c] == '/') {
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            while (!stack.empty()&&bigger_prior("/", stack.top())) {
                ans.push(stack.top());
                stack.pop();
            }
            stack.push("/");

            c++;
        } else if (str[c] == '^') {
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            while (!stack.empty()&&bigger_prior("^", stack.top())) {
                ans.push(stack.top());
                stack.pop();
            }
            stack.push("^");

            c++;
        } else if (str[c] == '(') {
            c++;
            stack.push("(");
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
        } else if (str[c] == ')') {
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            if (stack.empty()) {
                return "wrong bracket sequence";
            }
            while(stack.top() != "(" && !stack.empty()) {
                if (stack.top() == "[" || stack.top() == "]") {
                    return "wrong bracket sequence";
                }
                ans.push(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                return "wrong bracket sequence";
            }
            stack.pop();

            c++;
        } else if (str[c] == '[') {
            c++;
            stack.push("[");
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
        } else if (str[c] == ']') {
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
            if (stack.empty()) {
                return "wrong bracket sequence";
            }
            while(stack.top() != "[" && !stack.empty()) {
                if (stack.top() == "(" || stack.top() == ")") {
                    return "wrong bracket sequence";
                }
                ans.push(stack.top());
                stack.pop();
            }
            if (stack.empty()) {
                return "wrong bracket sequence";
            }
            stack.pop();

            c++;
        } else if (str[c] == ' '||str[c] == ',') {
            c++;
            if (number.length() > 0) {
                ans.push(number);
                number.clear();
            }
        } else if (str[c] == 'c') {
            if (c + 2 < str.length()){
                if (str[c + 1] == 't' && str[c + 2] == 'g') {
                    if (number.length() > 0) {
                        ans.push(number);
                        number.clear();
                    }
                    while (!stack.empty()&&bigger_prior("ctg", stack.top())) {
                        ans.push(stack.top());
                        stack.pop();
                    }
                    stack.push("ctg");
                    c += 2;
                    c++;
                } else if (str[c + 1] == 'o' && str[c + 2] == 's') {
                    if (number.length() > 0) {
                        ans.push(number);
                        number.clear();
                    }
                    while (!stack.empty()&&bigger_prior("cos", stack.top())) {
                        ans.push(stack.top());
                        stack.pop();
                    }
                    stack.push("cos");
                    c += 2;
                    c++;
                } else {
                    number += str[c];
                    c++;
                }
            } else {
                number += str[c];
                c++;
            }

    } else if (str[c] == 'l') {
            if (c + 2 < str.length()){
                if (str[c + 1] == 'o' && str[c + 2] == 'g') {
                    if (number.length() > 0) {
                        ans.push(number);
                        number.clear();
                    }
                    while (!stack.empty()&&bigger_prior("log", stack.top())) {
                        ans.push(stack.top());
                        stack.pop();
                    }
                    stack.push("log");
                    c += 2;
                    c++;
                } else {
                    number += str[c];
                    c++;
                }
            } else {
                number += str[c];
                c++;
            }
    } else if (str[c] == 's') {
            if (c + 2 < str.length()){
                if (str[c + 1] == 'i' && str[c + 2] == 'n') {
                    if (number.length() > 0) {
                        ans.push(number);
                        number.clear();
                    }
                    while (!stack.empty()&&bigger_prior("sin", stack.top())) {
                        ans.push(stack.top());
                        stack.pop();
                    }
                    stack.push("sin");
                    c += 2;
                    c++;
                } else {
                    number += str[c];
                    c++;
                }
            } else {
                number += str[c];
                c++;
            }
    } else if (str[c] == 't') {
            if (c + 1 < str.length()){
                if (str[c + 1] == 'g') {
                    if (number.length() > 0) {
                        ans.push(number);
                        number.clear();
                    }
                    while (!stack.empty()&&bigger_prior("tg", stack.top())) {
                        ans.push(stack.top());
                        stack.pop();
                    }
                    stack.push("tg");
                    c += 1;
                    c++;
                } else {
                    number += str[c];
                    c++;
                }
            } else {
                number += str[c];
                c++;
            }
        } else {
            number += str[c];
            c++;
        }
    }
    if (number.length() != 0) {
        ans.push(number);
    }
    while (!stack.empty()) {
        if (stack.top() == "(" || stack.top() == ")" || stack.top() == "[" || stack.top() == "]") {
            return "wrong bracket sequence";
        }
        ans.push(stack.top());
        stack.pop();
    }
    std::stack<std::string> t;
    while (!ans.empty()) {
        t.push(ans.top());
        ans.pop();
    }
    ans = t;

    while (!ans.empty()) {
        if (ans.top() == "+") {
            ans.pop();
            if (stack.empty()) return "expected expression";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "expected expression";
            std::string sec = stack.top();
            stack.pop();
            if ((fir.length() < 20 && sec.length() < 20)||(is_double(fir) || is_double(sec))) {
                double one = str_to_double(fir);
                double two = str_to_double(sec);
                stack.push(double_to_str(one + two));
            } else {
                num one;
                one.input(fir);
                num two;
                two.input(sec);
                stack.push((one + two).output());
            }
        } else if (ans.top() == "-") {
            ans.pop();
            if (stack.empty()) return "expected expression";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "expected expression";
            std::string sec = stack.top();
            stack.pop();
            if ((fir.length() < 20 && sec.length() < 20)||(is_double(fir) || is_double(sec))) {
                double one = str_to_double(fir);
                double two = str_to_double(sec);
                stack.push(double_to_str(two - one));
            } else {
                num one;
                one.input(fir);
                num two;
                two.input(sec);
                stack.push((two - one).output());
            }
        } else if (ans.top() == "*") {
            ans.pop();
            if (stack.empty()) return "expected expression";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "expected expression";
            std::string sec = stack.top();
            stack.pop();
            if ((fir.length() < 20 && sec.length() < 20)||(is_double(fir) || is_double(sec))) {
                double one = str_to_double(fir);
                double two = str_to_double(sec);
                stack.push(double_to_str(one * two));
            } else {
                num one;
                one.input(fir);
                num two;
                two.input(sec);
                stack.push((one * two).output());
            }
        } else if (ans.top() == "/") {
            ans.pop();
            if (stack.empty()) return "expected expression";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "expected expression";
            std::string sec = stack.top();
            stack.pop();
            if ((fir.length() < 20 && sec.length() < 20)||(is_double(fir) || is_double(sec))) {
                double one = str_to_double(fir);
                double two = str_to_double(sec);
                if (one == 0 || two == 0) return "division by zero";
                stack.push(double_to_str(two / one));
            }
        } else if (ans.top() == "^") {
            ans.pop();
            if (stack.empty()) return "expected expression";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "expected expression";
            std::string sec = stack.top();
            stack.pop();
            if ((fir.length() < 20 && sec.length() < 20)||(is_double(fir) || is_double(sec))) {
                double one = str_to_double(fir);
                double two = str_to_double(sec);
                stack.push(double_to_str(pow(two, one)));
            } else {
                num one;
                one.input(fir);
                num two;
                two.input(sec);
                stack.push((two ^ one).output());
            }
        } else if (ans.top() == "sin") {
            ans.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string fir = stack.top();
            stack.pop();
            if (fir.length() < 20||is_double(fir)) {
                double one = str_to_double(fir);
                stack.push(double_to_str(sin(one)));
            }
        } else if (ans.top() == "cos") {
            ans.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string fir = stack.top();
            stack.pop();
            if (fir.length() < 20||is_double(fir)) {
                double one = str_to_double(fir);
                stack.push(double_to_str(cos(one)));
            }
        } else if (ans.top() == "tg") {
            ans.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string fir = stack.top();
            stack.pop();
            if (fir.length() < 20||is_double(fir)) {
                double one = str_to_double(fir);
                stack.push(double_to_str(sin(one) / cos(one)));
            }
        } else if (ans.top() == "ctg") {
            ans.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string fir = stack.top();
            stack.pop();
            if (fir.length() < 20||is_double(fir)) {
                double one = str_to_double(fir);
                stack.push(double_to_str(cos(one) / sin(one)));
            }
        } else if (ans.top() == "log") {
            ans.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string fir = stack.top();
            stack.pop();
            if (stack.empty()) return "invalid number of arguments";
            std::string sec = stack.top();
            stack.pop();
            double one = str_to_double(fir);
            double two = str_to_double(sec);
            if (one <= 0 || two <= 0 || one == 1) return "not a number";
            stack.push(double_to_str(log(one) / log(two)));
        } else {
            bool gosha_lox = true;
            for (size_t i = 0; i < vars.size();++i) {
                if (vars[i] == ans.top()) {
                    stack.push(varn[i]);
                    gosha_lox = false;
                    break;
                }
            }
            if (gosha_lox) {
                stack.push(ans.top());
            }
            ans.pop();
        }
    }
    if ( stack.empty()) {
        return "type incongruity";
    }
    std::string answer = stack.top();
    stack.pop();
    if (!stack.empty()) return "wrong expression";
    return answer;
}

void MainWindow::varchange() {
    for(int i = 0;i < ui->tableWidget->rowCount();++i) {
        varn[i] = ui->tableWidget->item(i + 1,0)->text().toStdString();
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}

bool var_is_var(std::string str) {
    if (str == "log" || str == "sin" || str == "cos" || str == "tg" || str == "ctg") {
        return false;
    }
    for (size_t i = 0; i < str.size();++i) {
        if (str[i] == '.') return false;
    }
    if (str[0] >= 0 && str[0] <= '9') return false;
    return true;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    input = ui->lineEdit->text().toStdString();
    vars.clear();
    varn.clear();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    ui->tableWidget->insertColumn(ui->tableWidget->columnCount());
    int c = 0;
    std::string var;
    for (size_t i = 0;i < input.size();++i) {
        if ((input[i] <= '9'&&input[i] >= '0')||(input[i] <= 'Z'&&input[i] >= 'A')||(input[i] >= 'a'&&input[i] <= 'z')||input[i] == '.') {
            var.push_back(input[i]);
        } else {
            if (var_is_var(var)) {
                QString str;
                for (int i = 0;i < var.size();++i) {
                    str[i] = var[i];
                }
                bool s = true;
                for (size_t i = 0;i < vars.size();++i) {
                    if (vars[i] == var) {
                        s = false;
                    }
                }
                if (s) {
                    vars.push_back(var);
                    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(str));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("0"));
                    varn.push_back("0");

                }
            }
            var.clear();
        }
    }
    if (var_is_var(var)) {

        QString str;
        for (int i = 0;i < var.size();++i) {
            str[i] = var[i];
        }
        bool s = true;
        for (size_t i = 0;i < vars.size();++i) {
            if (vars[i] == var) {
                s = false;
            }
        }
        if (s) {
            vars.push_back(var);
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(str));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem("0"));
            varn.push_back("0");
            var.clear();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    std::string str2;
    str2 = count_everything(input);
    for(int i = 0;i < str2.length();++i) {
        str += str2[i];
    }
    ui->label->setText(str);
}


