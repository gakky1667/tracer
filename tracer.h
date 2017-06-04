#ifndef TRACER_H
#define TRACER_H

#include <stdlib.h>
#include <string>
#include "config.h"
#include <vector>
#include "yaml-cpp/yaml.h"
#include <iostream>
#include <sstream>

typedef struct node_info_t {
  std::string name;
  unsigned int pid;
  std::vector<std::string> v_subtopic;
  std::vector<std::string> v_pubtopic;
} node_info_t;

typedef struct trace_info_t {
	std::string name; //Currently this value indicates pid
	std::vector<std::string> v_subtopic;
	std::vector<std::string> v_pubtopic;
	int core;
	double runtime;
	double start_time;

	bool operator<(const trace_info_t& another) const{ 
		return start_time < another.start_time;
	}
} trace_info_t;

namespace SchedViz{
class Tracer{
public:
	Tracer();
	~Tracer();
	FILE *fp;
	void setup();
	void reset();
	void start_ftrace();
	
	std::vector<node_info_t> v_node_info_;
	std::vector<trace_info_t> v_trace_info;
private:
  void load_config_(const std::string &filename);
  Config config_;

  unsigned int get_pid(std::string name);
  void set_tracing_on(char *mode);
  void set_trace(char *mode);
  void set_events_enable(char *mode);
  void set_current_tracer(char *mode);
  void set_event(char *mode);
  void output_log();
  void filter_pid(bool mode);
	void extract_period();
	void create_process_info(
			std::vector<std::string> find_prev_pids,
			std::vector<std::string> find_next_pids);
	std::vector<std::string> split(std::string str, std::string delim);		
	std::string trim(const std::string& string); 
	int ctoi(std::string s);
};
}

#endif // TRACER_H
