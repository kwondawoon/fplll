/* Copyright (C) 2016 Martin R. Albrecht

   This file is part of fplll. fplll is free software: you
   can redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License as published by the Free Software Foundation,
   either version 2.1 of the License, or (at your option) any later version.

   fplll is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with fplll. If not, see <http://www.gnu.org/licenses/>. */

#include <chrono>
#include <cstring>
#include <fplll.h>
#include <fplll/simd/simd.h>
#include <iostream>

using namespace std;
using namespace fplll;

int test_dotproduct(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD dotproduct: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        double r1 = nonsimd.dot_product(vec1 + i, vec2 + j, n);
        double r2 = simd.dot_product(vec1 + i, vec2 + j, n);
        status |= (r1 / r2) >= 1.000001;
        status |= (r2 / r1) >= 1.000001;
        if (status)
        {
          cout << r1 << " " << r2 << " " << (r1 / r2) << " " << (r2 / r1) << " " << status << endl;
        }
      }
    }
  }
  return status;
}

int test_add(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD add: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        nonsimd.add(vec3 + i + j, vec1 + i, vec2 + j, n);
        simd.add(vec4 + i + j, vec1 + i, vec2 + j, n);
        for (int k = 0; k < n; ++k)
        {
          status |= vec4[i + j + k] != vec3[i + j + k];
        }
        if (status)
        {
          cout << status << endl;
        }
      }
    }
  }
  return status;
}

int test_sub(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD sub: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        nonsimd.sub(vec3 + i + j, vec1 + i, vec2 + j, n);
        simd.sub(vec4 + i + j, vec1 + i, vec2 + j, n);
        for (int k = 0; k < n; ++k)
        {
          status |= vec4[i + j + k] != vec3[i + j + k];
        }
        if (status)
        {
          cout << status << endl;
        }
      }
    }
  }
  return status;
}

int test_addmul(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD addmul: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        nonsimd.addmul(vec3 + i + j, vec1 + i, 3.1, vec2 + j, n);
        simd.addmul(vec4 + i + j, vec1 + i, 3.1, vec2 + j, n);
        for (int k = 0; k < n; ++k)
        {
          status |= vec4[i + j + k] != vec3[i + j + k];
        }
        if (status)
        {
          cout << status << endl;
        }
      }
    }
  }
  return status;
}

int test_addmul2(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD addmul2: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        nonsimd.addmul(vec3 + i + j, 1.1, vec1 + i, 3.1, vec2 + j, n);
        simd.addmul(vec4 + i + j, 1.1, vec1 + i, 3.1, vec2 + j, n);
        for (int k = 0; k < n; ++k)
        {
          status |= vec4[i + j + k] != vec3[i + j + k];
        }
        if (status)
        {
          cout << status << endl;
        }
      }
    }
  }
  return status;
}

int test_givens_rotation(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations nonsimd("sse128d avx256d avx512d");
  SIMD_operations simd(disable_versions);
  cout << "Testing SIMD givens_rotation: " << nonsimd.simd_double_version() << " vs "
       << simd.simd_double_version() << endl;
  status |= nonsimd.simd_double_version() != "nonsimd";
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  double vec5[256];
  double vec6[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = i - i * i;
    vec2[i] = (i * i) / 2 + 5 * i;
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      // ensure we test possible exception cases
      for (int n = 0; n < 3 * 16; ++n)
      {
        if (status)
        {
          cout << i << " " << j << " " << n << ": " << flush;
        }
        nonsimd.givens_rotation(vec3 + i + j, vec4 + i + j, vec1 + i, vec2 + j, 0.5, -0.5, n);
        simd.givens_rotation(vec5 + i + j, vec6 + i + j, vec1 + i, vec2 + j, 0.5, -0.5, n);
        for (int k = 0; k < n; ++k)
        {
          status |= vec5[i + j + k] != vec3[i + j + k];
          status |= vec6[i + j + k] != vec4[i + j + k];
        }
        if (status)
        {
          cout << status << endl;
        }
      }
    }
  }
  return status;
}

