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

#define image_size 1920*1080*3



class Camera{
    protected:
        int camera = 0;
        int width = 1920, height = 1080, refresh_rate = 30;
        cv::VideoCapture cap;
        char buffer[image_size];

        
        
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
            int size_image = frame_width * frame_height * 3;
            //char buffer1[size_image];

            //buffer[size_image];
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

        void Camera_IPC_Product(){
            if(!cap.isOpened()){
                std::cout << "check camera: " << camera << std::endl;
                return;
            }
            int counter = 0;
            
            void *addr;
            int fd = shm_open("RYAN", O_CREAT | O_RDWR, 0666);
            if(fd == -1){
                std::cout <<"!!! error with shm_open."<< std::endl;
            }

            if(ftruncate(fd,sizeof(buffer)) == -1){
                std::cout<<"ERROR with ftruncate. " << std::endl;
            }

            addr = static_cast<char *>(mmap(0, sizeof(buffer), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));

            if (addr == MAP_FAILED){
                std::cout <<"!!! error with mmap" << std::endl;
            }

            sem_t *sem = sem_open("time", O_CREAT, 0644,sizeof(buffer));
            if(sem==SEM_FAILED){
                exit(1);
            }
            bool flag = true;
            signal(SIGINT, &handler);
            cv::Mat frame;
            cv::Mat *frame_ptr = &frame;

            while(true){
                cap >> frame;
                //std::cout << "frame channels: " << frame.channels() << std::endl;
                if(!frame.empty()){
                    Display_Frame_Number(frame,counter);
                    memcpy(addr,frame_ptr -> data,sizeof(buffer));
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

            void *addr;
            addr= static_cast<int *>(mmap(0,sizeof(buffer),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0));
            sem_t *sem = sem_open("time",0);
            if (sem==SEM_FAILED) {
                std::cout << "EXIT " << std::endl;
                exit(1);
            }
            signal(SIGINT, &handler);
            bool flag = true;
            while(true){
                cv::Mat frame;
                memcpy(&frame, &addr,sizeof(buffer));
                cv::Mat image(480,640, CV_8UC3,(uchar*)addr);
                munmap(addr,0);
                if(!frame.empty()){
                    Show_Frame(image, flag);
                    if(flag == false){
                        break;
                    }
                }
                
            }
            if(close(fd) == -1){ 
                std::cout<<"ERROR with close." << std::endl;
            }
   
            sem_unlink("time");
   
            sem_close(sem);
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


