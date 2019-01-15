#include <stdio.h>
#include <stdlib.h>
struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info_t working,  //info about working
                retire_info_t retired)  //info about being retired
{
  double y = initial;
  int x = startAge;
  for (int i = 1; i <= working.months; i++) {
    printf("Age %3d month %2d you have $%.2lf\n", x / 12, x % 12, y);
    y = y * working.rate_of_return + working.contribution + y;
    x = x + 1;
  }
  for (int j = working.months; j < working.months + retired.months; j++) {
    printf("Age %3d month %2d you have $%.2lf\n", x / 12, x % 12, y);
    y = y * retired.rate_of_return + retired.contribution + y;
    x = x + 1;
  }
}
int main(void) {
  retire_info_t working;
  retire_info_t retired;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  int age = 327;
  double savings = 21345;
  retirement(age, savings, working, retired);
  return 0;
}
