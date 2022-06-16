
const int rs = 6;
const int rb = 9;
const int ls = 10;
const int lb = 11;
const int bee = 12;
const int key = 7;
const int rl = 5;
const int ll = 4;
const int L3 = 8;
const int L4 = 13;

const int vmotor = 3;

const int echo = A1;
const int trig = A0;
int front = 0;
int left = 0;
int right = 0;

void gb(int r, int l);
void gs(int r, int l);
void get_start(void);
void follow_link(void);
void link_2l(void);
void brake(void);
void bizhang(void);
int get_time(int times);
double csb(void);
void vm(int degree);
double f_d(void);
double r_d(void);
double l_d(void);
void find_way(void);

void setup() 
{
  Serial.begin(9600);
  pinMode(6, 1);
  pinMode(9, 1);
  pinMode(10, 1);
  pinMode(11, 1);
  pinMode(key, INPUT);
  pinMode(bee, 1);
  pinMode(L3, INPUT);
  pinMode(L4, INPUT);
  pinMode(echo, INPUT);
  pinMode(trig, 1);
  pinMode(vmotor, 1);
  get_start();
}

void loop() 
{
  find_way();
  
  
  
}

//刹车
void brake(void)
{
  digitalWrite(rs, 0);
  digitalWrite(rb, 0);
  digitalWrite(lb, 0);
  digitalWrite(ls, 0);
  
}

//前进 r为有右达功率，l为左马达功率
void gs(int r, int l)
{
  digitalWrite(rs, 1);
  digitalWrite(rb, 0);
  analogWrite(rs, l);
  analogWrite(rb, 0);
  digitalWrite(ls, 1);
  digitalWrite(lb, 0);
  analogWrite(ls, r);
  analogWrite(lb, 0);
}

//后退 参数同上,r是左，l是右
void gb(int r, int l)
{
  digitalWrite(rs, 0);  
  digitalWrite(rb, 1);
  analogWrite(rs, 0);
  analogWrite(rs, l);
  digitalWrite(ls, 0);  
  digitalWrite(lb, 1);
  analogWrite(ls, 0);
  analogWrite(lb, r);
}

//按钮按下后叫三声启动
void get_start(void)
{
  while(!digitalRead(key))
  {
    
  }
  if (digitalRead(key))
  {
    digitalWrite(bee, 1);
    delay(1000);
    digitalWrite(bee, 0);
    delay(1000);
    digitalWrite(bee, 1);
    delay(1000);
    digitalWrite(bee, 0);
    delay(1000);
    digitalWrite(bee, 1);
    delay(1000);
    digitalWrite(bee, 0);
    delay(1000);
  } 
}

//寻线函数（单光感）
void follow_link(void)
{
  while(1)
  {
    if (digitalRead(rl) == 0)
    {
      gs(90, 0); 
    }
    else if(digitalRead(rl) == 1)
    {
      gs(0, 90);
    }
  }
  
}

//双光感寻线
void link_2l(void)
{
  if (digitalRead(ll) == 0 && digitalRead(rl) == 0)
    gs(60, 60);
  else if (digitalRead(ll)== 1 && digitalRead(rl) == 0)
    gs(0, 60);
  else if (digitalRead(ll) == 0 && digitalRead(rl) == 1)
    gs(60, 0);
}

int get_time(int times)
{
  int x = millis();
  return (x - times);
}

//避障
void bizhang()
{
  int sl = digitalRead(L3);
  int sr = digitalRead(L4);
  if (sl == 1 && sr == 1)
    gs(90, 90);
  else if (sl == 0 && sr == 1)
    {
    gs(180, 0);
    delay(800);
    }
  else if (sl == 1 && sr == 0)
  {
    gs(0, 180);
    delay(800);
  }
  else
    gs(0, 0);    
}

double csb(void)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, 1);
  delayMicroseconds(10);
  digitalWrite(trig, 0);
  double distance = pulseIn(echo, 1);
  distance = distance/58;
  return distance;
}

void vm(int degree)
{
   int d = degree*11 + 500;
   digitalWrite(vmotor, 1);
   delayMicroseconds(d);
   digitalWrite(vmotor, 0);
   delay(20-(d*0.001));
   
}

double f_d(void)
{
  for (int i = 0; i < 10; i++)
  vm(60);
  double x = csb();
  return x;
}

double r_d(void)
{
  for (int i = 0; i < 10; i++)
  vm(40); 
  double x = csb();
  return x;
}

double l_d(void)
{
 for (int i = 0; i < 10; i++)
 vm(80);
 double x = csb();
 return x;
}

void find_way(void)
{
 while(1)
 {
  double f_dis = f_d();
  if (f_dis < 18)
  {
  gs(0, 0);
  delay(500);
  gb(110, 100);
  delay(1000);
  double r_dis = r_d();
  double l_dis = l_d();
    if (r_dis < 18 && l_dis < 18)
    {
      gs(100, 0);
      delay(2000);
    }
    else if (r_dis > l_dis)
    {
      gs(0, 100);
      delay(800);
    }
    else
    {
      gs(100, 0);
      delay(800);
    }
  }
  else
  {
    gs(150, 150);
  }
 }
  
}
