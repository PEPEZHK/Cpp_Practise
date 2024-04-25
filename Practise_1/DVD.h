#ifndef C_DVD_H
#define C_DVD_H
#include <iostream>
#include "string"
class DVD
        {
        public:
            DVD() ;
            DVD(const std::string serialNo, const std::string title, const std::string director) ;
            ~DVD() ;

            std::string getNo() ;
            std::string getDir() ;
            std::string getTitle() ;
            void setTitle(const std::string title) ;
            void setNo(const std::string serialNo) ;
            void setDirector(const std::string director) ;
            void setAvailability(const bool state) ;
            void toString() ;
            bool isAvailable() ;
        private:
            std::string no ;
            std::string title ;
            std::string dir ;
            bool available ;
        };
#endif
