fn main() {

    /*-------------------------------------------------------------------------------------*/
    // let - объявление переменной
    // mut - идет после let, делает переменную изменяемой

    // Целые числа (один тип: i32)
    let numberOne = 32;
    let numberThree:i32 = 32;
    let mut numberFour : i32 = 32;

    // Символы (char)
    let charOne = '\n';
    let charTwo:char = '\n';
    let mut charThree : char = '\n';
    
    // Строки (String)
    let strOne = "Hello world!!!";  // Надо будет сделать автоматически String
    let mut strTwo : String = String::new();
    let strThree : String = String::from("Hello world!!!");
    let strFour : String = "Hello\n\t world!!!".to_string();

    // Выражения с использованием локальных переменных
    // Арифметические операции (+, -, *, /)
    // (+=, -=, *=, /=) так же поддерживаются
    let mut a = 0;
    let mut b = 0;
    let mut c = 0;
    c = a + b;
    c = a - b;
    c = a * b;
    c = a / 1;


    // Операции сравнения (>, <, >=, <=, ==, !=) и присваивания (=)
    // Операции сравнения работают для всех используемых типов (i32, char, String)
    // char и String сравниваются по содержимому, а не по ссылке
    /*-----------------------------------------------------------------------------------------------------------*/

    // Одномерный массив (array)
    let mut numbers : [i32; 3];
    let mut strings : [String; 3];
    let mut chars : [char; 3];

    // Инициализация
    numbers = [1, 2, 3];
    let mut newStrings : [String; 2] = ["Hello".to_string(), "world".to_string()];
    let mut arr = ['a', 'b', 'c'];

    // Заполнение массива значениями по умолчанию
    chars = ['q'; 3];

    // Операция доступа к элементу массива ([])
    numbers[0] = numbers[1];

    /*------------------------------------------------------------------------------------------------------------*/

    


}