const int trigpin=18;//定义定义超声波模块的Trig引脚为A4
const int echopin=19;//定义超声波模块的Echo引脚为A5

const int led[8]={2,3,4,5,6,7,8,9};//定义数码管的LED引脚
const int digit[4]={13,12,11,10};//定义数码管的数字位引脚

float getDistance(int trigpin,int echopin);//封装超声波测距函数
void show(char wei,char n);//封装显示某一位的数字的函数
int getweiofdot(float s);//封装得到小数点位数的函数

int num1,num2,num3,num4;//定义四位数码管每位显示的值
float distance_float;//浮点型的距离数据值
int distance_int;//转化后的整形数据值
int delaytime=500;//人眼的视觉延迟时间
char num[17][8]=
{
    {1, 1, 1, 1, 1, 1, 0, 0},     //显示0
    {0, 1, 1, 0, 0, 0, 0, 0},     //显示1
    {1, 1, 0, 1, 1, 0, 1, 0},     //显示2
    {1, 1, 1, 1, 0, 0, 1, 0},     //显示3
    {0, 1, 1, 0, 0, 1, 1, 0},     //显示4
    {1, 0, 1, 1, 0, 1, 1, 0},     //显示5
    {1, 0, 1, 1, 1, 1, 1, 0},     //显示6
    {1, 1, 1, 0, 0, 0, 0, 0},     //显示7
    {1, 1, 1, 1, 1, 1, 1, 0},     //显示8
    {1, 1, 1, 1, 0, 1, 1, 0},     //显示9
    {0, 0, 0, 0, 0, 0, 0, 1}      //显示.
};

void setup()
{
    for(int i=0;i<8;i++)
    {
        pinMode(led[i],OUTPUT);//每个LED引脚都设为输出模式
    }
    for(int i=0;i<4;i++)
    {
        pinMode(digit[i],OUTPUT);//每个数码管的引脚设为输出模式
    }
    pinMode(trigpin,OUTPUT);
    pinMode(echopin,INPUT);
}

void loop()
{
    distance_float=getDistance(trigpin,echopin);//获取浮点类型的距离值
    int dot=getweiofdot(distance_float);//dot表示应该在哪一位上显示小数点

    int change=1;
    for(int i=1;i<dot;i++)change*=10;//改变change的值从而控制之后的格式转换

    distance_int=(int)(distance_float*change);//根据保留小数点位数的需要将测量值转换为相应的整数。
    num1=distance_int%10;//得到第1位的数字
    num2=distance_int/10%10;//得到第2位的数字
    num3=distance_int/100%10;//得到第3位的数字
    num4=distance_int/1000%10;//得到第4位的数字

    for(int i=0;i<=500;i++)
    {
        show(dot,10);//显示小数点
        show(1,num1);//显示第一位上的数字
        delayMicroseconds(delaytime);
        show(2,num2);//显示第二位上的数字
        delayMicroseconds(delaytime);
        show(3,num3);//显示第三位上的数字
        delayMicroseconds(delaytime);
        show(4,num4);//显示第四位上的数字
        delayMicroseconds(delaytime);
    }
}

void show(char wei,char n)
{
    for(int i=0;i<8;i++)
    {
        digitalWrite(led[i],LOW);//去除余晖
    }
    switch(wei)
    {
        case 1:
            digitalWrite(digit[0],LOW);
            digitalWrite(digit[1],HIGH);
            digitalWrite(digit[2],HIGH);
            digitalWrite(digit[3],HIGH);//选择显示第1位
            break;
        case 2:
            digitalWrite(digit[0],HIGH);
            digitalWrite(digit[1],LOW);
            digitalWrite(digit[2],HIGH);
            digitalWrite(digit[3],HIGH);//选择显示第2位
            break;
        case 3:
            digitalWrite(digit[0],HIGH);
            digitalWrite(digit[1],HIGH);
            digitalWrite(digit[2],LOW);
            digitalWrite(digit[3],HIGH);//选择显示第3位
            break;
        case 4:
            digitalWrite(digit[0],HIGH);
            digitalWrite(digit[1],HIGH);
            digitalWrite(digit[2],HIGH);
            digitalWrite(digit[3],LOW);//选择显示第4位
            break;
        default:break;
    }
    for(int i=0;i<8;i++)
    {
        digitalWrite(led[i],num[n][i]);//按照数字的值进行显示
    }
}

float getDistance(int trigpin,int echopin)
{
    digitalWrite(trigpin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin,HIGH);
    delayMicroseconds(12);
    digitalWrite(trigpin,LOW);
    float s=pulseIn(echopin,HIGH)/58.0;
    delay(10);
    return s;
}

int getweiofdot(float s)
{
    int dot_wei;
    if(distance_float<10)
    {
        dot_wei=4;
    }
    else if(distance_float>=10&&distance_float<100)
    {
        dot_wei=3;
    }
    else if(distance_float>=100)
    {
        dot_wei=2;
    }
    return dot_wei;
}