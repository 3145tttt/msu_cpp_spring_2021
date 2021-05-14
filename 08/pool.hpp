#pragma once

#include <thread>
#include <pthread.h>
#include <future>
#include <queue>
#include <vector>
#include <functional>
#include <iostream>

class ThreadPool
{
	bool stop = false;
	std::mutex m;
	std::vector <std::thread> threads;
	std::queue <std::function<void()>> tasks;
	std::condition_variable condition; 

public:
   	explicit ThreadPool(size_t poolSize = std::thread::hardware_concurrency()){
    	for( size_t i = 0; i < poolSize; ++i ){
    		threads.emplace_back(
    			[this]() {
    				while(1) {
		   				std::unique_lock <std::mutex> lock(m);
			           	this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;				            
				        auto task = tasks.front();
				        tasks.pop();
				        task();
			        }
		    	}
		   	 );
    		}
    	}
    

    	~ThreadPool(){

    		{
                std::unique_lock<std::mutex> lock(m);
                stop = true;
            }
	    	condition.notify_all();
    		for( auto &thr: threads )
    			thr.join();    	
    	}


	template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))> {
    	auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
           	(std::bind(func, args...));
        {
            std::unique_lock<std::mutex> lock(m);

            if(stop)
                std::cout << "DEBUG: thread execute" << std::endl;

            tasks.emplace([task](){ (*task)(); });
        }
        condition.notify_one();
        return task->get_future();
    }
};