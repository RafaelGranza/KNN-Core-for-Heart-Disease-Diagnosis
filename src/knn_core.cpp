#include "knn_core.h"

knn_core::knn_core(const std::string& csv_path = "scr/heart.csv") 
{
    read_csv(csv_path);
    if(entitis.size() < 1) return;
    for(unsigned i = 0; i < entitis[0].values.size(); ++i)
    {
        generate_scale(i);
    }
    for(auto& e: entitis)
    {
        normalize(e);
    }
}

void knn_core::normalize(entity& ent) 
{
    for(unsigned i = 0; i < ent.values.size(); ++i)
    {
        ent.values[i] *= scale[i].first;
        ent.values[i] += scale[i].second;
    }
}

void knn_core::generate_scale(const unsigned index) 
{
    double max_value = entitis[0].values[index];
    double min_value = entitis[0].values[index];
    for(auto ent: entitis)
    {
        max_value = std::max(max_value, ent.values[index]);
        min_value = std::min(min_value, ent.values[index]);
    }
    const double a = 1/(max_value - min_value);
    const double b = - min_value * a;
    scale[index].first  = a;
    scale[index].second = b;
}

double knn_core::distance(const entity& ent1, const entity& ent2) 
{
    double dist = 0;
    for(unsigned i = 0; i < ent1.values.size(); ++i)
    {
        dist += (ent1.values[i]-ent2.values[i]) * (ent1.values[i]-ent2.values[i]); 
    }
    dist = sqrt(dist);
    return dist;
}

std::vector<std::pair<double, bool>> knn_core::distances(entity ent) 
{
    std::vector<std::pair<double, bool>> distances;
    normalize(ent);
    for(auto e: entitis)
    {
        distances.push_back({distance(e, ent), e.positive});
    }
    sort(distances.begin(), distances.end());
    return  distances;
}

bool knn_core::classify_1(entity ent, const unsigned k = 1)
{
    std::vector<std::pair<double, bool>> dists = distances(ent);

    int positives = 0;
    int negatives = 0;
    for(unsigned i = 0; i < k; ++i)
    {
        (dists[i].second)? ++positives: ++negatives;
    }

    return positives >= negatives;
}

bool knn_core::classify_2(entity ent, const unsigned k) 
{
    std::vector<std::pair<double, bool>> dists = distances(ent);

    double prob = 0;
    double total_distance = 0;
    double max_v = dists[k].first;
    for(unsigned i = 0; i < k; ++i)
    {
        total_distance += max_v - dists[i].first;
        if (dists[i].second)
        {
            prob += max_v - dists[i].first;
        }
    }

    return std::round(prob/total_distance); 
}


void knn_core::read_csv(const std::string& csv_path) 
{
    FILE* file = fopen(csv_path.c_str(),"r");
    char header[512];
    fscanf(file, "%s\n", header);
    
    entitis.push_back(entity());
    double buf_d;
    char buf_c;
    while (fscanf(file, "%lf%c", &buf_d, &buf_c) == 2)
    {
        entitis.back().values.push_back(buf_d);
        if (buf_c != ',')
        {
            entitis.back().positive = buf_d;
            entitis.back().values.pop_back();
            entitis.push_back(entity());
            scale.push_back({0,0});
        }
    }
    entitis.pop_back();
    scale.pop_back();
    free(file);
}
