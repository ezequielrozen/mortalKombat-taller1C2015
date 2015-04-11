#include "logger.h"
#include <iostream>
#include <string>

logger::logger(char*  filename, unsigned char baseLevel)
{
    this->baseLevel = baseLevel;
    this->handler = fopen(filename, "a");
}

logger::~logger()
{
    fclose(this->handler);
}

void logger::Log(const char* mensaje, unsigned char level){
    if(0 != (level & this->baseLevel)){
        //obtengo fecha actual
        time_t now = time(0);
        tm* localtm = localtime(&now);
        char fecha[80]; //no sé por qué no cfunciona con char*
        strftime(fecha, sizeof(fecha), "[%Y-%m-%d %X] ", localtm);
        //nivel
        //char* nivel;
        char const *nivel;
        switch(level){//los espacios son importantes
            case ERROR_LEVEL_ERROR:
                nivel = "[ERROR]   ";
                break;
            case ERROR_LEVEL_WARNING:
                nivel = "[WARNING] ";
                break;
            case ERROR_LEVEL_INFO:
                nivel = "[DEBUG]   ";
                break;
        }
        //armo mensaje
        char* linea = new char[ strlen(fecha)+strlen(mensaje) + strlen(nivel)+1 ];
        strcpy(linea, fecha);
        strcat(linea, nivel);
        strcat(linea, mensaje);
        //guardo
        fprintf(this->handler, "%s%c", linea, 10);
    }
}
