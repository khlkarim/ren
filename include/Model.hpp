#ifndef MODEL_HPP
#define MODEL_HPP

#include <string>
#include <spdlog/spdlog.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Transform.hpp"

class Model
{
public:
    Model();
    virtual ~Model();
    friend bool operator==(const Model& m1, const Model& m2);

private:
    boost::uuids::uuid _id;
    std::wstring _path;
    Transform transform;
};

#endif // MODEL_HPP