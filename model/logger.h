#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <time.h>
#include <cstring>

const unsigned char ERROR_LEVEL_ERROR     =   1;
const unsigned char ERROR_LEVEL_WARNING   =   2;
const unsigned char ERROR_LEVEL_INFO      =   4;
const unsigned char ERROR_LEVEL_ALL       = 255;


class logger
{
    public:
        /** Default constructor */
        logger(char* filename, unsigned char baseLevel);
        /** Default destructor */
        ~logger();
        /** Access baseLevel
         * \return The current value of baseLevel
         */
        unsigned int GetbaseLevel() { return baseLevel; }
        /** Set baseLevel
         * \param val New value to set
         */
        void SetbaseLevel(unsigned int val) { baseLevel = val; }
        void Log(const char* mensaje, unsigned char level);
    protected:
    private:
        FILE* handler; //!< Member variable "hadler"
        unsigned int baseLevel; //!< Member variable "baseLevel"
};

#endif // LOGGER_H
