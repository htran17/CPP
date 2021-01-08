#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<opencv2/opencv.hpp>
#include<csignal>
#include<mutex>
#include<thread>


class ClassCamera{
    public:
        //bool loop = true;
        static void handler(int signum){
            std::cout << "Interrupt signal (" << signum << ") received. " << std::endl;
            exit(signum);
        }
        void CheckOpencvVersion(){
            std::cout << "Opencv version: " << CV_VERSION << std::endl;
            return;
        }
        void DisplayFrameCount(cv::Mat &frame, int &counter){
            std::ostringstream number_frame;
            number_frame << counter ;
            cv::putText(frame, number_frame.str().c_str(), cv::Point(5,50), cv::FONT_HERSHEY_PLAIN, 4, cv::Scalar(0,0,255),2);
        }

        static void CapSetUp(cv::VideoCapture &cap){
            if(!cap.isOpened()){
                std::cout << "check camera 1" << std::endl;
                return;
            }
            
            cap.set(CV_CAP_PROP_MODE, CV_CAP_MODE_BGR);

            cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
            cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
            cap.set(CV_CAP_PROP_FPS, 60);
            std::cout << "FORMAT: " << cap.get(CV_CAP_PROP_MODE )<< ". frame rate: " << cap.get(CV_CAP_PROP_FPS) << ". WIDTH: " 
            << cap.get(CV_CAP_PROP_FRAME_WIDTH) << ". HEIGHT: " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) 
            << std::endl;            
            return;
        }
        void Cap2Frame2Record(cv::VideoCapture &cap, cv::Mat &frame, int record_on){
            cv::VideoWriter record("hello.avi", CV_FOURCC('M','J','P','G'), cap.get(CV_CAP_PROP_FPS),
            cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
            int counter = 0;
            signal (SIGINT, &handler);
            while(true){
                cap >> frame;
                if(!frame.empty()){
                    DisplayFrameCount(frame,counter);
                    counter++;
                    if(record_on){
                        record.write(frame);
                    }
                    cv::imshow("FRAME", frame);
                    int keyboard = cv::waitKey(1);
                    if (keyboard == 'q' || keyboard == 27){
                        break;
                    }
                    if (keyboard == 'p' || keyboard == 112){
                        cv::waitKey(0);
                    }
                }
            }
            cap.release();
            return;
        }

        void RecordVideo(cv::VideoCapture &cap, cv::Mat &frame){
            cv::VideoWriter record("hello.avi", CV_FOURCC('H','2','6','4'), cap.get(CV_CAP_PROP_FPS),
            cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH),cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
            signal (SIGINT, &handler);

            while(true){
                cap >> frame;
                record.write(frame);
                int keyboard = cv::waitKey(1);
                if (keyboard == 'q' || keyboard == 27){
                    break;
                }
                if (keyboard == 'p' || keyboard == 112){
                     cv::waitKey(0);
                }
            }
            cap.release();
            return;
        }

        void Capture(){
            cv::VideoCapture cap(2, cv::CAP_V4L2);
            if(!cap.isOpened()){
                std::cout << "check camera 1" << std::endl;
                return;
            }
            cap.set(CV_CAP_PROP_FRAME_WIDTH,1920);
            cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);
            cap.set(CV_CAP_PROP_FPS, 30);

            std::cout << "frame rate: " << cap.get(CV_CAP_PROP_FPS) << ". WIDTH: " 
            << cap.get(CV_CAP_PROP_FRAME_WIDTH) << ". HEIGHT: " << cap.get(CV_CAP_PROP_FRAME_HEIGHT) 
            << std::endl;
            signal (SIGINT, &handler);
            while(true){
                cv::Mat frame;
                cap >> frame;
                if(!frame.empty()){
                    cv::imshow("FRAME", frame);
                    int keyboard = cv::waitKey(1);
                    if (keyboard == 'q' || keyboard == 27){
                        break;
                    }
                    if (keyboard == 'p' || keyboard == 112){
                        cv::waitKey(0);
                    }
                }
            }
            cap.release();
            return;

            
        }

        
};

int main(){
    ClassCamera Ryan;
    ClassCamera* Ryan_ptr;
    cv::VideoCapture cap(2, cv::CAP_V4L2);
    cv::Mat frame;
    Ryan_ptr -> CheckOpencvVersion();

    Ryan_ptr -> CapSetUp(cap);
    
    Ryan_ptr -> Cap2Frame2Record(cap,frame,1);
    
    return 0;
}


