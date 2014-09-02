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
      virtual bool
      setStartTime(uint32_t id, simtime_t start);
      virtual bool
      setEndTime(uint32_t id, simtime_t end);
      virtual uint8_t getInvalidLeaderNumber();
      virtual simtime_t getPeriod();
      virtual iterator begin();
      virtual iterator end();
      virtual unsigned int size();
      virtual uint32_t erase(uint32_t id);
      virtual void clearInvalidLeaders();
      virtual void clear();
      virtual uint8_t getChanges();
      virtual void resetChanges();
      virtual iterator find(uint32_t id);
      virtual std::string info();
   protected:
      //table storing valid leader
      std::unordered_map<uint32_t,period_t> table;
      //table that temporary stores leaders to be removed
      std::unordered_map<uint32_t,period_t> _table;
      uint8_t changes;
};

#endif
