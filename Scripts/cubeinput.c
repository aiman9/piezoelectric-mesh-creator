#include <stdlib.h>
#include <stdio.h>

int main()
{
	double xl, yl, h, radius, xt, yt, xb, yb;
	
	printf("Enter the values for cuboid:\nLength(X): ");
	scanf("%lf",&xl);

	printf("Length(Y): ");
	scanf("%lf",&yl);

	printf("Height: ");
	scanf("%lf",&h);
	
	printf("Radius of electrode: ");
	scanf("%lf",&radius);

	printf("X-coordinate of electrode center (top): ");
	scanf("%lf",&xt);

	printf("Y-coordinate of electrode center (top): ");
	scanf("%lf",&yt);
	
	printf("X-coordinate of electrode center (bottom): ");
	scanf("%lf",&xb);
	
	printf("Y-coordinate of electrode center (bottom): ");
	scanf("%lf",&yb);

	int flag = 0;
	if(xt<=radius || (xl-xt)<=radius || yt<=radius || (yl-yt)<=radius){
  		printf("Top Electrode does not fit on surface\n");
  		flag=1;
  	}
    if(xb<=radius || (xl-xb)<=radius || yb<=radius || (yl-yb)<=radius){
  		printf("Bottom Electrode does not fit on surface\n");
  		flag=1;
  	}
  	if(flag)
  		exit(1);

  	FILE *f = fopen("../OpenCascade/cubeinput.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

  	fprintf(f,"%lf\n",xl);
  	fprintf(f,"%lf\n",yl);
  	fprintf(f,"%lf\n",h);
  	fprintf(f,"%lf\n",radius);
  	fprintf(f,"%lf\n",xt);
  	fprintf(f,"%lf\n",yt);
  	fprintf(f,"%lf\n",xb);
  	fprintf(f,"%lf\n",yb);  	

	fprintf(f,"Key:\nlineNo-variable\n1-Xlength\n2-Ylength\n3-Height\n4-Radius\n5-TopCenter(X)\n6-TopCenter(Y)\n7-BottomCenter(X)\n8-BottomCenter(Y)");
	fclose(f);	
}
