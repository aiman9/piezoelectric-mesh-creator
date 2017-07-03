#include <stdlib.h>
#include <stdio.h>

int main()
{
	double a;
	FILE *f = fopen("../OpenCascade/ringinput.txt", "w");
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
	printf("Top inner radius: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	printf("Top outer radius: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	printf("Bottom inner radius: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	printf("Bottom outer radius: ");
	scanf("%lf",&a);
	fprintf(f,"%lf\n",a);
	fprintf(f,"Key:\nlineNo-variable\n1-radius\n2-height\n3-inradtop\n4-outradtop\n5-inradbottom\n6-inradbottom\n");
	fclose(f);	
}
