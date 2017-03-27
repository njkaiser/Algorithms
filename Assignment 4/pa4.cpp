// REQUIRED FILE: kargerMinCut.txt

// The file contains the adjacency list representation of a simple undirected
// graph. There are 200 vertices labeled 1 to 200. The first column in the file
// represents the vertex label, and the particular row (other entries except
// the first column) tells all the vertices that the vertex is adjacent to.
// So for example, the 6th row looks like : "6 155 56 52 120 ......". This
// just means that the vertex with label 6 is adjacent to (i.e., shares an
// edge with) the vertices with labels 155, 56, 52, 120,......, etc.

// Your task is to code up and run the randomized contraction algorithm for
// the min cut problem and use it on the above graph to compute the min cut.
// (HINT: Note that you'll have to figure out an implementation of edge
// contractions. Initially, you might want to do this naively, creating a
// new graph from the old every time there's an edge contraction. But you
// should also think about more efficient implementations.) (WARNING: As per
// the video lectures, please make sure to run the algorithm many times with
// different random seeds, and remember the smallest cut that you ever find.)
// Write your numeric answer in the space provided. So e.g., if your answer
// is 5, just type 5 in the space provided.

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>    // lots of stuff
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand



class KargerMinCut
{
private:
  // create public class copy of graph, so we don't have to pass it around or ruin the original
  int m_size; // number of nodes
  std::vector<std::vector<int> > m_graph;
  std::vector<int> remaining_nodes;
  // std::vector<int> random_indices;


  int GetRandomEntry()
  {


  }

  // void randomize()
  // {
  //   // create randomized index list for selecting which nodes to combine
  //   int i = 1;
  //   random_indices.resize(m_size);
  //   for(auto it = random_indices.begin(); it != random_indices.end(); ++it)
  //   {
  //     *it = i; // fill random_indices with values 0 to length
  //     // std::cout << *it << std::endl;
  //     ++i;
  //   }
  //   std::random_shuffle(random_indices.begin(), random_indices.end()); // randomize which nodes we combine
  //
  //   // verify everything looks good;
  //   // for(auto it = random_indices.begin(); it != random_indices.end(); ++it)
  //   // {
  //   //   std::cout << *it << std::endl;
  //   // }
  // }

  // int ElementExists(int val)
  // {
  //   if(std::find(remaining_nodes.begin(), remaining_nodes.end(), val) != remaining_nodes.end())
  //     return 0; // return false if value exists
  //   else
  //     return 1; // true otherwise
  // }


  int combine2nodes()//int index1, int index2)
  {
    std::srand(std::time(0)); // seed rand functions

    // generate 2 random, exclusive indices from remaining_nodes
    int index1 = rand() % (remaining_nodes.size()-1);
    // while(index1 == remaining_nodes.size())
    // { index1 = rand() % remaining_nodes.size(); }
    std::cout << "random index 1 before: " << index1 << std::endl;
    index1 = remaining_nodes[index1]-1;
    std::cout << "random index 1 after: " << index1 << std::endl;

    int index2 = rand() % (remaining_nodes.size()-1);
    // while(index2 == remaining_nodes.size() || index2 == index1) // ensure index 1 & 2 are different
    while(index2 == index1) // ensure index 1 & 2 are different
    { index2 = rand() % (remaining_nodes.size()-1); }
    std::cout << "random index 2 before: " << index2 << std::endl;
    index2 = remaining_nodes[index2]-1;
    std::cout << "random index 2 after: " << index2 << std::endl;

    // transfer index1's edges to index2
    if(std::find(m_graph[index1].begin(), m_graph[index1].end(), index2) != m_graph[index1].end())
    {
      std::cout << "made it here 1" << std::endl;

      for(auto it = m_graph[index1].begin(); it != m_graph[index1].end(); ++it)
      {
        m_graph[index2].push_back(*it); // combine graph edges of nodes 1 and 2
      }

      // remove indices pointing to self and freshly eliminated node
      m_graph[index2].erase(std::remove(m_graph[index2].begin(), m_graph[index2].end(), index1), m_graph[index2].end());
      m_graph[index2].erase(std::remove(m_graph[index2].begin(), m_graph[index2].end(), index2), m_graph[index2].end());

      // swap out references to old node and replace with new one
      for(auto it = m_graph[index1].begin(); it != m_graph[index1].end(); ++it)
      {
        // WILL THIS STILL WORK AFTER REPLACING INDEX1/2 WITH -1 VERSION?
        // ***IMPORTANT: remember to increase index by 1 when using as value instead of index
        std::replace(m_graph[*it].begin(), m_graph[*it].end(), remaining_nodes[index1], remaining_nodes[index2]); // replaces in-place
      }
      std::cout << "made it here 2" << std::endl;

      // remove indices from remaining_nodes list
      remaining_nodes.erase(remaining_nodes.begin()+index1);

      // cleanup index1's entries since the node no longer exists (not necessary but helps debug)
      m_graph[index1].erase(m_graph[index1].begin(), m_graph[index1].end());
      std::cout << "made it here 3" << std::endl;

      return 1; // success
    }
    else
    {
      std::cout << "CAN'T COMBINE NODES " << index1 << " AND " << index2 << ", THEY ARE NOT CONNECTED." << std::endl;
      return 0; // failure
    }

  } // END OF combine() METHOD


