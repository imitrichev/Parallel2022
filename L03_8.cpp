#include <iostream>
#include <future>
using namespace std;
std::future<bool> doWork(const std::string& msg)
{
    auto handle = [](const std::string& msg4) -> bool
    {
        std::cout << "Handle the submitted form: " << msg4 << "\n";
        return true;
    };
    std::packaged_task<bool(const std::string&)> task(handle);
    auto future = task.get_future();
    std::thread thread(std::move(task), msg);
    thread.detach();
    return std::move(future);
}
 
int main()
{
    auto check = doWork("Example");
    if(check.get())
        std::cout << "Finished\n";
    else
        std::cout << "Not\n";
    return 0;
}