#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int iterations = 0;// кол-во итераций

double f1(double x){// пока на си
  return 3 * (0.5 / (x + 1) + 1);
  //return x*x/16;
}



double f2(double x){// пока на си
  return 2.5*x - 9.5;
  //return x;
}

double f3(double x){// пока на си
  return 5/x;
}

double derivative(double (*f)(double), double x, double eps){//просто считаем через приращение
  double ans, ans_pred = 1.0/0.0;//inf
  double delta = 0.001;
  ans = (f(x + delta) - f(x))/delta;
  while (fabs(ans - ans_pred) >= eps)
  {
    delta /= 2;
    ans_pred = ans;
    ans = (f(x + delta) - f(x))/delta;
  }
  return ans;
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
  double x_pred;
  double x = (a + b)/2;
  
  double derivative1 = derivative(f, x, 0.01);//нам обещали сохранение знака на всём отрезке
  double derivative2 = derivative(g, x, 0.01);
  
  // d1 > 0, d2 > 0 , вниз - слева
  // f((a + b)/2) + (f(a) + f(b))/2 
  
  if ((derivative1*derivative2 < 0) && (f((a + b)/2) - g((a + b)/2) + (f(a) + f(b))/2 - (g(a) + g(b))/2))//идем справа
  {
    x = a;
    x_pred = b;
    //printf("%f", b);
    while (fabs(x-x_pred) >= eps1)
    {
      x_pred = x;
      x = x_pred - (f(x_pred) - g(x_pred))*(x_pred - b)/(f(x_pred) - g(x_pred) - f(b) + g(b));// метод хорд
    }
  }
  else// слева
  {
    x = b;
    x_pred = a;
    //printf("%f", b);
    while (fabs(x-x_pred) >= eps1)
    {
      x_pred = x;
      x = x_pred - (f(x_pred) - g(x_pred))*(x_pred - a)/(f(x_pred) - g(x_pred) - f(a) + g(a));// метод хорд
    }
  }
  return x;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
  int n = (int) (fabs(a-b)/eps2);//число шагов
  double result = 0, step = (b - a) / n;//результат и длина шага 
  
  for(int i = 0; i < n; i++) {
    result += f(a + step * (i + 0.5));
  }
  result *= step;
  
  double result_pred = 1.0/0.0;
  while (fabs(result - result_pred) >= eps2)//пока не сойдется
  {
    result_pred = result;
    n *= 2;
    result = 0;
    step = (b - a) / n;
    
    for(int i = 0; i < n; i++) {
      result += f(a + step * (i + 0.5));
    }
    result *= step;
  }
  return result;
}

int main()
{
  //ps по условию x > 0
  
  double x = root(f1, f2, -3, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: x == 5.09839
  
  x = root(f1, f3, 0.5, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: x == 1.37701
  
  x = root(f2, f3, 0.5, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: x == 4.26854
  
  x = integral(f1, 3, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: 13.0397
  
  x = integral(f2, 3, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: 12
  
  x = integral(f3, 3, 7, 0.001);
  printf("%f\n\n", x);
  //wolframalpha.com: 4.2365
  //x = derivative(f1, 2, 1);
  
  //printf("%f", x);
  return 0;
}
