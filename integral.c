/*
  作成日: 2019/1/15
  作成者: 金原隆斗
  学籍番号: B20B011
  ソースファイル名: integral.c
  実行ファイル名:integral
  説明: 与えられた関数の積分値を合成シンプソンの公式で求めるプログラム。
  入力:積分区間の上限、下限(どちらもdouble型)を入力する。
       続いて、区間の分割数(int型,偶数かつ自然数)を入力する。
       入力はすべて標準入力に行う。
  出力:被積分関数の情報、積分区間、積分値を出力する。
       出力は標準出力に行う。
*/
#include<stdio.h>

/*プロトタイプ宣言*/
double calc_integral(double lower, double upper, int param);
double target(double x);
void description();

int main()
{
  /*変数宣言*/
  int n;/*分割数*/
  double a;/*積分区間の下限*/
  double b;/*積分区間の上限*/
  double answer;/*積分値*/
  
  printf("関数");
  description();
  printf("の定積分を行います。\n");
  
  printf("積分区間の下限を入力してください:");
  scanf("%lf",&a);
  
  printf("積分区間の上限を入力してください:");
  scanf("%lf",&b);
  
  printf("区間[%3.1f, %3.1f]をいくつの区間に分割して積分値を求めますか?\n",a,b);
  printf("(2以上の偶数を入力してください)");
  scanf("%d",&n);
  
  /*エラー処理1*/
  /*分割数が自然数かつ偶数でないとき、エラーメッセージを出力してプログラムを終了する*/
  if(n <= 0||n%2 == 1)
    {
      printf("分割数は2以上の偶数で入力してください。\n");
      return -1;
    }
  
  
  answer=calc_integral(a,b,n);
  
  /*エラー処理2*/
  /*aがbより大きいとき答えにマイナスをつけることで正しい値に戻せる*/
  if(a > b)
    {
      answer = -answer;
    }
  
  printf("関数f(x)の区間[%3.1f, %3.1f]における積分値は\n",a,b);
  printf("%16.15f\n",answer);
  printf("です。\n");
  
  return 0;
}

/*
  関数target により定義される積分対象関数の定積分値を求める関数
  仮引数:
  lower:積分区間の下限(任意の実数)
  upper:積分区間の上限(upper > lower である実数)
  param:制御パラメータ
  戻り値:
  仮引数で指定された積分区間での、
  関数targetの定積分値(実数)
*/
double calc_integral(double lower,double upper,int param)
{
  int i;/*ループカウンタ*/
  double integral;/*積分値*/
  double h;/*区間の幅*/
  double x_i;/*x座標*/
  
  h = (upper - lower) / ((double)param);
  
  integral = 0.0;
  for(i=1;i<=param-1;i++)
    {
      x_i =lower + h * i;
      if(i%2 == 0)
		{
	  		integral = integral + 2.0 * target(x_i);
		}
      else
		{
	  		integral = integral + 4.0 * target(x_i);
		}
    }
  integral = integral + target(upper) + target(lower);
  integral = integral * (h / 3.0);

  return integral;
}

/*
  積分対象関数の関数値を求める関数
  仮引数:
  x:非演算項(任意の実数)
  戻り値:
  仮引数に与えられた実数値(実引数)に「対する数学的関数fの関数値
*/

double target(double x)
{
	return 4.0 /( 1 + x * x);
}

/*積分対象関数の説明を表示する関数
  仮引数:
  なし(void)
  戻り値:
  なし(void)
  副作用:
  積分対象関数の説明を標準出力へ出力する
*/

void description()
{
  printf("f(x)=4.0 / 1 + x * x");
  return;
}
