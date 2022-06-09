const int rs = 6;
const int rb = 9;
const int ls = 10;
const int lb = 11;
const int bee = 12;
const int key = 7;
const int rl = 5;
const int ll = 4;

void gb(int r, int l);
void gs(int r, int l);
void get_start(void);
void follow_link();

void setup() 
{
  Serial.begin(9600);
  pinMode(6, 1);
  pinMode(9, 1);
  pinMode(10, 1);
  pinMode(11, 1);
  pinMode(key, INPUT);
  pinMode(bee, 1);
  get_start();
}

void loop() 
{
  follow_link();
  
}

//前进 r为有马达功率，l为左马达功率
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

//后退 参数同上
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

//寻线函数
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
