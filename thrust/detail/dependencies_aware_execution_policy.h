/*
 *  Copyright 2018 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/detail/cpp11_required.h>

#if THRUST_CPP_DIALECT >= 2011

#include <tuple>

#include <thrust/detail/execute_with_dependencies.h>
#include <thrust/detail/type_deduction.h>

namespace thrust
{
namespace detail
{

template<template<typename> class ExecutionPolicyCRTPBase>
struct dependencies_aware_execution_policy
{
    template<typename ...Dependencies>
    using execute_with_dependencies_type = thrust::detail::execute_with_dependencies<
        ExecutionPolicyCRTPBase,
        Dependencies...
    >;

    template<typename ...Dependencies>
    __host__
    execute_with_dependencies_type<Dependencies...>
    after(Dependencies&& ...dependencies) const
    {
        return { THRUST_FWD(dependencies)... };
    }

    template<typename ...Dependencies>
    __host__
    execute_with_dependencies_type<Dependencies...>
    after(std::tuple<Dependencies...>&& dependencies) const
    {
        return { std::move(dependencies) };
    }
};

} // end detail
} // end thrust

#endif // THRUST_CPP_DIALECT >= 2011
