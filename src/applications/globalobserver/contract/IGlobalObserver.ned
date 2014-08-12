package inet.applications.globalobserver.contract;

//
// The module interface for global observers. Global
// Observers are modules that store the state of network
// nodes and implement in a centralized manner generic
// distributed algorithms.
//
// @author Adán G. Medrano-Chávez
//

moduleinterface IGlobalObserver
{
   parameters:
      @display("i=misc/sun_l");
      int range @unit(m); // coberture range of mobile hosts
   gates:
      //gate receiving notifications of network nodes
      input fromOut @directIn;
}
