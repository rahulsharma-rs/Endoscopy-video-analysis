#include<iostream>
#include "opencv2/opencv.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h> 
#include<dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;
using namespace cv;

 
int main(int argc, char** argv)
{   int tt,dir_count,t2;
    char st[100],temp[70],buff[70];
   // strcpy(buff1, buff11.c_str());
    /*for reading the directory*/
  ifstream fin;
  string dir, filepath,temp1,b;
  int num,temp_counter=0;
 ofstream myfile; 
 ifstream mfile;
 clock_t clk;
 clk=clock();
  mfile.open("/home/rahul/test/Integrating/counter.txt");
    mfile>>dir_count;
  mfile.close();
 tt=sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/RSS",dir_count);//calculating the directory location
  b=buff;
  DIR *dp;
  struct dirent *dirp;
  struct stat filestat;

//src_base = imread( "/home/rahul/test/blood_detection/test1.jpg", 1 );
  
 //dir = "/home/rahul/test/video_capture_test4_1/video_capture_test4";

dp = opendir( b.c_str() );
  if (dp == NULL)
    {
    cout << "Error(" <<"opening " << dir << endl;
    return 1;
    }

  while ((dirp = readdir( dp )))
    { temp1=dirp->d_name;
    filepath = b + "/" +dirp->d_name ;
    cout<<"my:"<<filepath;
    // If the file is a directory (or is in some way invalid) we'll skip it 
   if (stat( filepath.c_str(), &filestat )) continue;
       if (S_ISDIR( filestat.st_mode ))   continue;
     
    Mat src_frame, filter_frame, image;
    src_frame=imread(filepath);
    cout<<" file path read";
    //filtering the frame to detect red color
    inRange(src_frame, Scalar(33,13,110), Scalar(49,255,189),filter_frame);
    cout<<"\n range calculated\n";
    namedWindow("edges",1);
    imshow("edges",src_frame);
   tt=sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/temp/temp%d.jpg",dir_count,temp_counter);
    imwrite(buff,filter_frame);
    image = imread(buff,CV_LOAD_IMAGE_GRAYSCALE);
    temp_counter++;
    // cvtColor(filter_frame, image, CV_BGR2GRAY);
     cout<<"changed to grey\n";
    //string st="/home/rahul/test/newhisttest/final/image1.jpg";
    //while(d<=index){
    //tt= sprintf(st,"/home/rahul/test/Using_inrange/final/image%d.jpg",d);
    // image = imread(filepath,CV_LOAD_IMAGE_GRAYSCALE);
    //Mat i1=imread(filepath);
    // allcoate memory for no of pixels for each intensity value
    int histogram[256], red_pixel=0, total_pixel=0, outlier_redpixel=0;
    int percent_outlier_pixel=0, percent_red_pixel=0;
 
    // initialize all intensity values to 0
    for(int i = 0; i <= 255; i++)
    {
        histogram[i] = 0;
    }
 
    // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;
    
     for(int i=0;i<256;i++)
	total_pixel= total_pixel + histogram[i];
    outlier_redpixel= histogram[248]+histogram[249]+histogram[250]+histogram[251];
    red_pixel= histogram[252]+histogram[253]+histogram[254]+histogram[255];
    cout<<"total number of pixel :"<<total_pixel<<endl;
    percent_outlier_pixel= (outlier_redpixel*100)/total_pixel;
    percent_red_pixel=(red_pixel*100)/total_pixel;

    tt=sprintf(temp,"/home/rahul/test/Integrating/Samples/sample%d/blood/%s",dir_count,temp1.c_str());
    if(( percent_red_pixel+percent_outlier_pixel)>2){
    imwrite(temp, src_frame);
    }
    tt=sprintf(temp,"/home/rahul/test/Integrating/Samples/sample%d/blood_test_log.txt",dir_count);
    ofstream myfile;
    myfile.open(temp,ios::app);
    myfile<<"For the file "<< filepath<<" the observation is\n";
    myfile<<"Total Pixel"<<"	"<<"Red Pixel"<<"	\% Red pixel"<<"	Outlier redness"<<"		\% OUtlier Redness"<<"\n";
     myfile<<total_pixel<<"		"<<red_pixel<<"			"<<percent_red_pixel<<"\%		"<<outlier_redpixel<<"		"<<percent_outlier_pixel<<"\%\n";
     myfile<<"-----------------------------------------------------------------------------------------------------------------------------------\n";
    //for(int i = 0; i < 256; i++){
        //myfile<<i<<"	"<<histogram[i]<<" \n";
      //  }
   myfile.close();
    // draw the histograms
 //d++;  
}//end of while
 //   waitKey();
    clk= clock() - clk;
    float f = float(clk/CLOCKS_PER_SEC);
    cout<< clk;
    t2= sprintf(buff,"/home/rahul/test/Integrating/Samples/sample%d/time_total.txt",dir_count);
     mfile.open(buff);
     float time_temp =0.0;
     mfile>>time_temp;
     time_temp= time_temp + f;
    
    mfile.close();
 
    myfile.open(buff);
    myfile<<time_temp;
    myfile.close();
    
   myfile.open ("/home/rahul/test/Integrating/Samples/Processing_time_log.txt",ios::app);
   myfile <<"Redness and blood Detection is : "<<f<<"seconds" <<"\n";
   myfile <<"Total Time of execution :"<<time_temp<<" seconds\n";
   myfile<<"-----------------------------------------------------------------------------------------------\n";
  myfile.close();
    return 0;
}
