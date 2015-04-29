#include <opencv\cv.h>
#include <opencv\highgui.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
    {
        // Image matrix
        Mat img;
        Mat result;
        //---------------------------------------------
        //
        //---------------------------------------------
        namedWindow("Source Image");

        namedWindow("Result");
        // Load image in grayscale mode
        img=imread("C:\\Users\\Rohini\\Desktop\\Images\\monkey1.jpg",0);
        img.convertTo(img,CV_32FC1,1.0/255.0);
        cout << "Source size:" << img.rows*img.cols <<" elements "<< endl;
        // create SVD 
        cv::SVD s;
        // svd result
        Mat w,u,vt;
        // computations ...
        s.compute(img,w,u,vt);

        // collect Sigma matrix (diagonal - is eigen values, other - zeros)
        // we got it in as vector, transform it to diagonal matrix
        Mat W=Mat::zeros(w.rows,w.rows,CV_32FC1);       
        for(int i=0;i<w.rows;i++)
        {
            W.at<float>(i,i)=w.at<float>(i);
        }
		
		for(int i=0;i<w.rows;i++)
		{
		  cout << "value:" << W.at<float>(i,i) << endl;
		}

        // reduce rank to k
        int k=25;
        W=W(Range(0,k),Range(0,k));
        u=u(Range::all(),Range(0,k));
        vt=vt(Range(0,k),Range::all());

        // Get compressed image
        result=u*W*vt;
        cout << "Result size:" << u.rows*u.cols+k+vt.rows*vt.cols <<" elements "<< endl;
        //---------------------------------------------
        //
        //--------------------------------------------- 
        imshow("Source Image", img);
        imshow("Result", result);
        cvWaitKey(0);
        return 0;
    }










