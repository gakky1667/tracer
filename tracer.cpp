#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include "tracer.h"
#include "string"
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <sstream>

using namespace SchedViz;

Tracer::Tracer() : config_(){
	std::string filename(config_.get_configpath());
	load_config_(filename);
}

Tracer::~Tracer(){}

void Tracer::load_config_(const std::string &filename) {
  std::cout << filename << std::endl;

  try {
    YAML::Node node_list;
    node_list = YAML::LoadFile(filename);

		for (unsigned int i(0); i < node_list.size(); i++) {
      const YAML::Node node_name = node_list[i]["nodename"];
      const YAML::Node node_subtopic = node_list[i]["sub_topic"];
      const YAML::Node node_pubtopic = node_list[i]["pub_topic"];
      
			node_info_t node_info;
      node_info.name = node_name.as<std::string>();

            node_info.v_subtopic.resize(0);
      for (int j(0); (size_t)j < node_subtopic.size(); ++j) {
        node_info.v_subtopic.push_back(node_subtopic[j].as<std::string>());
      }

      node_info.v_pubtopic.resize(0);
      for (int j(0); (size_t)j < node_pubtopic.size(); ++j) {
        node_info.v_pubtopic.push_back(node_pubtopic[j].as<std::string>());
      }

            node_info.pid = get_pid(node_info.name);
      v_node_info_.push_back(node_info);
    }

  } catch (YAML::Exception &e) {
    std::cerr << e.what() << std::endl;
  }
}


unsigned int Tracer::get_pid(std::string name){
	FILE *pid_fp;
	unsigned int pid=0;
	char buf[1024];
	std::string pidof_x = "pidof ";
	pidof_x += name;

	if ((pid_fp=popen(pidof_x.c_str(),"r")) ==NULL)
		exit(1);

	while(fgets(buf, sizeof(buf), pid_fp) != NULL)
    pid = atoi(buf);

	std::cout << name.c_str() << ": " << pid <<std::endl;
	pclose(pid_fp);

	return pid;
}

void Tracer::setup(){
	system("mount -t debugfs nodev /sys/kernel/debug/");
	Tracer::filter_pid(true);
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
	Tracer::filter_pid(false);
	system("umount /sys/kernel/debug/");
	Tracer::extract_period();
}


void Tracer::set_tracing_on(char *mode){
	std::ofstream _set_tracing_on("/sys/kernel/debug/tracing/tracing_on");
	_set_tracing_on << mode << std::endl;
	if(_set_tracing_on.fail()){
		std::cerr << "open error" << std::endl;
    exit(1);
  }
}

void Tracer::set_trace(char *mode){
	std::ofstream _set_trace("/sys/kernel/debug/tracing/trace");
	_set_trace << mode << std::endl;
	if(_set_trace.fail()){
		std::cerr << "open error" << std::endl;
		exit(1);
	}
}

void Tracer::set_events_enable(char *mode){
	std::ofstream _set_events_enable("/sys/kernel/debug/tracing/events/enable");
	_set_events_enable << mode << std::endl;
	if(_set_events_enable.fail()){
		std::cerr << "open error" << std::endl;
		exit(1);
  }
}

void Tracer::set_current_tracer(char *mode){
	std::ofstream _set_current_tracer("/sys/kernel/debug/tracing/current_tracer");
	_set_current_tracer << mode << std::endl;
	if(_set_current_tracer.fail()){
		std::cerr << "open error" << std::endl;
    exit(1);
  }
}

