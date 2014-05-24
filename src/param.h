/*
 * scrm is an implementation of the Sequential-Coalescent-with-Recombination Model.
 * 
 * Copyright (C) 2013, 2014 Paul R. Staab, Sha (Joe) Zhu and Gerton Lunter
 * 
 * This file is part of scrm.
 * 
 * scrm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef scrm_param
#define scrm_param

#include <iostream>
#include <iomanip>      
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <stdlib.h>  
#include <stdio.h>
#include <stdexcept>
#include <memory>

#include "model.h"
#include "summary_statistics/summary_statistic.h"
#include "summary_statistics/tmrca.h"
#include "summary_statistics/first_last_tmrca.h"
#include "summary_statistics/seg_sites.h"
#include "summary_statistics/frequency_spectrum.h"
#include "summary_statistics/newick_tree.h"

#pragma clang diagnostic ignored "-Wdeprecated-register"


class Param {
 public:
 #ifdef UNITTEST
  friend class TestParam;
 #endif

  // Constructors
  Param() : argc_(0), argv_(NULL) { };
  Param(int argc, char *argv[], bool directly_called=true) : argc_(argc), argv_(argv) , directly_called_(directly_called) { }

  // Getters and setters
  bool seg_bool() const { return seg_bool_; }
  void set_seg_bool(const bool seg_bool) { seg_bool_ = seg_bool; } 
  bool execute() const { execute_; }
  void set_execute(const bool execute) { execute_ = execute; } 

  // Other methods
  void init();
  void printHelp(std::ostream& stream);

  friend std::ostream& operator<< (std::ostream& stream, const Param& param);

  void parse(Model &model);
  void print_param();

  // Member variables
  size_t random_seed;  

  template<class T>
  T readNextInput() {
    ++argc_i;

    if (argc_i >= argc_) {
      throw std::invalid_argument(std::string("Not enough parameters when parsing options"));
    }

    char c;
    T input;
    std::stringstream ss(argv_[argc_i]);
    ss >> input;
    if (ss.fail() || ss.get(c)) {
      throw std::invalid_argument(std::string("Failed to parse option: ") + argv_[argc_i]);
    }
    return input;
  }

 private:
  int argc_;
  int argc_i;
  char * const* argv_;
  bool seg_bool_;
  bool directly_called_;
  bool execute_;
};

#endif
