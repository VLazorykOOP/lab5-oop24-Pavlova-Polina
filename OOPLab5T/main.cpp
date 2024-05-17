#include <iostream>
#include <string>

using namespace std;

class Car {
protected:
    string brand;
    int cylinders;
    int power;

public:
    Car(const string& brand, int cylinders, int power)
        : brand(brand), cylinders(cylinders), power(power) {}

    void setBrand(const string& newBrand) {
        brand = newBrand;
    }

    void setPower(int newPower) {
        power = newPower;
    }

    virtual void display() const {
        cout << "Brand: " << brand << ", Cylinders: " << cylinders
            << ", Power: " << power << "hp" << endl;
    }
};

class Lorry : public Car {
private:
    int payloadCapacity; // вантажопідйомність кузова

public:
    Lorry(const string& brand, int cylinders, int power, int payloadCapacity)
        : Car(brand, cylinders, power), payloadCapacity(payloadCapacity) {}

    void setPayloadCapacity(int newCapacity) {
        payloadCapacity = newCapacity;
    }

    void display() const override {
        cout << "Brand: " << brand << ", Cylinders: " << cylinders
            << ", Power: " << power << "hp, Payload Capacity: " << payloadCapacity << "kg" << endl;
    }
};
class Button {
private:
    int size;

public:
    Button(int buttonSize) : size(buttonSize) {}

    int getSize() const {
        return size;
    }

    void setSize(int newSize) {
        size = newSize;
    }
};

class Window {
private:
    int xCoord;
    int yCoord;
    Button button;

public:
    Window(int x, int y, int buttonSize)
        : xCoord(x), yCoord(y), button(buttonSize) {}

    int getXCoord() const {
        return xCoord;
    }

    int getYCoord() const {
        return yCoord;
    }

    const Button& getButton() const {
        return button;
    }

    void setButtonSize(int newSize) {
        button.setSize(newSize);
    }

    ~Window() {
        cout << "Window destroyed." << endl;
    }
};

class MenuWindow : public Window {
private:
    string* menuText;

public:
    MenuWindow(int x, int y, int buttonSize, const string& text)
        : Window(x, y, buttonSize), menuText(new string(text)) {}

    void printMenuText() const {
        if (menuText != nullptr) {
            cout << "Menu Text: " << *menuText << endl;
        }
    }

    ~MenuWindow() {
        delete menuText; // Release memory allocated for menuText
        cout << "MenuWindow destroyed." << endl;
    }
};
class Person {
protected:
    string name;
    int age;

public:
    Person(const string& name, int age) : name(name), age(age) {}

    // Конструктор копіювання
    Person(const Person& other) : name(other.name), age(other.age) {}

    // Оператор присвоювання
    Person& operator=(const Person& other) {
        if (this != &other) {
            name = other.name;
            age = other.age;
        }
        return *this;
    }

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age;
    }

    friend ostream& operator<<(ostream& os, const Person& person) {
        os << "Name: " << person.name << ", Age: " << person.age;
        return os;
    }

    friend istream& operator>>(istream& is, Person& person) {
        cout << "Enter name: ";
        is >> person.name;
        cout << "Enter age: ";
        is >> person.age;
        return is;
    }
};

class Student : public Person {
private:
    string university;

public:
    Student(const string& name, int age, const string& university)
        : Person(name, age), university(university) {}

    // Конструктор копіювання
    Student(const Student& other) : Person(other), university(other.university) {}

    // Оператор присвоювання
    Student& operator=(const Student& other) {
        if (this != &other) {
            Person::operator=(other);
            university = other.university;
        }
        return *this;
    }

    void display() const override {
        Person::display();
        cout << ", University: " << university;
    }

    friend ostream& operator<<(ostream& os, const Student& student) {
        os << static_cast<const Person&>(student);
        os << ", University: " << student.university;
        return os;
    }

    friend istream& operator>>(istream& is, Student& student) {
        is >> static_cast<Person&>(student);
        cout << "Enter university: ";
        is >> student.university;
        return is;
    }
};

int main() {
    Car myCar("Toyota", 4, 150);
    myCar.display();

    Lorry myLorry("Volvo", 6, 300, 5000);
    myLorry.display();

    myLorry.setBrand("MAN");
    myLorry.setPayloadCapacity(7000);

    cout << "\nUpdated Lorry Details:\n";
    myLorry.display();
    MenuWindow menu(100, 50, 20, "File");
    cout << "Window coordinates: (" << menu.getXCoord() << ", " << menu.getYCoord() << ")" << endl;
    cout << "Button size: " << menu.getButton().getSize() << endl;
    menu.printMenuText();

    // Change button size
    menu.setButtonSize(25);
    cout << "Updated Button size: " << menu.getButton().getSize() << endl;

    Person person("John Doe", 25);
    cout << "Person Info: " << person << endl;

    Person newPerson("", 0);
    cout << "Enter Person's info:\n";
    cin >> newPerson;
    cout << "New Person Info: " << newPerson << endl;

    Student student("Alice Smith", 20, "University of ABC");
    cout << "Student Info: " << student << endl;

    Student newStudent("", 0, "");
    cout << "Enter Student's info:\n";
    cin >> newStudent;
    cout << "New Student Info: " << newStudent << endl;

    return 0;

}
