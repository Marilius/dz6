#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int iterations = 0;// кол-во итераций

extern double f1(double x);
extern double f2(double x);
extern double f3(double x);

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
      iterations++;
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
      iterations++;
    }
  }
  return x;
}


double f1_test(double x){
  return 3 * (0.5 / (x + 1) + 1);
}

double f2_test(double x){
  return 2.5*x - 9.5;
}

double f3_test(double x){
  return 5/x;
}

int main(int argc, char **argv)
{
  //ps по условию x > 0
  int keys[2] = {0, 0};
  for(int i = 1; i < argc; i++)
    {
        if(strcmp("-help", argv[i]) == 0)// help option
        {
            printf("-help\tdescribe all options\n-iters\tprint num of iterations\n-roots\tprint roots\n-test args\ttest this program\n\
to test root args must be: root n a b eps;\n n - number of set of funcs (1 - f1 f2, 2 - f1 f3, 3 - f2 f3)\nto test integral args must be: integral n b eps;\n n - number of func (1 - f1, 2 - f1, 3 - f3)\n\
to run on prepared test args must be: -test prepared n\n n - index of test\n");
            return 0;
        }
        if(strcmp("-iters", argv[i]) == 0)// iters option
            keys[0] = 1;
        if(strcmp("-roots", argv[i]) == 0)// roots option
            keys[1] = 1;
        if(strcmp("-test", argv[i]) == 0)// test option
        {
            if(strcmp("root", argv[++i]) == 0)// test root
            {
                int p = atoi(argv[++i]);
                double a = atof(argv[++i]);
                double b = atof(argv[++i]);
                double eps = atof(argv[++i]);
                if(p == 1)
                {
                    printf("result is %lf\n", root(f1_test, f2_test, a, b, eps));
                }
                if(p == 2)
                {
                    printf("result is %lf\n", root(f1_test, f3_test, a, b, eps));
                }
                if(p == 3)
                {
                    printf("result is %lf\n", root(f2_test, f3_test, a, b, eps));
                }
            }
            if(strcmp("integral", argv[i]) == 0)// test integral
            {
                int p = atoi(argv[++i]);
                double a = atof(argv[++i]);
                double b = atof(argv[++i]);
                double eps = atof(argv[++i]);
                if(p == 1)
                    printf("result is %lf\n", integral(f1_test, a, b, eps));
                if(p == 2)
                    printf("result is %lf\n", integral(f2_test, a, b, eps));
                if(p == 3)
                    printf("result is %lf\n", integral(f3_test, a, b, eps));
            }
            if(strcmp("prepared", argv[i]) == 0)// prepared tests
            {
            	int p = atoi(argv[++i]);// prepared tests
            	if (p == 1)
                	printf("result is %lf\n", root(f1_test, f2_test, -3, 7, 0.001));//wolframalpha.com: x == 5.09839
            	if (p == 2)
                	printf("result is %lf\n", root(f1_test, f3_test, 0.5, 7, 0.001)); //wolframalpha.com: x == 1.37701
            	if (p == 3)
                	printf("result is %lf\n", root(f2_test, f3_test, 0.5, 7, 0.001));//wolframalpha.com: x == 4.26854
            	if (p == 4)
                	printf("result is %lf\n", integral(f1_test, 3, 7, 0.001));//wolframalpha.com: 13.0397
            	if (p == 5)
                	printf("result is %lf\n", integral(f2_test, 3, 7, 0.001)); //wolframalpha.com: 12
            	if (p == 6)
                	printf("result is %lf\n", integral(f3_test, 3, 7, 0.001));//wolframalpha.com: 4.2365
            	return 0;
            }
        }
    }
    else
    {
        double r1 = root(f1, f2, -3, 7, 0.001);//first root
        double r2 = root(f1, f3, 0.5, 7, 0.001);//second root
    	double r3 = root(f2, f3, 0.5, 7, 0.001);//third root
    	double s1 = integral(f1, 3, 7, 0.001);//first integral
    	double s2 = integral(f2, 3, 7, 0.001);//second integral
    	double s3 = integral(f3, 3, 7, 0.001);//third integral
    	if(keys[1] == 1)// -roots
        	printf("roots are \n%lf\n%lf\n%lf\n", r1, r2, r3);
    	if(keys[0] == 1)// -iters
        	printf("num of iterations is %d\n", iterations);//if key -iters was used
    }
    return 0;
}
