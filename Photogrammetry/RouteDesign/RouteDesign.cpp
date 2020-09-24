#include "RouteDesign.h"

#include <fstream>
#include <iomanip>  //控制小数点位数的头文件
using namespace std;
RouteDesign::RouteDesign() {
  cout << "Begin to calculate" << endl;
  fstream  outf("./output.csv", ios::out);
  double   left_up_x = 38431550.4239;    //左上角X坐标
  double   left_up_y = 3896419.9716;     //左上角Y坐标
  double   left_up_x_T = 38431548.6566;  //左上角X坐标。指导书给的
  double   left_up_y_T = 3896426.6200;   //左上角Y坐标。指导书给的
  double   fly_height = 487.959;         //绝对航高
  double   B = 90;                       //摄影基线
  double   line_space = 160;             //航线间隔
  unsigned N1 = 26;                      //每条航线像片数
  unsigned N2 = 10;                      //航线数
  double x = 0;                          //摄站x坐标
  double y = 0;                          //摄站y坐标
  int pointcount = 0;                    //摄站编号
  double begin_x = left_up_x - B;//第一个摄站为西边线向西一个摄影基线。
  double begin_y = left_up_y;
  for (int i = 0; i < N2; ++i) {

    int Py = -1 * i;  //由北向南，Y坐标值递减
    int Px = (i % 2) ? -1 : 1;  //从西往东飞，奇数航线X值递减，偶数航线X坐标值递增（第一条航线编号为0）

    for (int j = 0; j < N1; ++j) {
      x = begin_x + (j * 1.0) * Px * B;
      y = begin_y + Py * line_space;
      outf << ++pointcount << "," << fixed << setprecision(4) << x << "," << y
           << "," << fly_height << "\n";
    }
    begin_x = x;  //航线尽头的X坐标值作为起始
  }
}

RouteDesign::~RouteDesign() {}