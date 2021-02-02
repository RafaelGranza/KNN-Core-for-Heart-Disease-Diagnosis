#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>

class entity
{
public:
    std::vector<double> values;
    bool positive;
    entity() {};
    ~entity() {};
};
#endif // __ENTITY_H__