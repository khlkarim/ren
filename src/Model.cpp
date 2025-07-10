#include "Model.hpp"

Model::Model()
{
    this->_id = boost::uuids::random_generator()();
    spdlog::info("Loaded model with ID: {}", boost::uuids::to_string(this->_id));
}

Model::~Model()
{
    spdlog::info("Unloaded model with ID: {}", boost::uuids::to_string(this->_id));
}

bool operator==(const Model& m1, const Model& m2) 
{
    return m1._id == m2._id;
}