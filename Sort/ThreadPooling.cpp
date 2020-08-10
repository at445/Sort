/*********************

 *  this is a copy of https://blog.csdn.net/carbon06/article/details/78171588

 *********************/

#include <iostream>
#include "ThreadPooling.h"

ThreadPool::ThreadPool(size_t threads) :
    stop(false),
    maxThread(threads),
    processing_task(0)
{
    for (size_t i = 0; i < maxThread; ++i)
        workers.emplace_back(
            [this]
            {
                for (;;)
                {
                    std::function<void()> task = nullptr;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this]() {
                            return !this->tasks.empty() || this->stop;
                        });
                        if (this->stop) {
                            return;
                        }
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
     
                    }
                    task();

                    this->processing_task--;

                }
            });

}
void ThreadPool::waitTillInsertable(void)
{
    while (processing_task >= 7) {
        std::this_thread::yield();
    }
}

bool ThreadPool::isEmpty(void)
{
    return 0 == tasks.size();
}
void ThreadPool::waitTillFinish(void) {
    while (processing_task > 0) { 
        std::this_thread::yield(); 
    }
}
void ThreadPool::enqueue(const std::function<void()>& task)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);

        // don't allow enqueueing after stopping the pool
        if (stop)
            throw std::runtime_error("enqueue on stopped ThreadPool");
        //waitTillInsertable();
        if (task == nullptr) {
            std::cout << "error here" << std::endl;
        }
        tasks.push(task);
    }
    condition.notify_one();
    processing_task++;
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread& worker : workers)
        worker.join();
}
