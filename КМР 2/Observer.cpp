// Observer.cpp Спостерігач — це поведінковий патерн проектування, який створює механізм підписки, що дає змогу одним об’єктам стежити й реагувати на події, які відбуваються в інших об’єктах.

#include <iostream>
#include <list>
#include <string>
using namespace std;

class IObserver
{
public:
    virtual void Update(const string& message_from_subject) = 0;

    virtual ~IObserver() {};
};

class ISubject
{
public:
    virtual void Attach(IObserver* observer) = 0;

    virtual void Detach(IObserver* observer) = 0;

    virtual void Notify() = 0;

    virtual ~ISubject() {};
};

class Subject : public ISubject
{
    list<IObserver*> list_observer_;
    string message_;
public:
    void Attach(IObserver* observer) override { list_observer_.push_back(observer); }

    void Detach(IObserver* observer) override { list_observer_.remove(observer); }

    void Notify() override {
        list<IObserver*>::iterator iterator = list_observer_.begin();
        HowManyObserver();
        while (iterator != list_observer_.end()) {
            (*iterator)->Update(message_);
            ++iterator;
        }
    }

    void CreateMessage(string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void HowManyObserver() { cout << "There are " << list_observer_.size() << " observers in the list.\n"; }

    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        cout << "I'm about to do some thing important\n";
    }

    virtual ~Subject() { cout << "Goodbye, I was the Subject.\n"; }
};

class Observer : public IObserver
{
    string message_from_subject_;
    Subject& subject_;
    static int static_number_;
    int number_;
public:
    Observer(Subject& subject) : subject_(subject) {
        this->subject_.Attach(this);
        cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }

    void Update(const string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }

    void RemoveMeFromTheList() {
        subject_.Detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }

    void PrintInfo() { cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n"; }

    virtual ~Observer() { cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n"; }
};

int Observer::static_number_ = 0;

void ClientCode()
{
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList();

    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    ClientCode();

    system("pause");
    return 0;
}