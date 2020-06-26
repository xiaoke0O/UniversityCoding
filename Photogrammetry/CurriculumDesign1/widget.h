#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextBrowser>
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

private slots:
    void doCalculation();

};