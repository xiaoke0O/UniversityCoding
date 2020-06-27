#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
#include <Eigen/Geometry>
class widget : public QWidget
{
public:
    widget();
private:
    QLabel       *title;
    QComboBox    *itemNumber;
    QLineEdit    *LX,*LY,*RX,*RY;
    QPushButton  *calculateButton;
    QTextBrowser *resultText;

private:
    void createWidget();
    Eigen::Matrix3d getRotateMatrix3d(double varphi,double omega,double kappa);

private slots:
    void doCalculation();

};