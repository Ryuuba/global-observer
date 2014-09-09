#ifndef LEADER_TABLE_H
#define LEADER_TABLE_H
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include <string>
#include <omnetpp.h>

class LeaderTable
{     
   public:
      //triple of kind <leader id, start time, end time>
      typedef std::pair<simtime_t,simtime_t> period_t;
      typedef std::unordered_map<uint32_t,period_t>
                 ::iterator iterator;
      typedef std::unordered_map<uint32_t,period_t>
                 ::const_iterator const_iterator;
      LeaderTable();
      ~LeaderTable();
      virtual bool insertLeader(uint32_t id);
      virtual bool insertFilteredLeader(uint32_t id);
      virtual void restoreFilteredLeaders();
      virtual bool
      setStartTime(uint32_t id, simtime_t start);
      virtual bool
      setEndTime(uint32_t id, simtime_t end);
      virtual uint8_t getInvalidLeaderNumber();
      virtual uint8_t getFilteredLeaderNumber();
      virtual simtime_t popPeriod();
      virtual simtime_t getPeriod(uint32_t id);
      virtual iterator begin();
      virtual iterator end();
      virtual iterator invalidLeaderTableBegin();
      virtual iterator invalidLeaderTableEnd();
      virtual unsigned int size();
      virtual uint32_t erase(uint32_t id);
      virtual void clearInvalidLeaders();
      virtual void clear();
      virtual uint8_t getChanges();
      virtual void incrementChanges();
      virtual void decrementChanges();
      virtual void resetChanges();
      virtual iterator find(uint32_t id);
      virtual std::string info();
   protected:
      //table storing valid leader
      std::unordered_map<uint32_t,period_t> table;
      //table that temporary stores leaders to be removed
      std::unordered_map<uint32_t,period_t> _table;
      //table storing filtered leaders
      std::unordered_map<uint32_t,period_t>
      filteredLeaders;
      uint8_t changes;
};

#endif
