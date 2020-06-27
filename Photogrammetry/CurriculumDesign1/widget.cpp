#include "widget.h"
#include <QDebug>
#include <QIcon>
#include <QGridLayout>
#include <Eigen/Geometry>
widget::widget()
{
    resize(350, 260);
    setMinimumSize(QSize(300, 200));
    setWindowTitle(QString::fromUtf8("前方交会分工"));
    setWindowIcon(QIcon("qrc/Dad_Shoes.svg"));

    createWidget();

    connect(calculateButton, &QPushButton::clicked, this, &widget::doCalculation);
}

void widget::createWidget()
{
    QGridLayout *layout = new QGridLayout;
    setLayout(layout);

    title = new QLabel(QString::fromUtf8("<b>请选择组合</b>"));
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title, 1, 0, 1, 4);

    itemNumber = new QComboBox;
    itemNumber->addItem("DO1617");
    itemNumber->addItem("DO1718");
    itemNumber->addItem("DO2627");
    itemNumber->addItem("DO2728");
    layout->addWidget(itemNumber, 2, 0, 1, 4);

    LX = new QLineEdit;
    LX->setPlaceholderText(QString::fromUtf8("左片X坐标"));
    layout->addWidget(LX, 4, 0, 1, 1);

    LY = new QLineEdit;
    LY->setPlaceholderText(QString::fromUtf8("左片Y坐标"));
    layout->addWidget(LY, 4, 1, 1, 1);

    RX = new QLineEdit;
    RX->setPlaceholderText(QString::fromUtf8("右片X坐标"));
    layout->addWidget(RX, 5, 0, 1, 1);

    RY = new QLineEdit;
    RY->setPlaceholderText(QString::fromUtf8("右片Y坐标"));
    layout->addWidget(RY, 5, 1, 1, 1);

    calculateButton = new QPushButton;
    calculateButton->setText(QString::fromUtf8("计算"));

    layout->addWidget(calculateButton, 5, 3, 1, 1);

    resultText = new QTextBrowser;
    layout->addWidget(resultText, 6, 0, 1, 5);
}

