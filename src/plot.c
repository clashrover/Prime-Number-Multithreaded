#include <stdlib.h>
#include <stdio.h>

int main()
{
    // plotting the graph.
	FILE* gnuplotpipe = popen("gnuplot -persistent","w");
	char* s[] = {"set title \"Plot of Thread Num vs Time(s)\"","set style data histograms","set style fill solid","set boxwidth 0.3", "set xlabel \"Thread Num\"","set ylabel \"Time(s)\"", "set term png" ,"set output \"./output/graph.png\"" ,"plot './output/naive_time.data'  title \"Naive\" , './output/load_time.data'  title \"Load\" " };
	for(int i=0;i<9;i++){
		fprintf(gnuplotpipe,"%s\n",s[i]);	
	}
	fflush(gnuplotpipe);
	fclose(gnuplotpipe);
}