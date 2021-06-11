#include <map>
#include <string>
#include <functional>
#include <memory>
#include <iostream>

class Message{
public:
    virtual ~Message() {}
    virtual void foo() {}
};
 
class Message1 : public Message{
public:
    Message1(): a_(0){
        std::cout << "message1" << std::endl;
    }
 
    Message1(int a): a_(a){
        std::cout << "message1 int: " << a << std::endl;
    }
 
    ~Message1(){}
 
    void foo() override {
        std::cout << "message1 and a_: " << a_ << std::endl;
    }
    int a_;
};

class Message2 : public Message{
public:
    Message2() {
        std::cout << "message2" << std::endl;
    }
    Message2(int a)  {
        std::cout << "message2 int: " << a << std::endl;
    }
 
    ~Message2(){}
 
    void foo() override {
        std::cout << "message2" << std::endl;
    }
};
 
 
class factory{
public:
    template<typename T>
    struct register_t  {
        register_t(const std::string& key) {
            factory::get().map_.emplace(key, [] { return new T(); });
        }
 
 
        template<typename... Args>
        register_t(const std::string& key, Args... args)  {
            //factory::get().map_.emplace(key, [&] { return new T(args...); });
            factory::get().map_.emplace(key, [args...] { return new T(args...); });
        }
    };
 
    static Message* produce(const std::string& key) {
        if (map_.find(key) == map_.end())
            throw std::invalid_argument("the message key is not exist!"); 
        return map_[key]();
    }
 
 
    static std::unique_ptr<Message> produce_unique(const std::string& key) {
        return std::unique_ptr<Message>(produce(key));
    }
 
 
    static std::shared_ptr<Message> produce_shared(const std::string& key) {
        return std::shared_ptr<Message>(produce(key));
    }
 
private:
    factory() {};
    factory(const factory&) = delete;
    factory(factory&&) = delete;
 
    static factory& get() {
        static factory instance;
        return instance;
    }
 
    static std::map<std::string, std::function<Message*()>> map_;
};
 
std::map<std::string, std::function<Message*()>> factory::map_;
// #define REGISTER_MESSAGE_VNAME(T) reg_msg_##T##_
// #define REGISTER_MESSAGE(T, key, ...) static factory::register_t<T> REGISTER_MESSAGE_VNAME(T)(key, ##__VA_ARGS__)
#define REGISTER_MESSAGE(T, key, ...) static factory::register_t<T> reg_msg_##T##_(key, ##__VA_ARGS__)

REGISTER_MESSAGE(Message1, "message1", 3);//this should move to the message class if there are multiple file;
REGISTER_MESSAGE(Message2, "message2"); 

// static factory::register_t<Message1> reg_msg_Message1_("message1", 3);
// static factory::register_t<Message2> reg_msg_Message2_("message2");


int main() {
    Message* p = factory::produce("message1");
    p->foo();   //Message1 
 
    delete p;  
    auto p2 = factory::produce_unique("message2");
    p2->foo();
}