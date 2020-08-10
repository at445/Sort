/*********************

 *  this is a copy of https://blog.csdn.net/carbon06/article/details/78171588

 *********************/



#include <queue>
#include <thread>         // std::thread
#include <mutex>          // std::mutex
#include <functional>
#include <atomic>
class ThreadPool {

public:
    ThreadPool(size_t threads);
    // add new work item to the pool
    void enqueue(const std::function<void()>& task);
    // wait all the task if finish
    void waitTillFinish(void);
    ~ThreadPool();

private:

    std::vector< std::thread > workers;
    // the task queue
    std::queue< std::function<void()> > tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<int> processing_task;
    int maxThread;
    bool stop;
    void waitTillInsertable(void);
    bool isEmpty(void);
};

using ThreadPoolPtr = std::shared_ptr<ThreadPool>;