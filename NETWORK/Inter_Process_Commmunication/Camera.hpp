#ifndef CAMERA_HPP
#define CAMERA_HPP
#include<iostream>
#include<vector>
#include<csignal> //signal handler
#include<opencv2/opencv.hpp> //opencv. read camera array and image processing.
#include <fcntl.h> // O_CREATE | ORDWR
#include <unistd.h> //ftruncate and close
#include <string.h>  // memcpy
#include <sys/shm.h> //shm_open
#include <sys/mman.h> //mmap
#include <semaphore.h> //

class Camera{
    protected:
        int width, height, refresh_rate;
        int channel;
        size_t buffer;
        cv::VideoCapture cap;
        int camera;

    
    public:
        //protected access
        Camera(int w = 1920, int h = 1080, int rate = 30){
            width = w;
            height = h;
            refresh_rate = rate;
            buffer = w * h * 3;
        }

        //private access
        void Set_Camera(int camera_digit = 0){
            camera = camera_digit;
            cv::VideoCapture capture(camera_digit,cv::CAP_V4L2);
            capture.set(CV_CAP_PROP_FRAME_WIDTH,width);
            capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);
            capture.set(CV_CAP_PROP_FPS, refresh_rate);
            cap = capture;
            return;
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
            std::cout << "buffer: " << buffer << std::endl;
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
class IPC:public Camera{
    public:
        IPC(int w, int h, int rate):Camera(w,h,rate){}
        void Camera_IPC_Product(){
            std::cout << "size of: " << buffer << std::endl;
            
            if(!cap.isOpened()){
                std::cout << "check camera: " << camera << std::endl;
                return;
            }
            void *addr;
            int fd = shm_open("RYAN", O_CREAT | O_RDWR, 0666);
            if(fd == -1){
                std::cout <<"!!! error with shm_open."<< std::endl;
            }
            if(ftruncate(fd,buffer) == -1){
                std::cout<<"ERROR with ftruncate. " << std::endl;
            }
            addr = (mmap(0, buffer, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
            if (addr == MAP_FAILED){
                std::cout <<"!!! error with mmap" << std::endl;
            }
            sem_t *sem = sem_open("time", O_CREAT, 0644,buffer);
            if(sem==SEM_FAILED){
                exit(1);
            }
            bool flag = true;
            int counter = 0;
            signal(SIGINT, &handler);
            cv::Mat frame;
            cv::Mat *frame_ptr = &frame;
            while(true){
                cap >> frame;
                //std::cout << "frame channels: " << frame.channels() << std::endl;
                if(!frame.empty()){
                    Display_Frame_Number(frame,counter);
                    memcpy(addr,frame_ptr -> data,buffer);
                    cv::Mat image(height,width,CV_8UC3,(char*)addr);
                    Show_Frame(image,flag);
                    if(flag == false){
                        break;
                    }
                    munmap(addr,0);
                    counter++;
                }
            }
            cap.release();
            return;
        }

        void Camera_IPC_Consume(){
            int fd = shm_open("RYAN", O_CREAT | O_RDWR, 0666);
            if(fd == -1){
                std::cout<<"ERROR with shm_open. "<< std::endl;
            }

            if(ftruncate(fd,buffer) == -1){
                std::cout<<"ERROR with ftruncate. " << std::endl;
            }
            void *addr;

            addr= static_cast<char *>(mmap(0,buffer,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0));

            sem_t *sem = sem_open("time",0);
            if (sem==SEM_FAILED) {
                std::cout << "EXIT " << std::endl;
                exit(1);
            }
            signal(SIGINT, &handler);
            bool flag = true;
            cv::Mat frame(height,width,CV_8UC3);
            while(true){
                memcpy(frame.data, addr,buffer);
                if(!frame.empty()){
                    Show_Frame(frame,flag);
                    if(flag == false){
                        break;
                    }
                }
                else{
                    std::cout << "NO FRAME" << std::endl;
                }
                munmap(addr,0);
            }
            if(close(fd) == -1){ 
                std::cout<<"ERROR with close." << std::endl;
            }
            sem_unlink("time");
            sem_close(sem);
        }

};

class Video_Record:public IPC{
    public:        
        Video_Record(int w, int h, int rate):IPC(w,h,rate){}
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