int benchmark_dotproduct(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations simd(disable_versions);
  cout << "Benchmarking SIMD dotproduct: " << simd.simd_double_version() << endl;
  double vec1[256];
  double vec2[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = 0.2 - 1.5 * double(i);
    vec2[i] = -6.0 + 0.2 * double(i);
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    cout << "Relative alignment: " << i << ": " << flush;
    auto start = std::chrono::system_clock::now();
    double r   = 0;
    for (int j = 0; j < (1 << 20); ++j)
    {
      r += simd.dot_product(vec1 + i, vec2, 250);
    }
    auto end                          = std::chrono::system_clock::now();
    std::chrono::duration<double> dur = end - start;
    cout << dur.count() * 1000 << "ms (" << r << ")" << endl;
  }
  return status;
}

int benchmark_givens_rotation(const std::string &disable_versions)
{
  int status = 0;
  SIMD_operations simd(disable_versions);
  cout << "Benchmarking SIMD givens_rotation: " << simd.simd_double_version() << endl;
  double vec1[256];
  double vec2[256];
  double vec3[256];
  double vec4[256];
  for (int i = 0; i < 256; ++i)
  {
    vec1[i] = 0.2 - 1.5 * double(i);
    vec2[i] = -6.0 + 0.2 * double(i);
  }
  // ensure we check all possible alignment issues
  for (int i = 0; i < 4; ++i)
  {
    cout << "Relative alignment: " << i << ": " << flush;
    auto start = std::chrono::system_clock::now();
    for (int j = 0; j < (1 << 20); ++j)
    {
      simd.givens_rotation(vec3 + i, vec4, vec1 + i, vec2, 0.6, -0.4, 250);
    }
    auto end                          = std::chrono::system_clock::now();
    std::chrono::duration<double> dur = end - start;
    cout << dur.count() * 1000 << "ms" << endl;
  }
  return status;
}

int main(int argc, char *argv[])
{
  SIMD_operations best_simd;
  int status = 0;
  try
  {
    status |= test_add("");
    status |= test_add("avx512d");
    status |= test_add("avx256d avx512d");
    status |= test_add("sse128d avx256d avx512d");
    status |= test_sub("");
    status |= test_sub("avx512d");
    status |= test_sub("avx256d avx512d");
    status |= test_sub("sse128d avx256d avx512d");
    status |= test_addmul("");
    status |= test_addmul("avx512d");
    status |= test_addmul("avx256d avx512d");
    status |= test_addmul("sse128d avx256d avx512d");
    status |= test_addmul2("");
    status |= test_addmul2("avx512d");
    status |= test_addmul2("avx256d avx512d");
    status |= test_addmul2("sse128d avx256d avx512d");
    status |= test_dotproduct("");
    status |= test_dotproduct("avx512d");
    status |= test_dotproduct("avx256d avx512d");
    status |= test_dotproduct("sse128d avx256d avx512d");
    status |= test_givens_rotation("");
    status |= test_givens_rotation("avx512d");
    status |= test_givens_rotation("avx256d avx512d");
    status |= test_givens_rotation("sse128d avx256d avx512d");
    benchmark_dotproduct("");
    benchmark_dotproduct("avx512d");
    benchmark_dotproduct("avx256d avx512d");
    benchmark_dotproduct("sse128d avx256d avx512d");
    benchmark_givens_rotation("");
    benchmark_givens_rotation("avx512d");
    benchmark_givens_rotation("avx256d avx512d");
    benchmark_givens_rotation("sse128d avx256d avx512d");
  }
  catch (exception &e)
  {
    cerr << "Caught exception: " << e.what() << endl;
    status |= 1;
  }
  if (status == 0)
  {
    cerr << "All tests passed." << endl;
    return 0;
  }
  else
  {
    return -1;
  }

  return 0;
}