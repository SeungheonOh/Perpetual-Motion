#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <ctime>

#include <sys/ioctl.h>
#include <unistd.h>

struct winsize terminalSize;

std::vector<double> perlnNoise;

double map(int val, int originalMin, int originalMax, int newMin, int newMax){
  double ratio = (double)(newMax - newMin) / (originalMax - originalMin);
  return newMin + ((val - originalMin) * ratio);
}

int random(int min, int max){
  return rand() % max + min;
}

double dist(int Aa, int Ab, int Ba, int Bb){
  return std::sqrt(std::pow(Aa - Ba, 2) + std::pow(Ab - Bb, 2));
}

void perlnInit(int waveLength, int vectorSize){
  perlnNoise.clear();
  perlnNoise.push_back(0);
  for(int i = 0; i < vectorSize; i++){
    double target = random(0, 100);
    double wavelen = waveLength + random(-20, 20);
    while(std::abs(perlnNoise.back() - target) > 5){
      if(target > perlnNoise.back()){
        perlnNoise.push_back(perlnNoise.back() + random(1, 2));
      } else {
        perlnNoise.push_back(perlnNoise.back() - random(1, 2));
      }
    }
    perlnNoise.push_back(perlnNoise.back());
  }
}

int main(){
  srand(time(NULL));
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize);
  std::vector<std::pair<int, int>> screen;

  double b = 0.01;
  double increment = 0.01;
  while(true){
  b += increment;
  perlnInit(10, 300);

  if(b > 1)increment = -0.01;
  if(b < 0.01)increment = 0.01;

  screen.clear();

  int r = 20;

  for(double i = 0; i < M_PI * 2; i+=b){
    bool isOkay = true;
    int x, y;
    int randomVal = map(perlnNoise[map(std::sin(i), -1, 1, 0, 100)], 0, 100, 0, random(1, 3));
    x = (r + randomVal) * std::sin(i) / 2;
    y = (r + randomVal) * std::cos(i);

    for(auto point : screen){
      if(std::round(std::atan2(point.second, point.first) * 180 / M_PI) - std::round(std::atan2(y, x) * 180 / M_PI) >= 0 && std::round(std::atan2(point.second, point.first) * 180 / M_PI) - std::round(std::atan2(y, x) * 180 / M_PI) < 4){
        isOkay = false;
      }
    }
    if(isOkay)screen.push_back(std::pair<int, int>(x, y));
  }

  std::string buffer;
  for(int i = terminalSize.ws_row * -0.5; i < terminalSize.ws_row * 0.5; i++){
    for(int j = terminalSize.ws_col * -0.5; j < terminalSize.ws_col * 0.5; j++){
      std::pair<int, int> current;
      for(auto point : screen){
        if(point.first == i && point.second == j){
          current = point;
        }
      }
      if(current.first&&current.second){
        buffer += "#";
        continue;
      }
      buffer += " ";
    }
  }
  std::cout << buffer;
  std::flush(std::cout);
  buffer.clear();
  usleep(random(40000, 100000));
  }
  //std::cin >> buffer;
}
