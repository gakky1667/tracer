#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include "tracer.h"

using namespace SchedViz;

Tracer::Tracer(){
}

Tracer::~Tracer(){
}

void Tracer::setup(){
	system("mount -t debugfs nodev /sys/kernel/debug/");
	Tracer::filter_pid((char*)"11532");
	Tracer::set_tracing_on((char*)"0");
	Tracer::set_trace((char*)"0");
	Tracer::set_events_enable((char*)"1");
	Tracer::set_event((char*)"sched:sched_switch");
	Tracer::set_current_tracer((char*)"function"); 
}

void Tracer::reset(){
	Tracer::set_tracing_on((char*)"0"); 
	Tracer::set_events_enable((char*)"0");
	Tracer::output_log();
	Tracer::filter_pid((char*)""); 
	system("umount /sys/kernel/debug/");
}

void Tracer::set_tracing_on(char *mode){
	std::ofstream _set_tracing_on("/sys/kernel/debug/tracing/tracing_on");
	_set_tracing_on << mode << std::endl;
	if(_set_tracing_on.fail()){
		std::cerr << "open error" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}

void Tracer::set_trace(char *mode){
	std::ofstream _set_trace("/sys/kernel/debug/tracing/trace");
	_set_trace << mode << std::endl;
	if(_set_trace.fail()){
		std::cerr << "open error" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}

void Tracer::set_events_enable(char *mode){
	std::ofstream _set_events_enable("/sys/kernel/debug/tracing/events/enable");
	_set_events_enable << mode << std::endl;
	if(_set_events_enable.fail()){
		std::cerr << "open error" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}

void Tracer::set_current_tracer(char *mode){
	std::ofstream _set_current_tracer("/sys/kernel/debug/tracing/current_tracer");
	_set_current_tracer << mode << std::endl;
	if(_set_current_tracer.fail()){
		std::cerr << "open error" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}

void Tracer::set_event(char *mode){
	std::ofstream _set_event("/sys/kernel/debug/tracing/set_event");
	_set_event << mode << std::endl;
	if(_set_event.fail()){
		std::cerr << "open error" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}

void Tracer::start_ftrace(){
	std::cout << "Trace start " << std::endl; 
	std::ofstream _set_ftrace("/sys/kernel/debug/tracing/tracing_on");
	_set_ftrace << 1 << std::endl; 
}

void Tracer::output_log(){
	std::ifstream _trace_log("/sys/kernel/debug/tracing/trace");
	//std::ifstream _trace_log("/sys/kernel/debug/tracing/trace_pipe"); 
	std::ofstream trace_log("./trace.log", std::ios::out | std::ios::app );
	std::string str;

	std::cout << "Trace finish"<< str << std::endl;

	if(_trace_log.fail()){
		std::cerr << "open error" << std::endl;
 		system("umount /sys/kernel/debug/");
		exit(1);
	}
	while(getline(_trace_log,str))
		trace_log << str << std::endl;

}

void Tracer::filter_pid(char *mode){
	std::ofstream _filter_pid("/sys/kernel/debug/tracing/set_ftrace_pid");
	_filter_pid << mode << std::endl;
	if(_filter_pid.fail()){
		std::cerr << "open error filter" << std::endl;
		system("umount /sys/kernel/debug/");
		exit(1);
	}
}


int main(){
	SchedViz::Tracer tracer;

	tracer.setup();	
	tracer.start_ftrace();
	//tracer.reset();
}

