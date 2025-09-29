#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
 
int main()
{
     std::cout << "Main thread id=" << std::this_thread::get_id() << "\n";
    auto asyncDefault = std::async([]() //поток зависит от имплементации
    {
        std::cout << "Async default, Threadid=" <<
            std::this_thread::get_id() << "\n";
    });
 //отложенный async. Выполняется в main-потоке
    auto asyncDeffered= std::async(std::launch::deferred,
        [](const std::string& str)
    {
        std::cout << "Async deffer, Threadid="
            << std::this_thread::get_id() << "," << str << "\n";
    }, std::string("end string")); //async с параметром, который передаем лямбде

 //"истинный" async - выполняется в новом потоке, возможно создаваемом для этого
    auto trueAsync = std::async(std::launch::async, []()
    {
        std::cout << "True async, Threadid="
            << std::this_thread::get_id() << "\n";
    });
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Sleep ended\n";
    asyncDefault.get();
    asyncDeffered.get();
    trueAsync.get();
}

//Main thread id=140198788257600
//Async default, Threadid=140198769891072
//True async, Threadid=140198761498368
//Sleep ended
//Async deffer, Threadid=140198788257600,end string