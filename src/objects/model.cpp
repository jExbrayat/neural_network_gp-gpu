#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xrandom.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <optional>

using namespace std;
using namespace xt;

// Define class structure
class Model
{
public:
    // Constructor
    Model(const vector<int> &architecture, const int &input_size);

    // Methods
    void load_weights(const string &path);
    void load_loss(const string &path);
    void save_weights(const string &path) const;
    void save_loss(const string &path) const;
    void fit(const xarray<double> &x_train, const xarray<double> &y_train, const int &epochs, const int &batch_size, const float &learning_rate);
    xarray<double> predict(const xarray<double> &x_test) const;

protected:
    vector<int> architecture; // Define the neural network architecture
    int input_size; // Define the input size of the data to fit predict
    vector<xarray<double>> weights; // Define vector of tensors for making operations on weights
    vector<xarray<double>> biases; // Define vector of tensors for making operations on biases
    vector<double> loss_history; // Store the loss over epochs

    void initialize_weights(); // Initialize weights. Used if no weights loaded
};

// Define class constructor
Model::Model(const vector<int> &architecture, const int &input_size) : architecture(architecture), input_size(input_size)
{
    // Define constructor for Model: architecture on the left is the object's member, on the right
    // is the constructor argument
    initialize_weights();
}

// Write class functions

void Model::initialize_weights()
// Set weights biases with random normal distribution
{
    weights.push_back(xt::random::randn<double>({architecture[0], input_size}));
    biases.push_back(xt::random::randn<double>({architecture[0], 1}));

    for (size_t l = 1; l < architecture.size(); l++) {
        xt::xarray<double> w = xt::random::randn<double>({architecture[l], architecture[l - 1]});
        xt::xarray<double> b = xt::random::randn<double>({architecture[l], 1});
        weights.push_back(w);
        biases.push_back(b);
    }
}

void Model::load_weights(const string &path)
{
    // Implement loading weights from a file
}

void Model::load_loss(const string &path)
{
    // Implement loading loss from a file
}

void Model::save_weights(const string &path) const
{
    // Implement saving weights to a file
}

void Model::save_loss(const string &path) const
{
    // Implement saving loss to a file
}

// void Model::fit(const xarray<double> &x_train, const xarray<double> &y_train, const unsigned int &epochs, const unsigned int &batch_size, const float &learning_rate)
// {
//     TODO: use GradientDescent class
//     for (int epoch = 0; epoch < epochs; ++epoch)
//     {
//         backpropagate(x_train, y_train, learning_rate);
//         // Track and store loss for each epoch
//         loss_history.push_back(0.0); // Placeholder, replace with actual loss calculation
//     }
// }

// xarray<double> Model::predict(const xarray<double> &x_test) const
// {
//     xarray<double> a = x_test;
//     for (size_t l = 0; l < weights.size(); ++l)
//     {
//         a = sigmoid(xt::linalg::dot(weights[l], a) + biases[l]);
//     }
//     return a;
// }