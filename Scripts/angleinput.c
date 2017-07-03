#include <stdlib.h>
#include <stdio.h>

int main()
{
	double a;
	FILE *f = fopen("../OpenCascade/angleinput.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	printf("Enter the values for:\nRadius: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	printf("Height: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	printf("Angle (degrees): ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	fprintf(f,"Key:\nlineNo-variable\n1-radius\n2-height\n3-angle (degrees)");
	fclose(f);	
}
