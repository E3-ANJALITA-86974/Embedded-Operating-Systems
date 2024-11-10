#include<stdio.h>
#include"circle.h"
#include"square.h"
#include"rectangle.h"

int main()
{
float rad,area_circle,side,area_square,a,b,area_rectangle;
printf("Enter radius of circle : ");
scanf("%f",&rad);
area_circle = circle_area(rad);
printf("Radius of circle is %.2f \n",area_circle);
printf("Enter side of square : ");
scanf("%f",&side);
area_square = square_area(side);
printf("Area of square is %.2f \n",area_square);
printf("Enter side a of rectangle : ");
scanf("%f",&a);
printf("Enter side b of rectangle : ");
scanf("%f",&b);
area_rectangle = rectangle_area(a,b);
printf("Area of rectangle is %.2f \n",area_rectangle);
return 0;
}