  void go()
  {
    // main loop. start combining/eliminating nodes
    int j = 0;
    while(remaining_nodes.size() >= 2)
    {
      std::cout << "remaining_nodes size is " << remaining_nodes.size() << std::endl;
      if(combine2nodes()) // do the thing
      {
        std::cout << "round " << j+1 << std::endl;
        for(auto it1 = m_graph.begin(); it1 != m_graph.end(); ++it1)
        {
          for(auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
          std::cout << *it2 << ' ';
          std::cout << std::endl;
        }
        ++j;
      }
      else // couldn't combine nodes, try again
      {
        // --i; // try again
      }
    }

    // finally, grab the answer and return it
    std::cout << "NOW, THE COUNTING CEREMONY: " << std::endl;

    int tmp;
    int ans = 999; // some number large enough it will get replaced
    for(auto it1 = m_graph.begin(); it1 != m_graph.end(); ++it1)
    {
      for(auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
      {
        std::cout << *it2 << ' ';
      }
      std::cout << std::endl;

      // tmp = count((*it1).begin(), (*it1).end(), 1);
      tmp = (*it1).size();
        std::cout << "potential answer: " << tmp << std::endl;
      ans = (tmp < ans && tmp > 0) ? tmp : ans;
    }

    std::cout << "FINAL COUNT: " << ans << std::endl;
  } // END OF go() METHOD


public:
  KargerMinCut(std::vector<std::vector<int> >& graph, int size)
  {
    // create copy of graph, so we can modify it
    m_graph = graph;
    m_size = size;

    // COMMENT THIS OUT FOR DEVELOPMENT PURPOSES IF NEEDED
    // std::srand(unsigned(std::time(0))); // seed rand functions
    std::srand(std::time(0)); // seed rand functions

    // fill index list
    for(int i = 1; i <= size; ++i)
      remaining_nodes.push_back(i);
    // randomize(); // randomize indices

    // everything's set up, now start iterating
    go();

  } // END OF CONSTRUCTOR
}; // END OF KargerMinCut CLASS


int main(int argc, char **argv)
{
  // EXTRACTING DATA FROM FILE >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  // int n = 200; // # of lines in file
  // std::vector<std::vector<int> > graph(n);//(n, std::vector<int>(n)); // data structure for holding input values from file
  //
  // std::ifstream input;
  // input.open("kargerMinCut.txt"); // import data from file
  //
  // int i = 0;
  // std::string line;
  // while(std::getline(input, line))
  // {
  //   std::stringstream ss(line);
  //
  //   // std::cout << "index " << i << std::endl;
  //
  //   int N;
  //   while(ss >> N)
  //   {
  //     int isfirst = 0;
  //     if(!isfirst && N != i + 1)
  //     {
  //       graph[i].push_back(N);
  //       // if(i < 5)
  //         std::cout << "index: " << i << ", value: " << N << std::endl;
  //     }
  //     ++isfirst;
  //   }
  //   ++i;
  // }
  // input.close();
  // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< END EXTRACTION

  int n = 4;
  std::vector<std::vector<int> > graph(4);
  graph[0].insert(graph[0].end(), {2, 3});
  graph[1].insert(graph[1].end(), {1, 3, 4});
  graph[2].insert(graph[2].end(), {1, 2, 4});
  graph[3].insert(graph[3].end(), {2, 3});


  std::cout << "UPON INSTANTIATION" << std::endl;
  for(auto it1 = graph.begin(); it1 != graph.end(); ++it1)
  {
    for(auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2)
      std::cout << *it2 << ' ';
    std::cout << std::endl;
  }


  // DO SOMETHING WITH FRESHLY EXTRACTED DATA >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
  KargerMinCut kmc = KargerMinCut(graph, n);

  // // verify everything looks good
  // std::cout << "           first 10: ";
  // for(int a = 0; a < 10; ++a) // print out first 10, just to check
  // { std::cout << arr[a] << ' '; }
  // std::cout << std::endl;
  //
  // // verify everything looks good
  // std::cout << "            last 10: ";
  // for(int a = n-10; a < n; ++a) // print out last 10, just to check
  // { std::cout << arr[a] << ' '; }
  // std::cout << std::endl;
  //
  // // verify correct order
  // int tmp = 99;
  // int maxdiff = 0;
  // for(int m = 0; m < n-1; ++m)
  // {
  //   tmp = arr[m+1] - arr[m];
  //   maxdiff = (tmp > maxdiff) ? tmp : maxdiff;
  // }
  // std::cout << "max difference in array: " << maxdiff << std::endl;
  //
  // // verify min/max are correct
  // int max = 0;
  // int min = 999;
  // for(int m = 0; m < n; ++m)
  // {
  //   max = (arr[m] > max) ? arr[m] : max;
  //   min = (arr[m] < min) ? arr[m] : min;
  // }
  // std::cout << "max value in array: " << max << std::endl;
  // std::cout << "min value in array: " << min << std::endl;
  //
  // // print out the value we're actually looking for
  // std::cout << "number of comparisons made: " << qs.comparisons << std::endl;

  return 0;
}
