/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * You may add other functions if you wish, but this template function
 * is the only one that need to be exposed for the testing code.
 * 
 * Authors: C. Painter-Wakefield & Tolga Can
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <cstddef>
#include <vector>

using namespace std;

template <class T>
void sorter(vector<T> &vec, int k) 
{  
	// write your solution for k-way merge sort below	
	if(vec.size() <= 1) { return; }
	if((int)vec.size() < k) { k = (int)vec.size(); }

	// split the list
	vector<vector<T>> vectorList;
	for(int i = 0; i < k; i++)
	{
		vector<T> nextVec;
		vectorList.push_back(nextVec);
	}
	for(size_t i = 0; i < vec.size(); i++)
	{
		vectorList.at(i % vectorList.size()).push_back(vec.at(i));
	}

	// call sort on each list
	for(int i = 0; i < (int)vectorList.size(); i++)
	{
		sorter(vectorList.at(i), k);
	}

	// sort the list
	vector<int> indices;
	for(int i = 0; i < (int)vectorList.size(); i++)
	{
		indices.push_back(0);
	}
	T mini;
	int index = 0;
	vector<T> fin;
	for(int i = 0; i < (int)vec.size(); i++)
	{
		for(int j = 0; j < (int)vectorList.size(); j++)
		{
			if( indices.at(j) < (int)vectorList.at(j).size() )
			{
				mini = vectorList.at(j).at(indices.at(j));
				index = j;
				break;
			}
		}
		for(int j = 0; j < (int)vectorList.size(); j++)
		{
			if( indices.at(j) < (int)vectorList.at(j).size() && vectorList.at(j).at(indices.at(j)) < mini )
			{
				mini = vectorList.at(j).at(indices.at(j));
				index = j;
			}
		}
		indices.at(index) = indices.at(index) + 1;
		fin.push_back(mini);
	}

	vec = fin;

}
#endif
