Заканчивается свободное пространство в хранилище (90 %). … Вскоре вы не сможете загружать файлы на Диск, а также получать и отправлять письма в Gmail.Подробнее…
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <algorithm>
#include <QMainWindow>
#include<cmath>
#include "stack"
#include <iostream>
#include <sstream>
#include <QTableWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    //QTimer *time;

public:
    //void varchange();

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
            void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_tableWidget_cellChanged(int row, int column);



    //void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

class num {
public:
    num() {
        number.push_back(0);
        sign = 1;
    }
    void input(std::string str) {
        int k = 0;
        number.clear();
        number.push_back(0);
        for (int i = str.length() - 1;i >= 0;--i) {
            number[k] = str[i] - '0';
            ++k;
            number.push_back(0);
        }
        number.pop_back();
        return;
    }


    std::string output() {
        std::string str;
        if (!sign) {
            str += '-';
        }
        for (int i = number.size() - 1;i >= 0;--i) {
            str += number[i] + '0';
        }
        return str;
    }

    bool operator<(num sec) {
        if (sec.sign != sign) {
            return sec.sign;
        }
        if (sec.number.size() != number.size()) {
            if (sec.number.size() > number.size()) {
                return sec.sign;
            } else {
                return !sec.sign;
            }
        }
        for (int i = number.size() - 1; i >= 0;--i) {
            if (number[i] < sec.number[i]) {
                return sec.sign;
            }
            if (number[i] > sec.number[i]) {
                return !sec.sign;
            }
        }
    }

    bool operator>(num sec) {
        if (sec.sign != sign) {
            return sign;
        }
        if (sec.number.size() != number.size()) {
            if (sec.number.size() < number.size()) {
                return sec.sign;
            } else {
                return !sec.sign;
            }
        }
        for (int i = number.size() - 1; i >= 0;--i) {
            if (number[i] > sec.number[i]) {
                return sec.sign;
            }
            if (number[i] < sec.number[i]) {
                return !sec.sign;
            }
        }
    }

    bool operator==(num sec) {
        if (number.size() != sec.number.size()) {
            return false;
        }
        for (int i = number.size() - 1; i >= 0;++i) {
            if (number[i] != sec.number[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator>=(num sec) {
        return (*this > sec||*this == sec);
    }

    bool operator<=(num sec) {
        return (*this < sec||*this == sec);
    }

    num silly(num A, num B) {
        num result;
        result.number.resize(B.number.size() + A.number.size());
        for (int i = 0;i < B.number.size();++i) {
            for (int j = 0; j < A.number.size();++j) {
                result.number[i + j] += A.number[j] * B.number[i];
            }
        }
        for (int i = 0;i < result.number.size();++i) {
            if (result.number[i] > base && i < result.number.size() - 1) {
                result.number[i + 1] += result.number[i] / base;
                result.number[i] %= base;
            }
            if (result.number[i] > base && i == result.number.size() - 1) {
                result.number.push_back(0);
                result.number[i + 1] += result.number[i] / base;
                result.number[i] %= base;
            }
        }
        result.number.pop_back();
        return result;

    }

    num operator*(int x) {
        int next = 0;
        num a;
        a = *this;
        for (int i = 0;i < a.number.size();++i) {
            a.number[i] *= x;
            a.number[i] += next;
            if (a.number[i] > base) {
                next = a.number[i] / base;
                a.number[i] %= base;
            } else {
                next = 0;
            }
        }
        if (next != 0) {
            a.number.push_back(next);
        }
        return *this;
    }


    num operator*(num sec) {
        return silly(*this, sec);
    }


    friend num operator+(num fir, num sec) {
        if (fir.number.size() < sec.number.size()) {
            std::swap(fir, sec);
        }
        if (fir.number.size() == sec.number.size() && ((fir < sec&&fir.sign)||(fir > sec&&!fir.sign))) {
            std::swap(fir, sec);
        }
        if ((fir.sign && sec.sign)||(!fir.sign && !sec.sign)) {
            for (int i = 0;i < sec.number.size();++i) {
                fir.number[i] += sec.number[i];
                if (fir.number[i] >= fir.base) {
                    if (i < sec.number.size() - 1) {
                        fir.number[i+1]++;
                        fir.number[i] -= fir.base;
                    } else {
                        fir.number.push_back(1);
                        fir.number[i] -= fir.base;
                    }
                }
            }
            return fir;
        }
        for (int i = 0;i < fir.number.size(); i++) {
            fir.number[i] -= sec.number[i];
            if (fir.number[i] < 0) {
                fir.number[i] += fir.base;
                fir.number[i+1]--;
                if (i ==  fir.number.size() - 1 && fir.number[i] == 0) {
                    fir.number.pop_back();
                }
            }
        }
        return fir;
    }
    friend num operator^(num fir, num sec) {
        num zero;
        num one;
        num ans;
        ans.input("1");
        one.input("1");
        while (sec >= zero) {
            sec = sec - one;
            ans = ans * fir;
        }
        return ans;
    }

    friend num operator-(num fir, num sec) {
        sec.sign = ! sec.sign;
        if (fir.number.size() < sec.number.size()) {
            std::swap(fir, sec);
        }
        if (fir.number.size() == sec.number.size() && ((fir < sec&&fir.sign)||(fir > sec&&!fir.sign))) {
            std::swap(fir, sec);
        }
        if ((fir.sign && sec.sign)||(!fir.sign && !sec.sign)) {
            for (int i = 0;i < sec.number.size();++i) {
                fir.number[i] += sec.number[i];
                if (fir.number[i] >= fir.base) {
                    if (i < sec.number.size() - 1) {
                        fir.number[i+1]++;
                        fir.number[i] -= fir.base;
                    } else {
                        fir.number.push_back(1);
                        fir.number[i] -= fir.base;
                    }
                }
            }
            return fir;
        }
        for (int i = 0;i < fir.number.size(); i++) {
            fir.number[i] -= sec.number[i];
            if (fir.number[i] < 0) {
                fir.number[i] += fir.base;
                fir.number[i+1]--;
                if (i ==  fir.number.size() - 1 && fir.number[i] == 0) {
                    fir.number.pop_back();
                }
            }
        }
        return fir;
    }
private:
    std::vector<int> number;
    int base = 100;
    bool sign = 1;
};



#endif // MAINWINDOW_H

