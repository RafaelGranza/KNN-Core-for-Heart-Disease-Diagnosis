#ifndef __KNN_CORE_H
#define __KNN_CORE_H

#include "entity.h"
#include <string>
#include <utility>
#include <algorithm>
#include <math.h>
#include <stdio.h> 

class knn_core
{
private:
    std::vector<entity> entitis;
    std::vector<std::pair<double, double>> scale;
    void read_csv(const std::string& csv_path);
public:
    knn_core(const std::string& csv_path);
    ~knn_core() {};
    void normalize(entity& ent);
    void generate_scale(const unsigned index);
    double distance(const entity& ent1, const entity& ent2);
    std::vector<std::pair<double, bool>> distances(entity ent);
    bool classify_1(entity ent, const unsigned k);
    bool classify_2(entity ent, const unsigned k);
};

#endif // __KNN_CORE_H