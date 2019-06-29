#ifndef LOGGER_H
#define LOGGER_H
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

class Logger{
public:
	Logger(const char *fileName) 
	: out_(fileName, std::ios::out | std::ios::app | std::ios::binary){
		PrintCurTime();
	}

	~Logger(){
		out_.close();
	}
	
	Logger(const Logger&) = delete;	
	Logger& operator=(const Logger&) = delete;
	
	template<typename T>
	Logger& operator<<(const T &rhs){
		out_ << rhs;
		return *this;
	}
public:
	//记录日志
	void log(const char *info){
		assert(info != nullptr);
		out_ << "	" << info << std::endl << std::endl; 
	}
	//~
	void log(const std::string &info){
		out_ << "	" << info << std::endl << std::endl;
	}

	//刷新缓存区
	void flush(){
		out_.flush();
	}

private:
	//输入当前时间
	inline void PrintCurTime(){
		static time_t time_ = std::time(nullptr);
		out_ << "-->" << std::ctime(&time_);
	}
	
	std::ofstream out_;
};

#endif
