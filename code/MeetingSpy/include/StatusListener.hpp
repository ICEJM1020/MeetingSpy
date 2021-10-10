#pragma once

#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <mutex>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/filesystem.hpp>
#include <boost/timer/timer.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

#include "ProcessStatusListener.h"

using namespace affdex;

class StatusListener : public ProcessStatusListener
{
public:
    
    StatusListener():mIsRunning(true) {};
    
    void onProcessingException(AffdexException ex)
    {
        std::cerr << "Encountered an exception while processing: " << ex.what() << std::endl;
        m.lock();
        mIsRunning = false;
        m.unlock();
    };
    
    void onProcessingFinished()
    {
        std::cerr << "Processing finished successfully" << std::endl;
        m.lock();
        mIsRunning = false;
        m.unlock();
        
    };
    
    bool isRunning()
    {
        bool ret = true;
        m.lock();
        ret = mIsRunning;
        m.unlock();
        return ret;
    };
    
private:
    std::mutex m;
    bool mIsRunning;
    
};
