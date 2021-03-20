#pragma once

#include <dlib/clustering.h>
#include <dlib/svm_threaded.h>

constexpr char const separator = ';';
constexpr char const newline = '\n';

constexpr char const* empty_field = ";;";
constexpr char const* zero_str = "0";

constexpr char const* results_file_postfix = "-results";
constexpr char const* model_file_postfix = "-model";

using sample_t = dlib::matrix<double, 7, 1> ;

using ovo_trainer = dlib::one_vs_one_trainer<dlib::any_trainer<sample_t>>;
using poly_kernel = dlib::polynomial_kernel<sample_t>;
using rbf_kernel = dlib::radial_basis_kernel<sample_t>;
