#include <iostream>

#include <cv.h>
#include <highgui.h>

unsigned int n_used = 0;

bool use_this_frame(unsigned int n)
{
    /*unsigned int n_start = 4022 + 285;// + 17;
    unsigned int n_stop = n_start + 658;
    unsigned int n_step = 20; */
    unsigned int n_start = 2526;
    unsigned int n_stop = 4011;
    
/*    if(n >= n_start && n <= n_stop && ((n - n_start) % n_step == 0))
    {
        return true;
        } */
    // 114   134   153   173
    // 23    38    54    69    85
    // 72    91   110   129

    if(n >= n_start && n <= n_stop)
    {
        n = n - n_start;
//        if(n == 114 || n == 134 || n == 153 || n == 173)
//        if(n == 23 || n == 38 || n == 54 || n == 69)
        if(n == 72 || n == 91 || n == 110 || n == 129)
        {
            n_used++;
            return true;
        }
    }

    return false;
}

int main(int argc, char** argv)
{

    const char* filename = "T25_C6_3L.dv";
    const char* bg_filename = "background.bmp";
    const char* out_filename = "composite.bmp";

    const unsigned int threshold = 10;

    CvCapture* capture = cvCaptureFromFile(filename);

    const unsigned int frame_height =
        (unsigned int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT);
    const unsigned int frame_width =
        (unsigned int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH);
    const unsigned int num_frames =
        (unsigned int) cvGetCaptureProperty(capture, CV_CAP_PROP_FRAME_COUNT);

    const CvSize frame_size = cvSize(frame_width, frame_height);

    unsigned int cur_frame_number = 0;
    IplImage* cur_frame = NULL;

    IplImage* bg_frame_orig = cvLoadImage(bg_filename);
    
    IplImage* bg_frame = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);
    cvCvtColor(bg_frame_orig, bg_frame, CV_RGB2GRAY);
    
    IplImage* gs_frame = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);
    IplImage* diff_frame = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);
    IplImage* thresh_frame = cvCreateImage(frame_size, IPL_DEPTH_8U, 1);    

    IplImage* composite_frame = cvCloneImage(bg_frame_orig);

    while(cur_frame = cvQueryFrame(capture))
    {
        cur_frame_number++;        
        if(!use_this_frame(cur_frame_number))
        {
            continue;
        }

        cvCvtColor(cur_frame, gs_frame, CV_RGB2GRAY);

		cvCmp(bg_frame, gs_frame, thresh_frame, CV_CMP_GT);
		cvSub(bg_frame, gs_frame, diff_frame);
		cvAnd(diff_frame, thresh_frame, diff_frame);

        cvThreshold(diff_frame,
                    thresh_frame,
                    threshold,
                    255.0,
                    CV_THRESH_BINARY);

        cvSmooth(thresh_frame, thresh_frame, CV_MEDIAN, 5);
        
        cvNamedWindow("Threshold");
        cvShowImage("Threshold", thresh_frame);
        cvWaitKey(1);

        cvCopy(cur_frame, composite_frame, thresh_frame);
        
    }

    cvSaveImage(out_filename, composite_frame);
    
    cvReleaseImage(&composite_frame);
    cvReleaseImage(&thresh_frame);            
    cvReleaseImage(&diff_frame);        
    cvReleaseImage(&gs_frame);    
    cvReleaseImage(&bg_frame);
    cvReleaseImage(&bg_frame_orig);    
    
    cvReleaseCapture(&capture);

    std::cout << "Used " << n_used << std::endl;

    return(0);
    
}