void Tracer::set_event(char *mode){
	std::ofstream _set_event("/sys/kernel/debug/tracing/set_event");
	_set_event << mode << std::endl;
	if(_set_event.fail()){
		std::cerr << "open error" << std::endl;
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
	std::ofstream trace_log("./trace.log");
	std::string str;

	std::cout << "Trace finish"<< str << std::endl;

	while(_trace_log && getline(_trace_log,str))
		trace_log << str << std::endl;

}

void Tracer::filter_pid(bool mode){

	std::ofstream _filter_pid("/sys/kernel/debug/tracing/set_ftrace_pid", std::ios::out | std::ios::app);

	if(_filter_pid.fail()){
		std::cerr << "open error filter" << std::endl;
		exit(1);
	}

	if(mode == false){
		_filter_pid << "" << std::endl;
	}
	else{
		for (int i(0); i < (int)v_node_info_.size(); ++i) {
			_filter_pid << v_node_info_.at(i).pid << std::endl;
		}
  }

}


void Tracer::extract_period(){
	std::vector<std::string> find_prev_pids;
	std::vector<std::string> find_next_pids;
	std::string _prev_pid = "prev_pid=";
	std::string _next_pid = "next_pid=";
	std::stringstream prev_pid, next_pid;

	// Initialize find pid list
	for (int i(0); i < (int)v_node_info_.size(); ++i) {

		// Clear buffer
		prev_pid.str("");
		next_pid.str("");
		prev_pid.clear(std::stringstream::goodbit);
		next_pid.clear(std::stringstream::goodbit);

		prev_pid << _prev_pid << v_node_info_.at(i).pid;
		next_pid << _next_pid << v_node_info_.at(i).pid;
		find_prev_pids.push_back(prev_pid.str());
		find_next_pids.push_back(next_pid.str());
	}		

	create_process_info(find_prev_pids, find_next_pids);
		
}

 
void Tracer::create_process_info(
		std::vector<std::string> find_prev_pid,
		std::vector<std::string> find_next_pid){

	std::string buf;
	std::string delim = " \t\v\r\n";
	std::vector<std::string> start_time_s, finish_time_s;
	double start_time_i = 0;
	double finish_time_i = 0;
	trace_info_t trace_info;

	// Loop by the number of pid
	for (int i(0); i < (int)find_prev_pid.size();i++){
		std::ifstream _trace_log("./trace.log");
		
		while(std::getline(_trace_log,buf)){

			// start time
			if(buf.find(find_next_pid.at(i)) != -1){
				start_time_s = split(trim(buf),delim);
				start_time_i = strtod(start_time_s[2].c_str(),NULL); 
				trace_info.name = find_next_pid.at(i).substr(9); //pid
				trace_info.start_time = start_time_i;
				trace_info.core = ctoi(start_time_s[0]);
			}

			// end time
			if(buf.find(find_prev_pid.at(i)) != -1){
				finish_time_s = split(trim(buf),delim);
				finish_time_i = strtod(finish_time_s[2].c_str(),NULL);
				trace_info.runtime = finish_time_i - start_time_i;
				v_trace_info.push_back(trace_info); 


			}
		}
	}

	//sort by start_time
	//std::sort(v_trace_info.begin(),v_trace_info.end());
for(int i=0;i<(int)v_trace_info.size();i++){
		std::cout<< v_trace_info[i].name;
		printf(" core: %d, s_time: %f. r_time: %f\n"
				,v_trace_info[i].core
				,v_trace_info[i].start_time, v_trace_info[i].runtime);}
}



 // Separate trace.log by spaces
std::vector<std::string> Tracer::split(std::string str, std::string delim) {
  std::vector<std::string> items;
  std::size_t dlm_idx;
  if(str.npos == (dlm_idx = str.find_first_of(delim))) {
    items.push_back(str.substr(0, dlm_idx));
  }
  while(str.npos != (dlm_idx = str.find_first_of(delim))) {
    if(str.npos == str.find_first_not_of(delim)) {
      break;
    }
    items.push_back(str.substr(0, dlm_idx));
    dlm_idx++;
    str = str.erase(0, dlm_idx);
    if(str.npos == str.find_first_of(delim) && "" != str) {
      items.push_back(str);
      break;
    }
  }
  return items;
}

 // Align the start position to read the trace.log per line
std::string Tracer::trim(const std::string& string){
	const char* trimCharacterList = "[=";
	std::string result;
 
	std::string::size_type left = string.find_first_of(trimCharacterList);
 
	if (left != std::string::npos){
		std::string::size_type right = string.find_last_of(trimCharacterList);
		result = string.substr(left, right - left + 1);
	}
 
	return result;
}

int Tracer::ctoi(std::string s){
	if(s == "[000]")
		return 0;
	else if(s == "[001]")
		return 1;
	else if(s == "[002]")
		return 2;
	else if(s == "[003]")
		return 3;
	else if(s == "[004]")
		return 4;
	else if(s == "[005]")
		return 5;
	else if(s == "[006]")
		return 6;
	else if(s == "[007]")
		return 7;
	else if(s == "[008]")
		return 8;
	else 
		return -1;
}

std::vector<trace_info_t> Tracer::get_info(){
	return v_trace_info;
}
