#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
	double xl, yl, h, el, eb;
	
	printf("Enter the values for cuboid:\nLength(X): ");
	scanf("%lf",&xl);

	printf("Length(Y): ");
	scanf("%lf",&yl);

	printf("Height: ");
	scanf("%lf",&h);
	
	printf("Length(X) of electrode: ");
	scanf("%lf",&el);

	printf("Length(Y) of Electrode: ");
	scanf("%lf",&eb);

	if(el>xl || eb>yl){
  		printf("Electrode does not fit on surface\n");
  		exit(1);
  	}

  	FILE *f = fopen("../OpenCascade/cuberectinput.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

  	fprintf(f,"%lf\n",xl);
  	fprintf(f,"%lf\n",yl);
  	fprintf(f,"%lf\n",h);
  	fprintf(f,"%lf\n",el);
  	fprintf(f,"%lf\n",eb);  	

	fprintf(f,"Key:\nlineNo-variable\n1-Xlength\n2-Ylength\n3-Height\n4-Electrode Xlength\n5-Electrode Ylength");
	fclose(f);	
}
