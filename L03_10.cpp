#include <future>
#include <thread>
#include <limits>
 
int main() // угадай число в потоке
{
    auto spPromise = std::make_shared<std::promise<void>>(); //promise можно как и future только move, но к нему надо иметь доступ и в главном потоке, и в лямбде (которая возвращает значение, а не promise - поэтому делаем shared pointer и передаем его как параметр в лямбду)
    std::future<void> waiter = spPromise->get_future();
    auto call = [spPromise](size_t value)
    {
        size_t i = std::numeric_limits<size_t>::max();
        while(i--)
        {
            if(i == value) //угадали число
                spPromise->set_value();
        }
    };
    std::thread thread(call, std::numeric_limits<size_t>::max() - 500000); //загадываем макс.число минус 500000
    thread.detach();
    waiter.get(); //здесь ожидаем выполнения обещания 
}