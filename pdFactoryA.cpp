#include <iostream>
#include <map>
#include <string>
#include <functional>
using namespace std;


class Shoes
{
public:
    virtual ~Shoes() {}
    virtual void Show() = 0;
};


class LiNingShoes : public Shoes
{
public:
    void Show() { cout << "LiNing" << endl; }
};


class AdidasShoes : public Shoes
{
public:
    int data;
    AdidasShoes(int data) :data(data) {}
    void Show() { cout << "Adidas " << data << endl; }
};


struct factory
{
    template<typename T>
    struct register_t
    {
        register_t(string key)
        {
            factory::get().map_.emplace(key, [] { return new T(); });
        }

        template<typename... Args>
        register_t(string key, Args... args)
        {
            factory::get().map_.emplace(key, [args...] { return new T(args...); });
        }
    };

    static Shoes* produce(string key)
    {
        if (map_.find(key) == map_.end())
            throw std::invalid_argument("the key is not exist!");
        return map_[key]();
    }

private:
    factory() {};
    factory(const factory&) = delete;
    factory(factory&&) = delete;
    static factory& get() // 单例工厂
    {
        static factory instance;
        return instance;
    }
    static map<string, function<Shoes* ()>> map_;
};
map<string, function<Shoes* ()>> factory::map_; // 不要忘记初始化私有static


// 以下##__VA_ARGS__表示可省略可变参数宏
#define REGISTER(T, key, ...) static factory::register_t<T> reg_msg_##T##_(key, ##__VA_ARGS__)


// 以下为注册
REGISTER(LiNingShoes, "LiNingShoes");
REGISTER(AdidasShoes, "AdidasShoes", 3);


int main()
{
    Shoes* pLiNingShoes = factory::produce("LiNingShoes");
    pLiNingShoes->Show();

    Shoes* AdidasShoes = factory::produce("AdidasShoes");
    AdidasShoes->Show();
}