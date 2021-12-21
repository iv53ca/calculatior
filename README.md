# calculatior
Калькулятор, работающий на длинной арифметике

В файле main.cpp создается окно в qt (генерируется автоматически при создании проекта в Qt Creator);

В файле mainwindiw.h объявляются функции различных ивентов: 

    void on_lineEdit_textChanged(const QString &arg1); - изменяет поле ввода
    void on_pushButton_clicked(); - нажата кнопка
    void on_tableWidget_cellChanged(int row, int column); - изменена таблица
    
Дальше в файле прописан класс длинного числа: 

    num(); - создаем +0;
    void input(std::string str); - вводит чиселку как строку;
    std::string output(); - возвращает чиселку как строку;
    {bool operator<(num sec);
    bool operator>(num sec);
    bool operator==(num sec;
    bool operator>=(num sec);
    bool operator<=(num sec);} - переопределяют операций; 
    num silly(num A, num B); - умножение маленьких больших чисел чисел;
    num operator*(num sec); - переопределение операции умножения;
    {friend num operator+(num fir, num sec);
    friend num operator^(num fir, num sec);
    friend num operator-(num fir, num sec);} - открывают приватные поля для операции. Может быть вызвана как обычная функция в коде;
    
В файле mainwindow.cpp собственно все и происходит: 

    bool bigger_prior(std::string one, std::string two); - определяет приоритеты операций с введенных строк;
    bool is_double(std::string str); - определяет десятичную дробь;
    double str_to_double(std::string str); - переводит строку в чиселку;
    std::string double_to_str(double d); - переводит чиселку в строку;
    std::string count_everything(std::string str); - считывает выражение, разбивает на строки, переводит в обратную польскую запись и при этом проверяет запись на адекватность
    (проходится по элементам строки, определяя буквы, числеки и их последовательность). Примечение: если число дробное, то оно не может быть большим и log, cos и т.д. написаны
    для маленьких больших чиселок. 
    {MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    {
    ui->setupUi(this);
    }
    MainWindow::~MainWindow()
    {
    delete ui;
    }} - генерируется в qt;
    bool var_is_var(std::string str); - проверка нашли ли мы переменную или что-то еще;
    void MainWindow::on_lineEdit_textChanged(const QString &arg1); - изменение переменных. Есть массив vras с именами и varn со значениями. Функция считает значение, как только строчка ввода изменится;
    void MainWindow::on_pushButton_clicked(); - по нажатию кнопки выдает значение
    
В файле mainwindow.ui прописаны кнопки поля. Qt генерирует этот файл автоматически, когда выставляем кнопки в редакторе. 

    
    
