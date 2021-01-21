/**
 * @file compareHist_Demo.cpp
 * @brief Sample code to use the function compareHist
 * @author OpenCV team
 */
//#include "opencv2/opencv.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
#include <stdio.h>

#include<string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
using namespace cv;

/**
 * @function main
 */
int main( int argc, char** argv)
{   
    Mat src_base, hsv_base;
    Mat src_test1, hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down, frame;
    int t,t1,t2,t3, num=1,dup_num=0,counter=0,dir_count,frame_count,number=0;
    char base_buff[70], temp_buff[70], buff[70],buff1[70],buff2[70];
    clock_t clk;
    ofstream myfile;
    
    clk= clock();
   //strcpy(buff10,buff110.c_str());
   /// Load three images with different environment settings
  /* if( argc < 4 )
     { printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
       return -1;
     }*/

/*for reading the directory*/
/*  ifstream fin;
  string dir, filepath;
  int num;
  DIR *dp;
  struct dirent *dirp;
  struct stat filestat;

src_base = imread( "/home/rahul/test/blood_detection/test1.jpg", 1 );
  
 dir = "/home/rahul/test/video_capture_test4_1/video_capture_test4";

dp = opendir( dir.c_str() );
  if (dp == NULL)
    {
    cout << "Error(" <<"opening " << dir << endl;
    return 1;
    }

*/ifstream mfile;
  mfile.open("/home/rahul/test/Integrating/counter.txt");
    mfile>>dir_count;
  mfile.close();
 
    //retrieving the number of files
    t=sprintf(buff2,"/home/rahul/test/Integrating/Samples/sample%d/frame_count.txt",dir_count);
   mfile.open(buff2);
   mfile>>frame_count;
   cout<<frame_count;
   mfile.close();
   t=sprintf(buff2,"/home/rahul/test/Integrating/Samples/sample%d/RSS",dir_count);
    const char* buff3= buff2;
    cout<<buff3;
    mkdir(buff3,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);//creating the directory
  for(int x=2;x<frame_count-2 ; x++){
/*while ((dirp = readdir( dp )))
    {
    filepath = dir + "/" + dirp->d_name;

    // If the file is a directory (or is in some way invalid) we'll skip it 
   // if (stat( filepath.c_str(), &filestat )) continue;
   // if (S_ISDIR( filestat.st_mode ))         continue;*/



   t= sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/image%d.jpg",dir_count,num);
   src_base = imread(buff , 1 );
   cout<<"path of base image :"<< buff<<endl;
   
   t1= sprintf(temp_buff,"/home/rahul/test/Integrating/Samples/sample%d/image%d.jpg",dir_count,x);
   src_test1 = imread( temp_buff, 1 );
   cout<<"path of comp image :"<<temp_buff<<endl;
   src_test2 = imread( "/home/rahul/test/Histogram_comparison/test21.jpg", 1 );

   /// Convert to HSV
   cvtColor( src_base, hsv_base, CV_BGR2HSV );
   cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
   cvtColor( src_test2, hsv_test2, CV_BGR2HSV );

   hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );

   /// Using 30 bins for hue and 32 for saturation
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };

    // hue varies from 0 to 256, saturation from 0 to 180
    float s_ranges[] = { 0, 256 };
    float h_ranges[] = { 0, 180 };

    const float* ranges[] = { h_ranges, s_ranges };

    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };


    /// Histograms
    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;

    /// Calculate the histograms for the HSV images
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
    normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );
     int i = 3;
    /// Apply the histogram comparison methods
   // for( int i = 0; i < 4; i++ )
        int compare_method = 3 ;
         double base_base = compareHist( hist_base, hist_base, compare_method );
         double base_half = compareHist( hist_base, hist_half_down, compare_method );
         double base_test1 = compareHist( hist_base, hist_test1, compare_method );
         double base_test2 = compareHist( hist_base, hist_test2, compare_method );
         
         printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
	dup_num=num;
	if(base_test1>0.27){
	number++;
	num= x-1;
	t2= sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/RSS/image%d.jpg",dir_count,num);
	imwrite(buff, src_base);	
	}
 	/*if(base_test2<0.6){
	t3= sprintf(buff1,"/home/rahul/test/Histogram_comparison/matchofsample1/image%d.jpg",num);	      
	imwrite(buff1, src_base);
	}
	*/
       t2= sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/Sample_Space_Reduction_log.txt",dir_count);
      
  myfile.open (buff,ios::app);
        if(num==dup_num){
	counter++;
	myfile << "image"<<num<<"----->"<<"image"<<x<<"---->"<<base_test1<<"\n";
	}else {
	myfile << "image"<<num<<"----->"<<"image"<<x<<"---->"<<base_test1<<"---->"<<counter<<"\n";
	counter=0;
	}
  myfile.close();

  
}//end of for// while 
//closedir( dp );
    clk= clock() - clk;
    float f = float(clk/CLOCKS_PER_SEC);
    cout<< clk;
    t2= sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/time_total.txt",dir_count);
cout<<buff<<endl;     
mfile.open(buff);
     int time_temp=0;
     mfile>>time_temp;
     cout<<time_temp<<endl;
     time_temp= time_temp + f;
 
    mfile.close();
 
    myfile.open(buff);
    myfile<<time_temp;
    myfile.close();
    
   myfile.open ("/home/rahul/test/Integrating/Samples/Processing_time_log.txt",ios::app);
   myfile <<"the "<<number<<" frames of Reduced Sample Space in obtained in : "<<f<<"seconds for"<<"\n";
   myfile.close();
   printf( "Done \n" );
return 0;
    
}
