#include "headers/general.hpp"
#include "headers/tempMeasure.hpp"
#include "headers/display.hpp"
#include "headers/checkGrowth.hpp"

int main() {
    
    float temp;
    double size, initialSize;
    dados *growth;
    growth = (dados*) malloc(sizeof(dados));
    growth->quantityMeans = 1;
    growth->quantityMeasures = 1;
    growth->quantityVars = 1;
    growth->growthStop = 1;
    pthread_t p_temp, p_size, p_growth;
    pthread_create(&p_size, NULL, &webcamShot, &size);
    pthread_join(p_size, NULL);
    initialSize = size;
    while(growth->growthStop){
        pthread_create(&p_temp, NULL, &tempMeasure, &temp);
        pthread_create(&p_size, NULL, &webcamShot, &size);
        pthread_join(p_size, NULL);
        growth->sizeX=size;
        pthread_create(&p_growth, NULL, &sizeBread, growth);
        pthread_join(p_temp, NULL);
        pthread_join(p_growth,NULL);
        system("clear");
        std::cout << "------------------------------------------" << std::endl;
        std::cout << "|     Bread Growth: " << ((size / initialSize) * 100) - 100 << "%        |" << std::endl;
        //std::cout << "|     Bread Area: " << size << "         |" << std::endl;
        std::cout << "|     Temperature: " << temp << "        |" << std::endl;
        std::cout << "------------------------------------------" << std::endl;
    }
    return 0;
}
