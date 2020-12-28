#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
 long long int totalidle = 0;
 long long int previdle = 0;

 long long int totalnonidle = 0;
 long long int prevnonidle = 0;

 long long int total = 0;
 long long int prevtotal = 0;

 float cpu_utilization = 0;

};

#endif