#include "processor.h"
#include "linux_parser.h"



// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
            
            totalidle = LinuxParser::IdleJiffies();
            totalnonidle = LinuxParser::ActiveJiffies();
            total = totalnonidle + totalidle;
            long long int totald = total - prevtotal;
            long long int idled = totalidle - previdle;
            
            cpu_utilization =  ( (float)totald - (float)idled ) / (float) totald ; 
 
            prevtotal = total;
            previdle = totalidle ; 
return cpu_utilization; 
}