void widget::doCalculation()
{
    QList<double> element_16;
    element_16 << 431834.729 << 3896023.910 << 1261.736 << 0.002194288 << 0.00078372700 << -0.01758355;
    QList<double> element_17;
    element_17 << 432224.292 << 3896015.360 << 1266.845 << 0.001888322 << 0.00067279300 << -0.005601195;
    QList<double> element_18;
    element_18 << 432616.141 << 3896018.089 << 1269.803 << 0.001182511 << 0.0007234885 << 0.007524145;
    QList<double> element_26;
    element_26 << 432028.494 << 3894841.515 << 1273.147 << -0.005528028 << 0.0007792605 << -0.01138808;
    QList<double> element_27;
    element_27 << 432438.565 << 3894841.049 << 1274.012 << -0.005785603 << 0.0003784083 << -0.01880947;
    QList<double> element_28;
    element_28 << 432847.537 << 3894836.718 << 1272.414 << -0.006604103 << 0.00053947040 << 0.000761938;

    QList<double> elementLeft, elementRight;

    switch (itemNumber->currentIndex())
    {
    case 0:
        elementLeft = element_16;
        elementRight = element_17;
        break;
    case 1:
        elementLeft = element_17;
        elementRight = element_18;
        break;
    case 2:
        elementLeft = element_26;
        elementRight = element_27;
        break;
    case 3:
        elementLeft = element_27;
        elementRight = element_28;
        break;
    default:
        resultText->append("ok?");
    }

    double Xs1 = elementLeft[0], Ys1 = elementLeft[1], Zs1 = elementLeft[2];
    double varphi1 = elementLeft[3], omega1 = elementLeft[4], kappa1 = elementLeft[5];
    double Xs2 = elementRight[0], Ys2 = elementRight[1], Zs2 = elementRight[2];
    double varphi2 = elementRight[3], omega2 = elementRight[4], kappa2 = elementRight[5];

    double focal_length = 70.5; //mm
                                //同名像点在左像的坐标
    Eigen::Vector3d Left_image_coordinate;
    Left_image_coordinate << LX->text().toDouble(), LY->text().toDouble(), -focal_length;
    //同名像点在右像的坐标
    Eigen::Vector3d Right_image_coordinate;
    Right_image_coordinate << RX->text().toDouble(), RY->text().toDouble(), -focal_length;

    //摄影基线的三个分量
    double Bx = Xs2 - Xs1;
    double By = Ys2 - Ys1;
    double Bz = Zs2 - Zs1;
    /**********************************计算旋转矩阵******************************/
    //左像片的旋转矩阵
    Eigen::Matrix3d Left_Rotate=getRotateMatrix3d(varphi1,omega1,kappa1);
    //右像片的旋转矩阵
    Eigen::Matrix3d Right_Rotate=getRotateMatrix3d(varphi2,omega2,kappa2);
    //同名像点的像空间辅助坐标
    Eigen::Vector3d Left_aux_coordinate;
    Left_aux_coordinate = Left_Rotate * Left_image_coordinate;
    Eigen::Vector3d Right_aux_coordinate;
    Right_aux_coordinate = Right_Rotate * Right_image_coordinate;
    //计算投影系数Left_N Right_N
    double X1 = Left_aux_coordinate(0, 0);
    double Y1 = Left_aux_coordinate(1, 0);
    double Z1 = Left_aux_coordinate(2, 0);

    double X2 = Right_aux_coordinate(0, 0);
    double Y2 = Right_aux_coordinate(1, 0);
    double Z2 = Right_aux_coordinate(2, 0);

    double Left_N = (Bx * Z2 - Bz * X2) / (X1 * Z2 - X2 * Z1);
    double Right_N = (Bx * Z1 - Bz * X1) / (X1 * Z2 - X2 * Z1);

    //计算地面点的左像像辅系坐标
    double delta_X = Left_N * X1;
    double delta_Y = (Left_N * Y1 + Right_N * Y2 + By) / 2.0;
    double delta_Z = Left_N * Z1;
    //    printf("地面点的左像像辅系坐标\n%.3lf,%.3lf,%.3lf\n", delta_X, delta_Y, delta_Z);
    //地面点的地面坐标
    double ground_X = Xs1 + delta_X;
    double ground_Y = Ys1 + delta_Y;
    double ground_Z = Zs1 + delta_Z;

    resultText->setText(QString::fromUtf8("地面点坐标为:\n") + QString::number(ground_X, 'f', 3) + "\t" + QString::number(ground_Y, 'f', 3) + "\t" + QString::number(ground_Z, 'f', 3));
}

Eigen::Matrix3d widget::getRotateMatrix3d(double varphi, double omega, double kappa)
{
    Eigen::Matrix3d RotateMatrix;
    RotateMatrix(0, 0) = cos(varphi) * cos(kappa) - sin(varphi) * sin(omega) * sin(kappa);
    RotateMatrix(0, 1) = (-1.0) * cos(varphi) * sin(kappa) - sin(varphi) * sin(omega) * cos(kappa);
    RotateMatrix(0, 2) = (-1.0) * sin(varphi) * cos(omega);
    RotateMatrix(1, 0) = cos(omega) * sin(kappa);
    RotateMatrix(1, 1) = cos(omega) * cos(kappa);
    RotateMatrix(1, 2) = (-1.0) * sin(omega);
    RotateMatrix(2, 0) = sin(varphi) * cos(kappa) + sin(varphi) * sin(omega) * sin(kappa);
    RotateMatrix(2, 1) = (-1.0) * sin(varphi) * sin(kappa) + cos(varphi) * sin(omega) * cos(kappa);
    RotateMatrix(2, 2) = cos(varphi) * cos(omega);
    return RotateMatrix;
}