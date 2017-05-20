#include <stdlib.h> 
#include <string>

namespace SchedViz{
class Tracer{
public:
	Tracer();
	~Tracer();
	FILE *fp;
	void setup();
	void reset();
	void set_tracing_on(char *mode);
	void set_trace(char *mode);
	void set_events_enable(char *mode);
	void set_current_tracer(char *mode);
	void set_event(char *mode);
	void output_log();
	//void print_tracers();	
	void start_ftrace();

	void filter_pid(char *mode);
#if 0
	void stop_ftrace();
	void get_ftrace();


private:
	void load_config_(const std::string &filename);
	Config config_;
#endif
};
}
