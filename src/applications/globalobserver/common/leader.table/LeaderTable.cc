#include "LeaderTable.h"

LeaderTable::LeaderTable()
{
   changes = 0;
}

LeaderTable::~LeaderTable(){}

bool
LeaderTable::insertLeader(uint32_t id)
{
   bool result = false;
   if(table.find(id) == table.end())
   {
      table[id] = std::make_pair(0.0,0.0);
      changes++;
      result = true;
   }
   return result;
}

bool
LeaderTable::insertFilteredLeader(uint32_t id)
{
   bool result = false;
   if(_table.find(id) != _table.end())
   {
      filteredLeaders[id] = _table[id];
      _table.erase(id);
      result = true;
   }
   else if(table.find(id) != table.end())
   {
      filteredLeaders[id] = table[id];
      table.erase(id);
      result = true;
   }
   return result;
}

void
LeaderTable::restoreFilteredLeaders()
{
   if(!filteredLeaders.empty())
      for(auto& pair : filteredLeaders)
      {
         if(pair.second.second > 0)
            _table[pair.first] = pair.second;
         else
            table[pair.first] = pair.second;
      }
   filteredLeaders.clear();
}

bool
LeaderTable::setStartTime(uint32_t id, simtime_t start)
{
   bool result = false;
   if(table.find(id) == table.end())
   {
      table[id] = std::make_pair(start,0.0);
      result = true;
      changes++;
   }
   return result;
}

bool
LeaderTable::setEndTime(uint32_t id, simtime_t end)
{
   bool result = false;
   if(table.find(id) != table.end())
   {
      period_t temp = table[id];
      table.erase(id);
      temp.second = end;
      _table[id] = temp;
      result = true;
      changes++;
   }
   return result;
}

uint8_t
LeaderTable::getInvalidLeaderNumber()
{
   return _table.size();
}

uint8_t
LeaderTable::getFilteredLeaderNumber()
{
   return filteredLeaders.size();
}

simtime_t
LeaderTable::popPeriod()
{
   simtime_t period = 0.0;
   if(!_table.empty())
   {
      auto it = _table.begin();
      period = it->second.second - it->second.first;
      _table.erase(it);
   }
   return period;
}

simtime_t
LeaderTable::getPeriod(uint32_t id)
{
   simtime_t period = 0.0;
   if(!_table.empty())
      period = _table[id].second - _table[id].first;
   return period;
}

LeaderTable::iterator
LeaderTable::invalidLeaderTableBegin()
{
   return _table.begin();
}

LeaderTable::iterator
LeaderTable::invalidLeaderTableEnd()
{
   return _table.end();
}


LeaderTable::iterator
LeaderTable::begin()
{
   return table.begin();
}

LeaderTable::iterator
LeaderTable::end()
{
   return table.end();
}

unsigned int
LeaderTable::size()
{
   return table.size();
}

uint32_t
LeaderTable::erase(uint32_t id)
{
   uint32_t result = 0;
   result += table.erase(id);
   result += _table.erase(id);
   return result;
}

void
LeaderTable::clear()
{
   table.clear();
}

LeaderTable::iterator
LeaderTable::find(uint32_t id)
{
   return table.find(id);
}

uint8_t
LeaderTable::getChanges()
{
   return changes;
}

void
LeaderTable::incrementChanges()
{
   changes++;
}

void
LeaderTable::decrementChanges()
{
   changes--;
}

void
LeaderTable::resetChanges()
{
   changes = 0;
}

void
LeaderTable::clearInvalidLeaders()
{
   _table.clear();
}

std::string
LeaderTable::info()
{
   std::string buffer;
   buffer += "Leader table:\n";
   for(auto& pair : table)
   {
      buffer += "leader ID: ";
      buffer += std::to_string((int)pair.first);
      buffer += " ";
      buffer += "start time: ";
      buffer +=
      std::to_string(std::get<0>(pair.second).dbl());
      buffer += "\n";
   }

   buffer+="filtered data:\n";
   for(auto& pair : filteredLeaders)
   {
      buffer += "leader ID: ";
      buffer += std::to_string((int)pair.first);
      buffer += " ";
      buffer += "start time: ";
      buffer +=
      std::to_string(std::get<0>(pair.second).dbl());
      buffer += " ";      
      buffer += "end time: ";
      buffer +=
      std::to_string(std::get<1>(pair.second).dbl());
      buffer += "\n";
   }
   
   buffer += "leaders to be erased:\n";
   for(auto& pair : _table)
   {
      buffer += "leader ID: ";
      buffer += std::to_string((int)pair.first);
      buffer += " ";
      buffer += "start time: ";
      buffer +=
      std::to_string(std::get<0>(pair.second).dbl());
      buffer += " ";      
      buffer += "end time: ";
      buffer +=
      std::to_string(std::get<1>(pair.second).dbl());
      buffer += "\n";
   }
   

   return buffer;
}
