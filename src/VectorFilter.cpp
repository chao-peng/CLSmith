// -*- mode: C++ -*-
//
// Copyright (c) 2007, 2008, 2009, 2010, 2011 The University of Utah
// All rights reserved.
//
// This file is part of `csmith', a random generator of C programs.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "VectorFilter.h"

#include <functional>
#include <algorithm>
#include "ProbabilityTable.h"

using namespace std;

VectorFilter::VectorFilter(void) 
	: ptable(NULL), 
	  flag_(FILTER_OUT) 
{
	//Nothing to do
}

VectorFilter::VectorFilter(DistributionTable *table) 
	: ptable(table), 
	  flag_(FILTER_OUT) 
{
	//Nothing to do
}

VectorFilter::VectorFilter(std::vector<unsigned int> &vs, int flag) 
	: vs_(vs),
	  ptable(NULL),
	  flag_(flag) 
{
	//Nothing to do
}

VectorFilter::~VectorFilter(void)
{
	//Nothing to do
}

bool
VectorFilter::filter(int v) const
{
	if (!this->valid_filter())
		return false;
 
	v = lookup(v); 
	bool re = std::find(vs_.begin(), vs_.end(), static_cast<unsigned int>(v)) != vs_.end();
	return (flag_ == FILTER_OUT) ? re : !re;
}

VectorFilter&
VectorFilter::add(unsigned int item)
{ 
	if (std::find(vs_.begin(), vs_.end(), item) == vs_.end()) {
		vs_.push_back(item); 
	}
	return *this;
}

int 
VectorFilter::get_max_prob(void) const 
{
	return ptable ? ptable->get_max() : 100;
}

int
VectorFilter::lookup(int v) const
{
	if (!this->valid_filter() || ptable == NULL)
		return v; 
	return v = ptable->rnd_num_to_key(v);
}
