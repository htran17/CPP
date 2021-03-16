#ifndef CAMERA_HPP
#define CAMERA_HPP
#include<iostream>
#include<vector>
#include<csignal> //signal handler
#include<opencv2/opencv.hpp> //opencv. read camera array and image processing.

class Camera{
    protected:
        int camera = 0;
        int width = 1920, height = 1080, refresh_rate = 30;
        cv::VideoCapture cap;
        
        
    public:
        Camera(int camera_digit = 0, int frame_width = 1920, int frame_height = 1080, int frame_rate = 30){
            camera = camera_digit;
            width = frame_width;
            height = frame_height;
            refresh_rate = frame_rate;
            cv::VideoCapture capture(camera_digit,cv::CAP_V4L2);
            capture.set(CV_CAP_PROP_FRAME_WIDTH,frame_width);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT, frame_height);
            capture.set(CV_CAP_PROP_FPS, frame_rate);
            cap = capture;
            
        }


        //check OpenCV version
        void Check_OpenCV_Version(){
            std::cout << "OPENCV VERSION: " << CV_VERSION << std::endl;
            return;
        }
        //quit the infinity while loop in multithreading
        static void handler(int signum){
            std::cout <<"Interrupt Signal: " << signum << std::endl;
            exit(signum);
        }
        //display frame number in video frame.
        void Display_Frame_Number(cv::Mat &frame, int &counter){
            std::ostringstream number_frame;
            number_frame << counter;
            cv::putText(frame,number_frame.str().c_str(), cv::Point(5,50), cv::FONT_HERSHEY_PLAIN, 4 , cv::Scalar(0,0,255),2);
            return;
        }
        //display image
        void Show_Frame(cv::Mat &frame, bool &flag){
            cv::imshow("FRAME", frame);
            int keyboard = cv::waitKey(1);
            if (keyboard == 'q' || keyboard == 27){
                flag = false;
            }
            if (keyboard == 'p' || keyboard == 112){
                cv::waitKey(0);
            }
            
        }

        //read image and display it.
        void Capture(bool display = true){
            if(!cap.isOpened()){
                std::cout << "check camera: " << camera << std::endl;
                return;
            }
            signal(SIGINT, &handler);
            int counter = 0;
            bool flag = true;// pass boolean to show frame function to exit the program. 
            bool terminal = true;

            while(true){
                cv::Mat frame;
                cap >> frame;
                
                if(!frame.empty()){
                    Display_Frame_Number(frame,counter);
                    counter++;

                    if(display == true){
                        Show_Frame(frame, flag);
                        if(flag == false){
                            break;
                        }
                    }
                    
                }
                
            }
            cap.release();
            return;
            
        }

};

class Video_Record:public Camera{
    public:
        Video_Record(int camera_digit = 0, int frame_width = 1920, 
        int frame_height = 1080, int frame_rate = 30):Camera(camera_digit, 
        frame_width, frame_height, frame_rate){}
        
        //reord a video.
        void Record(bool record_on = true, bool display = true ){
            cv::VideoWriter record("hello.avi", CV_FOURCC('M','J','P','G'), cap.get(CV_CAP_PROP_FPS),
            cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
            int counter = 0;
            bool flag = true;
            signal (SIGINT, &handler);
            while(true){
                cv::Mat frame;
                cap >> frame;
                if(!frame.empty()){
                    Display_Frame_Number(frame,counter);
                    counter++;
                    if(record_on){
                        record.write(frame);
                    }
                    if(display == true){
                        Show_Frame(frame, flag);
                        if(flag == false){
                            break;
                        }
                    }
                    
                }
            }
            cap.release();
            return;
        }

};


#endif


