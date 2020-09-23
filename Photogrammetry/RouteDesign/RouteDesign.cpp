#include "RouteDesign.h"

#include <fstream>
#include <iomanip>  //控制小数点位数的头文件
using namespace std;
RouteDesign::RouteDesign() {
  cout << "Start to design" << endl;
  fstream outf("./output.csv", ios::out);
  double left_up_x = 38431550.4239;  //左上角X坐标
  double left_up_y = 3896419.9716;   //左上角Y坐标
  double left_up_x_T = 38431548.6566;  //左上角X坐标
  double left_up_y_T = 3896426.6200;   //左上角Y坐标
  double B = 90;                     //摄影基线
  double line_space = 160;           //航线间隔
  unsigned N1 = 26;                  //每条航线像片数
  unsigned N2 = 10;                  //航线数
  double x = 0;
  double y = 0;
  int pointcount = 0;
  for (int i = 0; i < N2; ++i) {
    int Px = (i % 2) ? -1 : 1;  // TODO:奇数为1，偶数为-1
    int Py = -1 * i;
    for (int j = 0; j < N1; ++j) {
      x = left_up_x + ((j -1)*1.0) *Px *B;
      y = left_up_y + Py * line_space;
      outf <<++pointcount<<","<< fixed << setprecision(4) << x << "," << y << "," << 487.959<< "\n";
    }
    left_up_x = x-Px*B;
  }
}

RouteDesign::~RouteDesign() {}