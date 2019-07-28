#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#include <sys/ioctl.h>
#include <unistd.h>

struct winsize terminalSize;

double map(int val, int originalMin, int originalMax, int newMin, int newMax){
  double ratio = (double)(newMax - newMin) / (originalMax - originalMin);
  return newMin + ((val - originalMin) * ratio);
}

void graph(double a, double b, double c, double d){
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);
  std::vector<double> values;

  int min, max;
  min = max = 0;

  double x = terminalSize.ws_col/-2;
  for(int i = 0; i < terminalSize.ws_col; i++){
    values.push_back(std::pow(x, 3) * a + std::pow(x, 2) * b + x * c + d);
    //values.push_back(std::sin(x) * 10);
    x += 1;
  }

  for(auto val : values){
    if(min > val) min = val;
    if(max < val) max = val;
  }

  std::string buffer;

  for(int i = terminalSize.ws_row; i > 0; i--){
    for(int j = 0; j < values.size(); j++){
      if(i == (int)(map(values[j], -50, 50, 1, terminalSize.ws_row - 1) + 0.5)){
        buffer += "#";
      } else {
        buffer += " ";
      }
    }
  }

  std::cout << buffer;
  std::flush(std::cout);
}

int main(){
  /*
  while(1){
    for(int i = 0; i < 100; i++){
      graph(0, -i * 0.01, 0, 0);
      usleep(10000);
    }
    for(int i = 100; i > 0 ; i--){
      graph(0, -i * 0.01, 0, 0);
      usleep(10000);
    }
    for(int i = 0; i < 100; i++){
      graph(0, i * 0.01, 0, 0);
      usleep(10000);
    }
    for(int i = 100; i > 0 ; i--){
      graph(0, i * 0.01, 0, 0);
      usleep(10000);
    }
  }
  return 0;
  while(1){
    for(int i = 0; i < 100; i++){
      graph(i * -0.001, 0, 0, 0);
      usleep(10000);
    }
    for(int i = 100; i > 0 ; i--){
      graph(i * -0.001, 0, 0, 0);
      usleep(10000);
    }
    for(int i = 0; i < 100; i++){
      graph(i * 0.001, 0, 0, 0);
      usleep(10000);
    }
    for(int i = 100; i > 0 ; i--){
      graph(i * 0.001, 0, 0, 0);
      usleep(10000);
    }
  }

  return 0;
  */
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);
  std::vector<double> values;

  double a, b, c, d;
  int min, max;
  min = max = 0;
  a = -0.01;
  b = 0.3;
  c = 1.3;
  d = -40;

  double x = terminalSize.ws_col/-2;
  for(int i = 0; i < terminalSize.ws_col; i++){
    values.push_back(std::pow(x, 3) * a + std::pow(x, 2) * b + x * c + d);
    //values.push_back(std::sin(x) * 10);
    x += 1;
  }

  for(auto val : values){
    if(min > val) min = val;
    if(max < val) max = val;
  }

  for(auto val : values){
    //std::cout << (int)(map(val, -100, 100, 0, terminalSize.ws_row) + 0.5) << std::endl;
    std::cout << val << std::endl;
  }

  std::string buffer;

  for(int i = terminalSize.ws_row; i > 0; i--){
    for(int j = 0; j < values.size(); j++){
      if(i == (int)(map(values[j], -50, 50, 1, terminalSize.ws_row - 1) + 0.5)){
        buffer += "@";
      } else {
        buffer += " ";
      }
    }
  }

  std::cout << buffer;
}
