#include "widget.h"
#include<QDebug>
#include <QIcon>
#include <QGridLayout>
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
    qDebug("执行啦");
}