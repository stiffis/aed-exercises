#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "chainhash.h"

using namespace std;

vector<pair<string, string>> loadCSV(string file);
void testUnorderedMap();

int main()
{
  testUnorderedMap();
  testHashTable();
  return 0;
}

void testHashTable(){
  vector<pair<string, string>> data = loadCSV("smalldata.csv");
  ChainHash<string, string> hash(13);

  for(size_t i=0;i<data.size();i++)
      hash.set(data[i].first, data[i].second);
  
  cout<<"Size of the hash table:"<<hash.bucket_count()<<endl;

  for(int i=0;i<hash.bucket_count();i++){
      cout<<"Bucket #"<<i<<" contains "<<hash.bucket_size(i)<<" elements:";
      //usar el forward_list del stl
      for(auto& it = hash.begin(i); it != hash.end(i); ++it)
          cout<<"["<<*it<<"] ";
      cout<<endl;
  }
}

void testUnorderedMap()
{
  vector<pair<string, string>> data = loadCSV("smalldata.csv");  
  unordered_map<string, string> map;  

  for (auto par : data)
    map[par.first] = par.second;  
  
  int maxCount = 0;
  for (unsigned i = 0; i < map.bucket_count(); ++i)
  {
    cout << "bucket #" << i << " contains "<<map.bucket_size(i)<<" elements ";
    for (auto it = map.begin(i); it != map.end(i); ++it)
      cout << "[" << it->first << ":" << it->second << "] ";
    cout << "\n";

    if(map.bucket_size(i) > maxCount) maxCount = map.bucket_size(i);
  }

  cout << "Size of Hash Table: " << map.bucket_count() << endl;
  cout<<"Max count:"<<maxCount<<endl;
}

vector<pair<string, string>> loadCSV(string file)
{
  vector<pair<string, string>> data;
  fstream fin;
  fin.open(file, ios::in);
  vector<string> row;
  string line, word, temp;
  int i = 0;
  while (!fin.eof())
  {
    row.clear();
    getline(fin, line);
    if (i++ == 0)
      continue;
    stringstream s(line);
    while (getline(s, word, ';'))
    {
      row.push_back(word);
    }    
    if (row.size() == 2)
      data.push_back({row[0], row[1]});
  }
  return data;
}

template<typename TK>
size_t getHashCode(TK key){
    hash<string> hasher;
    return hasher(key);
}